#ifndef METHODS_H_
#define METHODS_H_

/** \brief define classes/functions to handle FEL physics related problems.
 *
 * class:
 *  1 FELAnalysis : FEL formulae for analytical calculation
 *  2 FELNumerical: Numerical simulations for FEL physics
 * function:
 *  1 *normrand() : generate random distribution with Gaussian distribution
 *  2 meancosh()  : return <cos(h*psi)> 
 *  3 meansinh()  : return <sin(h*psi)> 
 *
 * created time: Jul. 1st,  15:53, 2014
 * last updated: Jul. 21th, 10:47, 2014
 */

#include "constants.h"
#include "elements.h"
#include <fstream>
#include <string>

class FELAnalysis : public physicalConstants
{
    public:
        //!< class initialization to calculate all physics objectives:
        //!< 1D and 3D FEL parameters and gain length, saturation power, as well.
        FELAnalysis(undulator &unduP, electronBeam &elecP, FELradiation &radiP);
        ~FELAnalysis();

        double get_FELparameter1D ();
        double get_FELparameter3D ();
        double get_FELgainlength1D();
        double get_FELgainlength3D();
        double get_FELsatpower    ();
    private:
        double gamma0, sigmag0, emitn, avgbeta, lambdau, current, lambdas, bfield;
        double sigmax, au, rho1D, rho3D, Lg1D, Lg3D, Psat;
};

class FELNumerical : public physicalConstants
{
    public:
        //!< class initialization with input parameters
        FELNumerical(seedfield &seedP, undulator &unduP, electronBeam &elecP, FELradiation &radiP, controlpanel &contP);
        ~FELNumerical();

        unsigned int get_npart();
        double* get_psi();
        double* get_gam();
        double get_maxExAmp(); //!< get max Ex amplitude
        double get_maxEyAmp(); //!< get max Ey amplitude
        double get_endExAmp(); //!< get the last record of Ex amplitude
        double get_endEyAmp(); //!< get the last record of Ey amplitude

        //!< generate initial electron longitudinal distribution
        void generateDistribution(double minpsi, double maxpsi);

        //!< parameters initialization for numerical calculation
        void initParams();

        //!< FEL numerical calculation, single frequency in one-dimensional
        //!< by default Runge-Kutta algorithm is applied,
        //!< or define key word method as "EU1" or "EU2"
        void FELsolverSingleFrequency1D();

        //!< do FEL simulation
        void FELsimulation1D();

        //!< functions defined for ODE solver
        inline double odef1(double psi1, double Exr, double Exi, double j1r, double j1i, unsigned int &idx);
        inline double odef2(double gam1);
        inline double odef3(double j1value, unsigned int &idx); // j1value: j1r or j1i

        //!< dump numerical simulation results
        void dumpResults();

        //!< dump particle distribution
        void dumpParfile();
        
        //!< import particle distribution
        void importDisfile();

    private:
        unsigned int npart, num;
        int parflag; //!< if dump particle dist (1) or not (0, default)
        int disflag; //!< if import particle dist (1) or not (0, default)
        int pardelz; //!< save particle dist every delz period
        double deltz;
        double gamma0, sigmag0, emitn, avgbeta, lambdau, current, lambdas, bfield;
        efield seedEx, seedEy;
        double *psi, *gam;  //!< longitudinal phase space, phase [rad] and energy [gamma]
        double *zposArr;    //!< longitudinal undulator position, [m]
        double *bfArr;      //!< bunching factor
        efield *ExArr, *EyArr; //!< electric field in x and y, [v/m]
        double maxExAmp2, maxEyAmp2; // max |E(x,y)|^2
        intMethods method;
        std::string outfile; //!< output file for calc results
        std::ofstream soutfile;
        std::string parfile; //!< output file for particle dist
        std::string disfile; //!< particle dist filename to be imported if defined

        //!< for numerical calculation initialization
        double coef1, coef2, coef3, gammar, omegas, au, ku, sigmax, j0, ndelz;
        unsigned int totalIntSteps;
        double *K0Arr; //!< undulator parameter array, desinged for including errores
        double *JJArr; //!< coupled bessel factor array according to K0Arr
};


//!< generate Gaussian distribution, average value of mu,
//!< standard deviation value of sigma
double* normrand(int N, double mu, double sigma);

//!< return <cos(h*psi[])>
double meancosh(double* &a, unsigned int &n, int h = 1);

//!< return <sin(h*psi[])>
double meansinh(double* &a, unsigned int &n, int h = 1);

#endif //!< METHODS_H_
