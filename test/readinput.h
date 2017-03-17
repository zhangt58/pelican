#ifndef READINPUT_H_
#define READINPUT_H_

#include <string>
#include <fstream>
#include <map>
#include <complex>
#include "elements.h"

void trimline(std::string &str); // trim leading and tailing spaces of a string

void getfield(std::ifstream &infile, std::map <std::string, std::string> &var); // get variable names and values from infile

void printlist(std::map <std::string, std::string> &var); // print all the parameter names and values

std::complex <double> str2cplx(std::string str); // convert string into double complex

//void set_seedfield(seedfield &param, std::map <std::string, std::string> &var); // set initial field signal

//void set_undulator(undulator &param, std::map <std::string, std::string> &var); // set undulator parameters

//void set_electronBeam(electronBeam &param, std::map <std::string, std::string> &var); // set electron beam parameters

//void set_FELradiation(FELradiation &param, std::map <std::string, std::string> &var); // set FELradiation parameters

#endif // READINPUT_H_
