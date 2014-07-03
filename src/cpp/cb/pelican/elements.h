#ifndef ELEMENTS_H_
#define ELEMENTS_H_

/*************************************************************************\
 *
 * define element classes
 *
 * created time: Jul. 1st, 15:47, 2014
 * last updated: Jul. 1st, 15:47, 2014
\*************************************************************************/

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

class undulator : public defaultParams
{
    private:
        double period, field;
        unsigned int num, nstep;

    public:

        undulator();
        undulator(std::map <std::string, std::string> &var);

        void set_period(double x); // period length, [m]
        void set_field (double x); // peak magnetic field, [T]
        void set_num   (unsigned int n); // total period number
        void set_nstep (unsigned int n); // integration steps per period

        double get_field ();
        double get_period();
        unsigned int get_num  ();
        unsigned int get_nstep();

        void info(); //show all parameters

};

class electronBeam : public defaultParams
{
    private:
        double centralEnergy, energySpread, emitnx, emitny, peakCurrent;
        double avgBetaFunc;

    public:

        electronBeam();
        electronBeam(std::map <std::string, std::string> &var);

        void set_centralEnergy(double x); // beam energy, $\gamma$
        void set_energySpread (double x); // rms energy spread, $\sigma\gamma$
        void set_emitnx(double x); // normalized emittance in x
        void set_emitny(double x); // normalized emittance in y

        void set_peakCurrent(double x); // peak current, [A]

        void set_avgBetaFunc(double x); // average beta function, [m]

        double get_centralEnergy();
        double get_energySpread ();
        double get_emitnx();
        double get_emitny();
        double get_peakCurrent();
        double get_avgBetaFunc();

        void info();

};

class FELradiation : public defaultParams
{
    private:
        double wavelength;
        double* Ex;

    public:

        FELradiation();
        FELradiation(std::map <std::string, std::string> &var);

        void set_wavelength(double x); // central wavelength, [m]

        double get_wavelength();

        void info();

};

class controlpanel : public defaultParams
{
    private:
        unsigned int npart;

    public:

        controlpanel();
        controlpanel(std::map <std::string, std::string> &var);

        void set_npart(unsigned int n); // particle number

        unsigned int get_npart();

        void info();
};

#endif // ELEMENTS_H_
