#ifndef ELEMENTS_H_
#define ELEMENTS_H_

/** \brief define element classes.
 *
 * created time: Jul. 1st,  15:47, 2014
 * last updated: Jul. 17th, 20:49, 2014
 */

#include <string>
#include <map>
#include "constants.h"

class seedfield : public defaultParams
{
    private:
        efield Ex, Ey;

    public:

        seedfield();
        seedfield(std::map <std::string, std::string> &var);

        void set_Ex (efield x); //!< electric field in x, [V/m]
        void set_Ey (efield x); //!< electric field in y, [V/m]

        efield get_Ex();
        efield get_Ey();

        void info(); //!< show all parameters
};

class undulator : public defaultParams
{
    private:
        double period, field;
        unsigned int num;
        double deltz;

    public:

        undulator();
        undulator(std::map <std::string, std::string> &var);

        void set_period(double x);       //!< period length, [m]
        void set_field (double x);       //!< peak magnetic field, [T]
        void set_num   (unsigned int n); //!< total period number
        void set_deltz (double x);       //!< integration length in period

        double get_field ();
        double get_period();
        unsigned int get_num();
        double get_deltz();

        void info(); //!< show all parameters

};

class electronBeam : public defaultParams
{
    private:
        double centralEnergy, energySpread, emitnx, emitny, peakCurrent;
        double avgBetaFunc;

    public:

        electronBeam();
        electronBeam(std::map <std::string, std::string> &var);

        void set_centralEnergy(double x);   //!< beam energy, $\gamma$
        void set_energySpread (double x);   //!< rms energy spread, $\sigma\gamma$
        void set_emitnx(double x);          //!< normalized emittance in x
        void set_emitny(double x);          //!< normalized emittance in y

        void set_peakCurrent(double x);     //!< peak current, [A]

        void set_avgBetaFunc(double x);     //!< average beta function, [m]

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

        void set_wavelength(double x); //!< central wavelength, [m]

        double get_wavelength();

        void info();

};

class controlpanel : public defaultParams
{
    private:
        unsigned int npart;
        intMethods method;
        std::string outfilename;
        std::string parfilename;
        std::string disfilename;
        int parflag;
        int pardelz;
        int disflag;
        int anaflag;

    public:

        controlpanel();
        controlpanel(std::map <std::string, std::string> &var);

        void set_npart(unsigned int n); //!< particle number
        void set_method(intMethods flag); //!< integration method
        void set_outfilename(std::string str); //!< outputfile name
        void set_parfilename(std::string str); //!< outputfile name for particle dist
        void set_disfilename(std::string str); //!< file name for particle dist to read in
        void set_parflag(int n); //!< set particle dump flag, 1: dump, 0: not dump, the file name is defined by parfilename
        void set_disflag(int n); //!< set particle import flag, 1: import, 0: not, the file name is defined by disfilename
        void set_pardelz(int n); //!< dump particle dist every n periods
        void set_anaflag(int n); //!< set FEL analysis calculation flag, 1: enable, 0: disable

        unsigned int get_npart();
        intMethods get_method();
        std::string get_outfilename();
        std::string get_parfilename();
        std::string get_disfilename();
        int get_parflag();
        int get_disflag();
        int get_pardelz();
        int get_anaflag();

        void info();
};

class scanpanel : public defaultParams
{
    private:
        bool scanflag;                                  //!< 1: do scan; other values, do not scan
        bool echoflag;                                  //!< 1: print scan information, or not
        std::string paramName;                          //!< specify the parameter name to scan
        std::string objfunc;                            //!< the objective function to optimize
        double vbegin, vstep, vend;                     //!< specify paramName scan range, from vbegin to vend with step of vstep
        int nscan;                                      //!< total number of scan points
        double *scancord1, *scancord2;                  //!< (scancord1, scancord2) = (x, y)
        std::string outfilename;                        //!< output file for scan results 
    public:

        scanpanel();
        scanpanel(std::map <std::string, std::string> &var);

        ~scanpanel();

        int checkScanParamIsOK();       //!< check if scan parameter (string) setup is OK, return 1 if is OK, or 0;

        int checkScanSetupIsOK();       //!< check scan setup, return 1 if all the parameters are OK, or 0 and exit(1);

        void updateVarlist(std::map <std::string, std::string> &var,
                           double newvalue,
                           electronBeam &elecP,
                           seedfield    &seedP,
                           undulator    &unduP,
                           FELradiation &radiP);           //!< update varlist read from external namelist file


        void set_electronBeam(electronBeam &elecP, std::map <std::string, std::string> &var);
        void set_seedfield   (seedfield    &seedP, std::map <std::string, std::string> &var);
        void set_undulator   (undulator    &unduP, std::map <std::string, std::string> &var);
        void set_FELradiation(FELradiation &radiP, std::map <std::string, std::string> &var);

        void paramScan(std::map <std::string, std::string> &var,
                       electronBeam &elecP,
                       seedfield    &seedP,
                       undulator    &unduP,
                       FELradiation &radiP,
                       controlpanel &cntlP);               //!< do parameters scan

        void dumpdata();                //!< output the scan result into some file

        void info();

        bool get_scanflag();

        void set_outfilename(std::string str); 
        std::string get_outfilename();

};

#endif //!< ELEMENTS_H_
