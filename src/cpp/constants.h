#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <vector>
#include <string>

/** \brief define classes: physical constants and default input parameters.
 *
 * created time: Jul. 1st,  15:48, 2014
 * last updated: Jul. 17st, 20:06, 2014
 */

// integration methods:
// RK4: Runge-Kutta 4th
// EU1: Euler 1st
// EU2: Euler 2nd
enum intMethods 
{
    RK4 = 0,
    EU1 = 1,
    EU2 = 2
};

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
        void info(); //!< show all the physical constants
};

class defaultParams
{
    protected:
        //!< paramlist: structure of default input parameters list
        struct paramlist{
            //!< seedfield
            std::string seedEx;
            std::string seedEy;

            //!< undulator
            double       undulatorField;
            double       undulatorPeriod;
            double       undulatorNstep;
            unsigned int undulatorNum;

            //!< electron beam
            double electronAvgBetaFunc;
            double electronCentralEnergy;
            double electronEnergySpread;
            double electronEmitnx;
            double electronEmitny;
            double electronPeakCurrent;

            //!< FEL radiation
            double FELwavelength;

            //!< control panel
            unsigned int cpnpart;
            intMethods cpmethod;
            std::string cpoutfile;

            //!< scan panel
            bool spsflag, speflag;
            std::string spparam, spobjfunc;
            double spvbegin, spvend, spvstep;
            std::string spoutfile;
            
        } dparams;

        //!< other defined parameters
        struct otherparams{
            std::vector <std::string> allowedScanParams; //!< allowed scan parameters
            std::vector <std::string> allowedObjeParams; //!< allowed objective parameters
        } oparams;

    public:
        defaultParams();
        //~defaultParams();
};

// define electric field class
class efield
{
    private:
        double realpart, imagpart;
//        double phase, amplitude;
    public:
        efield(); // default constructor,(0,0)
        efield(std::string str);
        efield(double &x, double &y); // (x,y)
        efield(efield &x);
        void set_efield(double &x, double &y);
        efield get_efield(); // return efield class type
        double get_real();
        double get_imag();
        double get_phase();
        double get_amplitude(); // return |Ex|
        double get_amplitude2(); // return |Ex|^2
};

#endif //!< CONSTANTS_H_
