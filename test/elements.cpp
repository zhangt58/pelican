#include "elements.h"
#include "readinput.h"
#include "constants.h"
#include <cmath>
#include <iostream>
#include <iomanip>

/*
seedfield::seedfield()
{
    defaultParams dparams;
    Ex = str2cplx(dparams.Ex);
    Ey = str2cplx(dparams.Ey);
}
*/
seedfield::seedfield()
{
    Ex = str2cplx(dparams.Ex);
    Ey = str2cplx(dparams.Ey);
}

seedfield::seedfield(std::map <std::string, std::string> &var)
{
    Ex = str2cplx((var.find("Exin")->second).c_str());
    Ey = str2cplx((var.find("Eyin")->second).c_str());
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
    std::cout << std::setw(16) << "Ex: "   << std::setw(10) << Ex << "[T/m]\n";
    std::cout << std::setw(16) << "Phix: " << std::setw(10) << atan(std::imag(Ex)/std::real(Ex)) << "[rad]\n";
    std::cout << std::setw(16) << "Ey: "   << std::setw(10) << Ey << "[T/m]\n";
    std::cout << std::setw(16) << "Phiy: " << std::setw(10) << atan(std::imag(Ey)/std::real(Ey)) << "[rad]\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}
