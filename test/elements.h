#ifndef ELEMENTS_H_
#define ELEMENTS_H_

#include <string>
#include <complex>
#include <map>
#include "constants.h"

class seedfield : public defaultParams 
{
    private:
        std::complex <double> Ex, Ey;

    public:

        seedfield();
        seedfield(std::map <std::string, std::string> &var);

        void set_Ex (std::complex <double> x); // electric field in x, [T/m]
        void set_Ey (std::complex <double> x); // electric field in y, [T/m]

        std::complex <double> get_Ex();
        std::complex <double> get_Ey();

        void info(); //show all parameters
};

#endif // ELEMENTS_H_
