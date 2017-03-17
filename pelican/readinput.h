#ifndef READINPUT_H_
#define READINPUT_H_

/** \brief define functions to handle reading input parameters from external namelist file.
 *
 * created time: Jul. 1st,  15:46, 2014
 * last updated: Jul. 14th, 08:56, 2014
 */

#include <string>
#include <fstream>
#include <map>
#include "elements.h"
#include "constants.h"

inline void trimline(std::string &str); //!< trim leading and tailing spaces of a string

void getfield(std::ifstream &infile, std::map <std::string, std::string> &var); //!< get variable names and values from infile

void printlist(std::map <std::string, std::string> &var); //!< print all the parameter names and values

efield str2efield(std::string str); //!< convert string into efield format, string format: (real, imag)

std::string dbl2str(double x); //!< convert double into string

intMethods str2enum(std::string &str); //!< convert string into enum type

#endif //!< READINPUT_H_
