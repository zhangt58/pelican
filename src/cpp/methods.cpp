#include "methods.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

FELAnalysis::FELAnalysis(undulator &unduP, electronBeam &elecP, FELradiation &radiP)
{
    gamma0  = elecP.get_centralEnergy();
    sigmag0 = elecP.get_energySpread ();
    emitn   = elecP.get_emitnx       ();
    avgbeta = elecP.get_avgBetaFunc  ();
    lambdau = unduP.get_period       ();
    bfield  = unduP.get_field        ();
    current = elecP.get_peakCurrent  ();
    lambdas = radiP.get_wavelength   ();

    sigmax = sqrt(avgbeta*emitn/gamma0);
    au = sqrt(lambdas*2*gamma0*gamma0/lambdau-1);
    //au     = 0.934*bfield*lambdau*100/sqrt(2.0);
    b      = au*au/2.0/(1+au*au);
    JJ     = gsl_sf_bessel_J0(b) - gsl_sf_bessel_J1(b);
    rho1D  = pow((0.5/gamma0)*(0.5/gamma0)*(0.5/gamma0)*current/IA*(au*lambdau*JJ/2.0/PI/sigmax)*(au*lambdau*JJ/2.0/PI/sigmax),1.0/3.0);
    Lg1D   = lambdau/4/PI/sqrt(3)/rho1D;
    etad = Lg1D/(4*PI*sigmax*sigmax/lambdas);
    etae = Lg1D/avgbeta*4*PI*emitn/gamma0/lambdas;
    etag = Lg1D/lambdau*4*PI*sigmag0/gamma0;
    CapG = coefs.a1 *pow(etad,coefs.a2 )
         + coefs.a3 *pow(etae,coefs.a4 )
         + coefs.a5 *pow(etag,coefs.a6 )
         + coefs.a7 *pow(etae,coefs.a8 )*pow(etag,coefs.a9 )
         + coefs.a10*pow(etad,coefs.a11)*pow(etag,coefs.a12)
         + coefs.a13*pow(etad,coefs.a14)*pow(etae,coefs.a15)
         + coefs.a16*pow(etad,coefs.a17)*pow(etae,coefs.a18)*pow(etag,coefs.a19);
    Lg3D  = Lg1D*(1+CapG);
    rho3D = lambdau/4/PI/sqrt(3)/Lg3D;
    Psat  = 1.6*rho1D*Lg1D*Lg1D/(Lg3D*Lg3D)*gamma0*0.511*current/1000.0; // GW
}

FELAnalysis::~FELAnalysis()
{
}

double FELAnalysis::get_FELparameter1D()
{
    return rho1D;
}

double FELAnalysis::get_FELparameter3D()
{
    return rho3D;
}

double FELAnalysis::get_FELgainlength1D()
{
    return Lg1D;
}

double FELAnalysis::get_FELgainlength3D()
{
    return Lg3D;
}

double FELAnalysis::get_FELsatpower()
{
    return Psat;
}

FELNumerical::FELNumerical(seedfield &seedP, undulator &unduP, electronBeam &elecP, FELradiation &radiP, controlpanel &contP)
{
    seedEx  = seedP.get_Ex           ();
    seedEy  = seedP.get_Ey           ();
    gamma0  = elecP.get_centralEnergy();
    sigmag0 = elecP.get_energySpread ();
    emitn   = elecP.get_emitnx       ();
    avgbeta = elecP.get_avgBetaFunc  ();
    lambdau = unduP.get_period       ();
    bfield  = unduP.get_field        ();
    nstep   = unduP.get_nstep        ();
    num     = unduP.get_num          ();
    current = elecP.get_peakCurrent  ();
    lambdas = radiP.get_wavelength   ();
    npart   = contP.get_npart        ();
    method  = contP.get_method       ();
    outfile = contP.get_outfilename  ();
}

FELNumerical::~FELNumerical()
{
    delete[] psi;
    delete[] gam;
    delete[] zposArr;
    delete[] bfArr;
    delete[] K0Arr;
    delete[] JJArr;
    delete[] ExArr;
    delete[] EyArr;
}

void FELNumerical::generateDistribution(double minpsi, double maxpsi)
{
    psi = new double [npart];
    double deltpsi = (maxpsi - minpsi)/(npart - 1);
    for(unsigned int i = 0; i < npart; i++)
    {
        psi[i] = minpsi + i*deltpsi;
    }
    gam = normrand(npart, gamma0, sigmag0);
}

void FELNumerical::initParams()
{
    au     = 0.934*bfield*100*lambdau/sqrt(2);      // normalized undulator parameter, calculated from the input parameters read from namelist file
    ku     = 2*PI/lambdau;                          // undulator wave number
    omegas = 2*PI*C0/lambdas;                       // radiation angular frequency
    gammar = sqrt(lambdau*(1+au*au)/2.0/lambdas);   // resonant gamma
    sigmax = sqrt(avgbeta*emitn/gamma0);
    j0     = current/(PI*sigmax*sigmax);            // transverse current density
    coef1  = E0/M0/C0/C0;
    coef2  = mu0*C0*C0/omegas;
    coef3  = mu0*C0/4.0/gammar;
    ndelz  = lambdau/nstep;                         // integration step size, [m]
    totalIntSteps = (int) (nstep*num);                // total integration steps
    K0Arr   = new double [totalIntSteps];
    JJArr   = new double [totalIntSteps];
    zposArr = new double [totalIntSteps];
    bfArr   = new double [totalIntSteps];
    ExArr   = new efield [totalIntSteps];
    EyArr   = new efield [totalIntSteps];

    double btmp;
    for(unsigned int i = 0; i < totalIntSteps; i++)
    {
        K0Arr[i] = au*sqrt(2);
        btmp = K0Arr[i]*K0Arr[i]/(4.0+2.0*K0Arr[i]*K0Arr[i]);
        JJArr[i] = gsl_sf_bessel_J0(btmp) - gsl_sf_bessel_J1(btmp);
    }
}

void FELNumerical::FELsolverSingleFrequency1D()
{
    efield Ex0(seedEx);
    double j1r, j1i; // j1r: real part of j1; j1i: imaginart part of j1
    double Exr, Exi; // Exr: real part of Ex; Exi: imaginart part of Ex
    
    double Eamp2; // max |E|^2
    
    maxExAmp2 = 0;
    maxEyAmp2 = 0;

    double h  = ndelz;
    double z0 = 0;

    double k1, k2, k3 ,k4;      // gamma
    double l1, l2, l3, l4;      // psi
    double m1r, m2r, m3r, m4r;  // Ex real part
    double m1i, m2i, m3i, m4i;  // Ex imag part

    for(unsigned int intzstep = 0; intzstep < totalIntSteps; intzstep++)
    {
        zposArr[intzstep] = z0;
        ExArr  [intzstep] = Ex0;

        Exr = Ex0.get_real();
        Exi = Ex0.get_imag();

        z0 += h;
        j1r =  2*j0*meancosh(psi, npart);
        j1i = -2*j0*meansinh(psi, npart);

        m1r = odef3(j1r, intzstep); // real part
        m1i = odef3(j1i, intzstep); // real part

        m4r = m3r = m2r = m1r;
        m4i = m3i = m2i = m1i;

        for(unsigned int i = 0; i < npart; i++)
        {
            switch (method)
            {
                case RK4: //!< RK4
                {
                    k1 = odef1(psi[i], Exr, Exi, j1r, j1i, intzstep);
                    l1 = odef2(gam[i]);

                    k2 = odef1(psi[i]+0.5*h*l1, Exr+0.5*h*m1r, Exi+0.5*h*m1i, j1r, j1i, intzstep);
                    l2 = odef2(gam[i]+0.5*h*k1);

                    k3 = odef1(psi[i]+0.5*h*l2, Exr+0.5*h*m2r, Exi+0.5*h*m2i, j1r, j1i, intzstep);
                    l3 = odef2(gam[i]+0.5*h*k2);

                    k4 = odef1(psi[i]+1.0*h*l3, Exr+1.0*h*m3r, Exi+1.0*h*m3i, j1r, j1i, intzstep);
                    l4 = odef2(gam[i]+1.0*h*k3);

                    gam[i] += h*(k1+2.0*k2+2.0*k3+k4)/6.0;
                    psi[i] += h*(l1+2.0*l2+2.0*l3+l4)/6.0;
                    break;
                }
                case EU1: //!< EU1
                {
                    k1 = odef1(psi[i], Exr, Exi, j1r, j1i, intzstep);
                    l1 = odef2(gam[i]);

                    gam[i] += h*k1;
                    psi[i] += h*l1;
                    break;
                }
                case EU2: //!< EU2
                {
                    k1 = odef1(psi[i], Exr, Exi, j1r, j1i, intzstep);
                    l1 = odef2(gam[i]);

                    k2 = odef1(psi[i]+h*l1, Exr+h*m1r, Exi+h*m1i, j1r, j1i, intzstep);
                    l2 = odef2(gam[i]+h*k1);

                    gam[i] += h*(k1+k2)/2.0;
                    psi[i] += h*(l1+l2)/2.0;
                    break;
                }
                default: //!< other cases
                {
                    std::cout << "Please define correct method (EU1|EU2|RK4)." << std::endl;
                    exit(1);
                }
            }
        }
        Exr += h*m1r;
        Exi += h*m1i;
        //RK4
        //Exr += h*(m1r+2.0*m2r+2.0*m3r+m4r)/6.0;
        //Exi += h*(m1i+2.0*m2i+2.0*m3i+m4i)/6.0;
        //EU1
        //Exr += h*m1r;
        //Exi += h*m1i;
        //EU2
        //Exr += h*(m1r+m2r)/2.0;
        //Exi += h*(m1i+m2i)/2.0;
        Ex0 = efield(Exr, Exi);
//        if ((Eamp2 = Ex0.get_amplitude2()) > maxExAmp2) maxExAmp2 = Eamp2;
    }
}


inline double FELNumerical::odef1(double psi1, double Exr, double Exi, double j1r, double j1i, unsigned int &idx)
{
    double tmp = K0Arr[idx]*JJArr[idx]/2.0/gammar*(Exr*cos(psi1)-Exi*sin(psi1))+coef2*(j1r*sin(psi1)+j1i*cos(psi1));
    return -coef1*tmp;
}

inline double FELNumerical::odef2(double gam1)
{
    return 2*ku*(gam1/gammar-1);
}

inline double FELNumerical::odef3(double j1value, unsigned int &idx)
{
    return -coef3*K0Arr[idx]*JJArr[idx]*j1value;
}

void FELNumerical::dumpResults()
{
    soutfile.open(outfile.c_str());
    if (soutfile.good())
    {
        for(unsigned int i= 0; i < totalIntSteps; i++)
        {
            soutfile << zposArr[i] << " " << 0.5*ExArr[i].get_amplitude2()*eps0*C0*PI*sigmax*sigmax << std::endl;
        }
        soutfile.close();
    }
    else
    {
        std::cout << outfile << " write ERROR!" << std::endl;
        exit(1);
    }
}

double* FELNumerical::get_psi()
{
    return psi;
}

double* FELNumerical::get_gam()
{
    return gam;
}

unsigned int FELNumerical::get_npart()
{
    return npart;
}

double FELNumerical::get_maxExAmp()
{
    return sqrt(maxExAmp2);
}

double FELNumerical::get_maxEyAmp()
{
    return sqrt(maxEyAmp2);
}

// global functions
double* normrand(int N, double mu, double sigma)
{
    gsl_rng *r;
    r = gsl_rng_alloc(gsl_rng_taus);
    //!<gsl_rng_set(r, time(NULL));
    double *distnum = new double [N];
    for(int i = 0; i < N; i++)
        distnum[i] = mu + gsl_ran_gaussian(r, sigma);
    gsl_rng_free(r);
    return distnum;
}

inline double meancosh(double* &a, unsigned int &n, int h)
{
    double s(0);

    for(unsigned int j = 0; j < n; j++)
        s += cos(a[j]*h);
    return s/n;
}

inline double meansinh(double* &a, unsigned int &n, int h)
{
    double s(0);

    for(unsigned int j = 0; j < n; j++)
        s += sin(a[j]*h);
    return s/n;
}
