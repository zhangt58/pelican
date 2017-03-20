#include "readinput.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>

void trimline(std::string &str)
{
    size_t pos1, pos2;
    pos1 = str.find_first_not_of(" \t\n\"\';,");
    pos2 = str.find_last_not_of (" \t\n\"\';,");
    str = str.substr(pos1,pos2-pos1+1);
}

void getfield(std::ifstream &infile, std::map <std::string, std::string> &var)
{
    std::string line, vname, value;
    while (getline(infile, line))
    {
        if (line.empty()) continue;
        trimline(line);
        if (line[0] == '#' || line[0] == '!' || line[0] == '/' || line[0] == '%') continue;
        std::istringstream sline(line);
        getline(sline, vname, '=');
        getline(sline, value, '=');
        trimline(vname);
        trimline(value);
        var[vname] = value.c_str();
    }
}

void printlist(std::map <std::string, std::string> &var)
{
    int i = 0;
    std::map <std::string, std::string> :: iterator it;
    for (it = var.begin(); it != var.end(); it++,++i)
        std::cout << std::left << std::setw(16) << it->first << " ==> " << std::setw(16) << std::setprecision(6) << atof(it->second.c_str()) << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "Total " << i << " records printed." << std::endl;
}

std::complex <double> str2cplx(std::string str)
{
    std::complex <double> dcplx;
    std::istringstream sstr(str);
    sstr >> dcplx;
    return dcplx;
}
