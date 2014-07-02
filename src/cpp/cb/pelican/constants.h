#ifndef CONSTANTS_H_
#define CONSTANTS_H_
#include <complex>

/*************************************************************************\
 *
 * define classes: physical constants and default input parameters
 *
 * created time: Jul. 1st, 15:48, 2014
 * last updated: Jul. 1st, 15:48, 2014
\*************************************************************************/

class physicalConstants
{
    protected:
        double PI, eps0, mu0, M0, E0, C0, IA;
        struct coefsXie{
            double a1,  a2,  a3,  a4,  a5,  a6,
                   a7,  a8,  a9,  a10, a11, a12,
                   a13, a14, a15, a16, a17, a18,
                   a19;
            } coefs;

    public:
        physicalConstants();
        void info(); // show all the physical constants
};

class defaultParams
{
    protected:
        // paramlist: structure of default input parameters list
        struct paramlist{
            // seedfield
            std::string seedEx;
            std::string seedEy;

            // undulator
            double       undulatorField;
            double       undulatorPeriod;
            unsigned int undulatorNstep;
            unsigned int undulatorNum;

            // electron beam
            double electronAvgBetaFunc;
            double electronCentralEnergy;
            double electronEnergySpread;
            double electronEmitnx;
            double electronEmitny;
            double electronPeakCurrent;

            // FEL radiation
            double FELwavelength;

        } dparams;

    public:
        defaultParams();
};


#endif // CONSTANTS_H_
