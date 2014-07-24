#include "constants.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

void physicalConstants::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "Physical Constants:\n";
    std::cout << std::setw(16) << "PI: "                  << std::setw(10) << PI   << "\n";
    std::cout << std::setw(16) << "vacuum permittivity: " << std::setw(10) << eps0 << "[F/m]\n";
    std::cout << std::setw(16) << "vacuum permeability: " << std::setw(10) << mu0  << "[V.s/(A.m)]\n";
    std::cout << std::setw(16) << "electron mass: "       << std::setw(10) << M0   << "[kg]\n";
    std::cout << std::setw(16) << "electron charge: "     << std::setw(10) << E0   << "[coulomb]\n";
    std::cout << std::setw(16) << "light speed: "         << std::setw(10) << C0   << "[m/s]\n";
    std::cout << std::setw(16) << "Alfven current: "      << std::setw(10) << IA   << "[A]\n";
    std::cout << std::setw(16) << "19 coefficients of M.Xie formula..." << "\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

physicalConstants::physicalConstants()
{
    PI   = 3.141592653589793;
    eps0 = 8.854187817620e-12; //!< vacuum permittivity, [F/m]
    mu0  = 4*PI*1e-7;          //!< vacuum permeability, [V.s/(A.m)]
    M0   = 9.10938188E-31;     //!< electron mass, [kg]
    E0   = 1.60218E-19;        //!< electron charge, [coulomb]
    C0   = 299792458.0;        //!< light speed, [meter/sec]
    IA   = 17045.0;            //!< Alfven current, [A]

    //!< coefficients for M.Xie formula, a1-a19
    coefs.a1  = 0.45;
    coefs.a2  = 0.57;
    coefs.a3  = 0.55;
    coefs.a4  = 1.6;
    coefs.a5  = 3.0;
    coefs.a6  = 2.0;
    coefs.a7  = 0.35;
    coefs.a8  = 2.9;
    coefs.a9  = 2.4;
    coefs.a10 = 51.0;
    coefs.a11 = 0.95;
    coefs.a12 = 3.0;
    coefs.a13 = 5.4;
    coefs.a14 = 0.7;
    coefs.a15 = 1.9;
    coefs.a16 = 1140.0;
    coefs.a17 = 2.2;
    coefs.a18 = 2.9;
    coefs.a19 = 3.2;
}

defaultParams::defaultParams() //!< default parameters
{
    //!< seedfield
    dparams.seedEx = "1e6,0";     //!< electric field in x [V/m], string of "realpart,imagpart" format
    dparams.seedEy = "0.001,0";   //!< electric field in y [V/m], string of "realpart,imagpart" format

    //!< undulator
    dparams.undulatorField  = 0.42548; //!< undulator peak field, [T]
    dparams.undulatorPeriod = 0.025;   //!< undulator period, [m]
    dparams.undulatorDeltz  = 1.0;     //!< integration length in period
    dparams.undulatorNum    = 200;     //!< total integrated undulator period

    //!< electron beam
    dparams.electronAvgBetaFunc   = 4;      //!< average beta function, sigma_r = sqrt(emitnx*betax/gamma)
    dparams.electronCentralEnergy = 265;    //!< central energy, gamma0
    dparams.electronEnergySpread  = 265e-4; //!< energy spread
    dparams.electronEmitnx        = 4e-6;   //!< normalized emittance in x, [mm.mrad]
    dparams.electronEmitny        = 4e-6;   //!< normalized emittance in y, [mm.mrad]
    dparams.electronPeakCurrent   = 200;    //!< peak current, [A]

    //!< FEL radiation
    dparams.FELwavelength = 266e-9;         //!< FEL wavelength, [m]

    //!< control panel
    dparams.cpnpart  = 10000;               //!< particle number
    dparams.cpmethod = RK4;                 //!< integration method, RK4|EU1|EU2
    dparams.cpoutfile = "pelican.out";      //!< pelican output file name
    dparams.cpparfile = "pelican.par";      //!< pelican output file name for particle dist
    dparams.cpparflag = 0;                  //!< by default, do not dump particle dist
    dparams.cppardelz = 0;                  //!< 0 means dump the last record particle dist, or dump every cppardelz period

    //!< scan panel
    dparams.spsflag  = 0;                       //!< scan flag, enable by none zero value
    dparams.speflag  = 0;                       //!< echo flag, enable by none zero value
    dparams.spparam  = "electronCentralEnergy"; //!< scan beam energy
    dparams.spobjfunc= "power";                 //!< objective function
    dparams.spvbegin = 260;                     //!< scan begin value for param
    dparams.spvend   = 270;                     //!< scan end value for param
    dparams.spvstep  = 0.1;                     //!< scan step value for param
    dparams.spoutfile= "pelican.scn";           //!< output file name for scan results

    //!< other defined parameters
/*
    std::string allowedScanParamsArr[] = {
        "electronCentralEnergy",
        "electronPeakCurrent"
    };
    std::string allowedObjeParamsArr[] = {
       "power",
        "bunching"
    };
*/
    //oparams.allowedScanParams = new std::vector <std::string> (allowedScanParamsArr, allowedScanParamsArr+sizeof(allowedScanParamsArr)/sizeof(allowedScanParamsArr[0]));
    //oparams.allowedObjeParams = new std::vector <std::string> (allowedObjeParamsArr, allowedObjeParamsArr+sizeof(allowedObjeParamsArr)/sizeof(allowedObjeParamsArr[0]));
    oparams.allowedScanParams.push_back("electronCentralEnergy");
    oparams.allowedScanParams.push_back("electronPeakCurrent");

    oparams.allowedObjeParams.push_back("power");
    oparams.allowedObjeParams.push_back("bunching");
}

/*
defaultParams::~defaultParams()
{
    delete[] oparams.allowedObjeParams;
    delete[] oparams.allowedScanParams;
}
*/

efield::efield()
{
    realpart = imagpart = 0;
}

efield::efield(std::string str)
{
    size_t pos = str.find(","); 
    std::istringstream sstr(str.replace(pos, 1, " "));
    double x, y;
    sstr >> x;
    sstr >> y;
    realpart = x;
    imagpart = y;
}

efield::efield(double &x, double &y)
{
    realpart = x;
    imagpart = y;
}

efield::efield(efield &x)
{
    realpart = x.get_real();
    imagpart = x.get_imag();
}

void efield::set_efield(double &x, double &y)
{
    realpart = x;
    imagpart = y;
}

efield efield::get_efield()
{
    efield Extmp(realpart, imagpart);
    return Extmp;
    //return efield(realpart, imagpart);
}

double efield::get_real()
{
    return realpart;
}

double efield::get_imag()
{
    return imagpart;
}

double efield::get_phase()
{
    return atan(imagpart/realpart);
}

double efield::get_amplitude()
{
    return sqrt(realpart*realpart+imagpart*imagpart);
}

double efield::get_amplitude2()
{
    return realpart*realpart+imagpart*imagpart;
}

