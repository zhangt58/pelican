#include "elements.h"
#include "readinput.h"
#include "constants.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

seedfield::seedfield()
{
    Ex = str2cplx(dparams.seedEx);
    Ey = str2cplx(dparams.seedEy);
}

seedfield::seedfield(std::map <std::string, std::string> &var)
{
    Ex = str2cplx((var.find("seedEx")->second).c_str());
    Ey = str2cplx((var.find("seedEy")->second).c_str());
}

void seedfield::set_Ex(std::complex <double> x)
{
    Ex = x;
}

void seedfield::set_Ey(std::complex <double> x)
{
    Ey = x;
}

std::complex <double> seedfield::get_Ex()
{
    return Ex;
}

std::complex <double> seedfield::get_Ey()
{
    return Ey;
}

void seedfield::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "seedfield:\n";
    std::cout << std::setw(16) << "Ex: "   << std::setw(10) << Ex << "[V/m]\n";
    std::cout << std::setw(16) << "Phix: " << std::setw(10) << atan(std::imag(Ex)/std::real(Ex)) << "[rad]\n";
    std::cout << std::setw(16) << "Ey: "   << std::setw(10) << Ey << "[V/m]\n";
    std::cout << std::setw(16) << "Phiy: " << std::setw(10) << atan(std::imag(Ey)/std::real(Ey)) << "[rad]\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

undulator::undulator()
{
    field  = dparams.undulatorField;
    period = dparams.undulatorPeriod;
    nstep  = dparams.undulatorNstep;
    num    = dparams.undulatorNum;
}

undulator::undulator(std::map <std::string, std::string> &var)
{
    field  = atof((var.find("undulatorField" )->second).c_str());
    period = atof((var.find("undulatorPeriod")->second).c_str());
    nstep  = atof((var.find("undulatorNstep" )->second).c_str());
    num    = atof((var.find("undulatorNum"   )->second).c_str());
}

void undulator::set_period(double x)
{
    period = x;
}

void undulator::set_field(double x)
{
    field = x;
}

void undulator::set_num(unsigned int n)
{
    num = n;
}

void undulator::set_nstep(unsigned int n)
{
    nstep = n;
}

double undulator::get_field()
{
    return field;
}

double undulator::get_period()
{
    return period;
}

unsigned int undulator::get_num()
{
    return num;
}

unsigned int undulator::get_nstep()
{
    return nstep;
}

void undulator::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "undulator:\n";
    std::cout << std::setw(16) << "Period length: "   << std::setw(10) << period << "[m]\n";
    std::cout << std::setw(16) << "Period number: "   << std::setw(10) << num << "\n";
    std::cout << std::setw(16) << "Field: " << std::setw(10) << field << "[T]\n";
    std::cout << std::setw(16) << "nstep: " << std::setw(10) << nstep << "\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

electronBeam::electronBeam()
{
    avgBetaFunc   = dparams.electronAvgBetaFunc;
    centralEnergy = dparams.electronCentralEnergy;
    energySpread  = dparams.electronEnergySpread;
    emitnx        = dparams.electronEmitnx;
    emitny        = dparams.electronEmitny;
    peakCurrent   = dparams.electronPeakCurrent;
}

electronBeam::electronBeam(std::map <std::string, std::string> &var)
{
    avgBetaFunc   = atof((var.find("electronAvgBetaFunc"  )->second).c_str());
    centralEnergy = atof((var.find("electronCentralEnergy")->second).c_str());
    energySpread  = atof((var.find("electronEnergySpread" )->second).c_str());
    emitnx        = atof((var.find("electronEmitnx"       )->second).c_str());
    emitny        = atof((var.find("electronEmitny"       )->second).c_str());
    peakCurrent   = atof((var.find("electronPeakCurrent"  )->second).c_str());
}

void electronBeam::set_centralEnergy(double x)
{
    centralEnergy = x;
}

void electronBeam::set_energySpread(double x)
{
    energySpread = x;
}

void electronBeam::set_emitnx(double x)
{
    emitnx = x;
}

void electronBeam::set_emitny(double x)
{
    emitny = x;
}

void electronBeam::set_peakCurrent(double x)
{
    peakCurrent = x;
}

void electronBeam::set_avgBetaFunc(double x)
{
    avgBetaFunc = x;
}

double electronBeam::get_centralEnergy()
{
    return centralEnergy;
}

double electronBeam::get_energySpread()
{
    return energySpread;
}

double electronBeam::get_emitnx()
{
    return emitnx;
}

double electronBeam::get_emitny()
{
    return emitny;
}

double electronBeam::get_peakCurrent()
{
    return peakCurrent;
}

double electronBeam::get_avgBetaFunc()
{
    return avgBetaFunc;
}

void electronBeam::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "electron beam:\n";
    std::cout << std::setw(16) << "central energy: "    << std::setw(10) << centralEnergy*0.511 << "[MeV]\n";
    std::cout << std::setw(16) << "energy spread: "     << std::setw(10) << energySpread*0.511  << "[MeV]\n";
    std::cout << std::setw(16) << "emittance (x): "     << std::setw(10) << emitnx              << "[um]\n";
    std::cout << std::setw(16) << "emittance (y): "     << std::setw(10) << emitny              << "[um]\n";
    std::cout << std::setw(16) << "peak current: "      << std::setw(10) << peakCurrent         << "[A]\n";
    std::cout << std::setw(16) << "average beta func: " << std::setw(10) << avgBetaFunc         << "[m]\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

FELradiation::FELradiation()
{
    wavelength = dparams.FELwavelength;
}

FELradiation::FELradiation(std::map <std::string, std::string> &var)
{
    wavelength = atof((var.find("FELwavelength")->second).c_str());
}

void FELradiation::set_wavelength(double x)
{
    wavelength = x;
}

double FELradiation::get_wavelength()
{
    return wavelength;
}

void FELradiation::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "FEL radiation:\n";
    std::cout << std::setw(16) << "central wavelength: " << std::setw(10) << wavelength*1e9 << "[nm]\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

controlpanel::controlpanel()
{
    npart = dparams.npart;
}

controlpanel::controlpanel(std::map <std::string, std::string> &var)
{
    npart = atoi((var.find("cpnpart")->second).c_str());
}

void controlpanel::set_npart(unsigned int n)
{
    npart = n;
}

unsigned int controlpanel::get_npart()
{
    return npart;
}

void controlpanel::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "control parameters:\n";
    std::cout << std::setw(16) << "particle number: " << std::setw(10) << npart << "\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}
