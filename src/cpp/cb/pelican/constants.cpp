#include "constants.h"
#include <iostream>
#include <iomanip>

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
    eps0 = 8.854187817620e-12; // vacuum permittivity, [F/m]
    mu0  = 4*PI*1e-7;          // vacuum permeability, [V.s/(A.m)]
    M0   = 9.10938188E-31;     // electron mass, [kg]
    E0   = 1.60218E-19;        // electron charge, [coulomb]
    C0   = 299792458.0;        // light speed, [meter/sec]
    IA   = 17045.0;            // Alfven current, [A]

    // coefficients for M.Xie formula, a1-a19
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

defaultParams::defaultParams() // default parameters
{
    // seedfield
    dparams.seedEx = "(1e6,0)"; // electric field in x [T/m], double complex, (realpart, imagpart)
    dparams.seedEy = "(0.001,0)"; // electric field in y [T/m], double complex, (realpart, imagpart)

    // undulator
    dparams.undulatorField  = 0.42548; // undulator peak field, [T]
    dparams.undulatorPeriod = 0.025;   // undulator period, [m]
    dparams.undulatorNstep  = 1;       // integration steps per period
    dparams.undulatorNum    = 200;     // total integrated undulator period

    // electron beam
    dparams.electronAvgBetaFunc   = 4;      // average beta function, sigma_r = sqrt(emitnx*betax/gamma)
    dparams.electronCentralEnergy = 265;    // central energy, gamma0
    dparams.electronEnergySpread  = 265e-4; // energy spread
    dparams.electronEmitnx        = 4e-6;   // normalized emittance in x, [mm.mrad]
    dparams.electronEmitny        = 4e-6;   // normalized emittance in y, [mm.mrad]
    dparams.electronPeakCurrent   = 200;    // peak current, [A]

    // FEL radiation
    dparams.FELwavelength = 266e-9; // FEL wavelength, [m]
}
