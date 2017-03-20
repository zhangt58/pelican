#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <complex>
/*************************************************************************\
 *
 * define constants
 *
\*************************************************************************/



class physicalConstants
{
    private:
        double PI;
//        double PI   = 3.141592653589793;
//        double eps0 = 8.854187817620e-12; // vacuum permittivity, [F/m]
//        double mu0  = 4*PI*1e-7;          // vacuum permeability, [V.s/(A.m)]
//        double M0   = 9.10938188E-31;     // electron mass, [kg]
//        double E0   = 1.60218E-19;        // electron charge, [coulomb]
//        double C0   = 299792458.0;        // light speed, [meter/sec]

    public:
        physicalConstants();
        void info(); // show all the physical constants
};

/*
class defaultParams
{
    private:
        std::string Ex = "(1e5,1e4)";
        std::string Ey = "(5e5,2e3)";

    friend class seedfield;
};
*/

class defaultParams
{
    protected:
        /*
        struct params {
            std::string Ex = "(5e5, 7e4)";
            std::string Ey = "(8e5, 9e2)";
        } dparams;
        */
        struct params {
            std::string Ex;
            std::string Ey;
        } dparams;
        
    public:
        defaultParams();

};

#endif // CONSTANTS_H_
