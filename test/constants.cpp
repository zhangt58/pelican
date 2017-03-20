#include "constants.h"
#include <iostream>
#include <iomanip>

void physicalConstants::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "Physical Constants:\n";
    std::cout << std::setw(16) << "PI: "                  << std::setw(10) << PI   << "\n";
//    std::cout << std::setw(16) << "vacuum permittivity: " << std::setw(10) << eps0 << "[F/m]\n";
//    std::cout << std::setw(16) << "vacuum permeability: " << std::setw(10) << mu0  << "[V.s/(A.m)]\n";
//    std::cout << std::setw(16) << "electron mass: "       << std::setw(10) << M0   << "[kg]\n";
//    std::cout << std::setw(16) << "electron charge: "     << std::setw(10) << E0   << "[coulomb]\n";
//    std::cout << std::setw(16) << "light speed: "         << std::setw(10) << C0   << "[m/s]\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

physicalConstants::physicalConstants()
{
    PI = 3.14;
}

defaultParams::defaultParams()
{
    dparams.Ex = "(1e5, 3e4)";
    dparams.Ey = "(2e5, 5e4)";
}

