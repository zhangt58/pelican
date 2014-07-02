#include "methods.h"
#include <cmath>
#include <ctime>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

FELAnalysis::FELAnalysis(undulator &unduP, electronBeam &elecP, FELradiation &radiP)
{
    gamma0  = elecP.get_centralEnergy();
    sigmag0 = elecP.get_energySpread();
    emitn   = elecP.get_emitnx();
    avgbeta = elecP.get_avgBetaFunc();
    lambdau = unduP.get_period();
    bfield  = unduP.get_field();
    current = elecP.get_peakCurrent();
    lambdas = radiP.get_wavelength();

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


FELNumerical::FELNumerical(undulator &unduP, electronBeam &elecP, FELradiation &radiP)
{
    gamma0  = elecP.get_centralEnergy();
    sigmag0 = elecP.get_energySpread();
    emitn   = elecP.get_emitnx();
    avgbeta = elecP.get_avgBetaFunc();
    lambdau = unduP.get_period();
    bfield  = unduP.get_field();
    current = elecP.get_peakCurrent();
    lambdas = radiP.get_wavelength();
    npart = 10000;
}

void FELNumerical::generateDistribution(double minpsi, double maxpsi)
{
    psi = new double [npart];
    double deltpsi = (maxpsi - minpsi)/(npart - 1);
    for(int i = 0; i < npart; i++)
    {
        psi[i] = minpsi + i*deltpsi;
    }
    gam = normrand(npart, gamma0, sigmag0);
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

double* normrand(int N, double mu, double sigma)
{
    gsl_rng *r;
    r = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(r, time(NULL));
    double *distnum = new double [N];
    for(int i = 0; i < N; i++)
        distnum[i] = mu + gsl_ran_gaussian(r, sigma);
    gsl_rng_free(r);
    return distnum;
}
