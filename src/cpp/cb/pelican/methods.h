#ifndef METHODS_H_
#define METHODS_H_

/*************************************************************************\
 *
 * define classes/functions to handle FEL physics related problems
 * class:
 *  1 FELAnalysis : FEL formulae for analytical calculation
 *  2 FELNumerical: Numerical simulations for FEL physics
 * function:
 *  1 *normrand() : generate random distribution with Gaussian distribution
 * created time: Jul. 1st, 15:53, 2014
 * last updated: Jul. 2nd, 10:42, 2014
\*************************************************************************/

#include "constants.h"
#include "elements.h"

class FELAnalysis : public physicalConstants
{
    private:
        double gamma0, sigmag0, emitn, avgbeta, lambdau, current, lambdas, bfield;
        double sigmax, au, b, JJ, rho1D, rho3D, Lg1D, Lg3D, etad, etae, etag, CapG, Psat;
    public:
        // class initialization to calculate all physics objectives:
        // 1D and 3D FEL parameters and gain length, saturation power, as well.
        FELAnalysis(undulator &unduP, electronBeam &elecP, FELradiation &radiP);
        double get_FELparameter1D ();
        double get_FELparameter3D ();
        double get_FELgainlength1D();
        double get_FELgainlength3D();
        double get_FELsatpower    ();
};

class FELNumerical : public physicalConstants
{
    private:
        unsigned int npart;
        double gamma0, sigmag0, emitn, avgbeta, lambdau, current, lambdas, bfield;
        double *psi, *gam;
    public:
        FELNumerical(undulator &unduP, electronBeam &elecP, FELradiation &radiP);
        void generateDistribution(double minpsi, double maxpsi);
        unsigned int get_npart();
        double* get_psi();
        double* get_gam();
};

double* normrand(int N, double mu, double sigma);

#endif // METHODS_H_
