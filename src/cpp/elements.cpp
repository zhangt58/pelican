#include "elements.h"
#include "readinput.h"
#include "constants.h"
#include "methods.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <map>

seedfield::seedfield()
{
    Ex = efield(dparams.seedEx);
    Ey = efield(dparams.seedEy);
}

seedfield::seedfield(std::map <std::string, std::string> &var)
{
    Ex = efield((var.find("seedEx")->second));
    Ey = efield((var.find("seedEy")->second));
}

void seedfield::set_Ex(efield x)
{
    Ex = efield(x);
}

void seedfield::set_Ey(efield x)
{
    Ey = efield(x);
}

efield seedfield::get_Ex()
{
    return Ex;
}

efield seedfield::get_Ey()
{
    return Ey;
}

void seedfield::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "seedfield:\n";
    std::cout << std::setw(16) << "Ex: "   << std::setw(10) << Ex.get_amplitude() << "exp(i" << Ex.get_phase() << ")[V/m]\n";
    std::cout << std::setw(16) << "Ey: "   << std::setw(10) << Ey.get_amplitude() << "exp(i" << Ey.get_phase() << ")[V/m]\n";
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
    num    = atoi((var.find("undulatorNum"   )->second).c_str());
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

void undulator::set_nstep(double x)
{
    nstep = x;
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

double undulator::get_nstep()
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
    npart       = dparams.cpnpart;
    method      = dparams.cpmethod; 
    outfilename = dparams.cpoutfile;
}

controlpanel::controlpanel(std::map <std::string, std::string> &var)
{
    npart        = atoi((var.find("cpnpart" )->second).c_str());
    method       = str2enum((var.find("cpmethod")->second));
    outfilename  = var.find("cpoutfile")->second;
      
}

void controlpanel::set_npart(unsigned int n)
{
    npart = n;
}

void controlpanel::set_method(intMethods flag)
{
    method = flag;
}

void controlpanel::set_outfilename(std::string str)
{
    outfilename = str;
}

unsigned int controlpanel::get_npart()
{
    return npart;
}

intMethods controlpanel::get_method()
{
    return method;
}

std::string controlpanel::get_outfilename()
{
    return outfilename;
}

void controlpanel::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "control parameters:\n";
    std::cout << std::setw(16) << "particle number: " << std::setw(10) << npart << "\n";
    std::cout << std::setw(16) << "integration by : " << std::setw(10) << method << "\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

scanpanel::scanpanel()
{
    scanflag   = dparams.spsflag;
    echoflag   = dparams.speflag;
    paramName  = dparams.spparam;
    objfunc    = dparams.spobjfunc;
    vbegin     = dparams.spvbegin;
    vend       = dparams.spvend;
    vstep      = dparams.spvstep;
    outfilename= dparams.spoutfile;
    
    nscan     = (int)((vend-vbegin)/vstep)+1;
    scancord1 = new double [nscan];
    scancord2 = new double [nscan];
}

scanpanel::scanpanel(std::map <std::string, std::string> &var)
{
    scanflag  = atoi((var.find("spsflag"   )->second).c_str());
    echoflag  = atoi((var.find("speflag" )->second).c_str());
    vbegin    = atof((var.find("spvbegin" )->second).c_str());
    vend      = atof((var.find("spvend"   )->second).c_str());
    vstep     = atof((var.find("spvstep"  )->second).c_str());
    paramName =      (var.find("spparam"  )->second).c_str();
    objfunc   =      (var.find("spobjfunc")->second).c_str();
    outfilename = var.find("spoutfile")->second;

    nscan     = (int)((vend-vbegin)/vstep)+1;
    scancord1 = new double [nscan];
    scancord2 = new double [nscan];
}

scanpanel::~scanpanel()
{
    delete[] scancord1;
    delete[] scancord2;
}

int scanpanel::checkScanParamIsOK()
{
    int ifindscan = 0, ifindobje = 0;

    for (std::vector <std::string> :: iterator it = oparams.allowedScanParams.begin();
         it != oparams.allowedScanParams.end(); ++it)
    {
        if (paramName == *it)
            ifindscan = 1;
    }

    for (std::vector <std::string> :: iterator it = oparams.allowedObjeParams.begin();
         it != oparams.allowedObjeParams.end(); ++it)
    {
        if (objfunc == *it)
            ifindobje = 1;
    }

    return (int)(ifindscan && ifindobje);
}

int scanpanel::checkScanSetupIsOK()
{
   if (checkScanParamIsOK() != 1)
   {
       std::cout << "Scan parameter name Error!" << std::endl;
       exit(1);
   }

   if ((vbegin == vend) || ((vbegin < vend) && (vstep <= 0)) || ((vbegin > vend) && (vstep >= 0)))
   {
       std::cout << "Scan range setup Error!" << std::endl;
       exit(1);
   }

   return 1; //!< scanpanel setup is OK, ready for scan
}

void scanpanel::updateVarlist(
        std::map <std::string, std::string> &var,
        double newvalue,
        electronBeam &elecP,
        seedfield    &seedP,
        undulator    &unduP,
        FELradiation &radiP)
{
    var.find(paramName)->second = dbl2str(newvalue);
    set_electronBeam(elecP, var);
    //set_seedfield   (seedP, var);
    set_undulator   (unduP, var);
    set_FELradiation(radiP, var);
}

void scanpanel::set_electronBeam(electronBeam &elecP, std::map <std::string, std::string> &var)
{
    elecP.set_centralEnergy(atof((var.find("electronCentralEnergy")->second).c_str()));
    elecP.set_energySpread (atof((var.find("electronEnergySpread" )->second).c_str()));
    elecP.set_emitnx       (atof((var.find("electronEmitnx"       )->second).c_str()));
    elecP.set_emitny       (atof((var.find("electronEmitny"       )->second).c_str()));
    elecP.set_peakCurrent  (atof((var.find("electronPeakCurrent"  )->second).c_str()));
    elecP.set_avgBetaFunc  (atof((var.find("electronAvgBetaFunc"  )->second).c_str()));
}


void scanpanel::set_seedfield(seedfield &seedP, std::map <std::string, std::string> &var)
{
//    seedP.set_Ex()
}


void scanpanel::set_undulator(undulator &unduP, std::map <std::string, std::string> &var)
{
    unduP.set_field (atof((var.find("undulatorField" )->second).c_str()));
    unduP.set_period(atof((var.find("undulatorPeriod")->second).c_str()));
    unduP.set_nstep (atof((var.find("undulatorNstep" )->second).c_str()));
    unduP.set_num   (atoi((var.find("undulatorNum"   )->second).c_str()));
}

void scanpanel::set_FELradiation(FELradiation &radiP, std::map <std::string, std::string> &var)
{
    radiP.set_wavelength(atof((var.find("FELwavelength")->second).c_str()));
}

void scanpanel::paramScan(std::map <std::string, std::string> &var,
                          electronBeam &elecP,
                          seedfield    &seedP,
                          undulator    &unduP,
                          FELradiation &radiP,
                          controlpanel &cntlP)
{
    if (checkScanSetupIsOK()) //!< do scan, or not
    {
        int idx = 0;
        for (double vscan = vbegin; vscan <= vend; vscan += vstep)
        {
            if (echoflag) //!< print scan information or not
            {
                std::cout << std::setw(10) << paramName << " = " << std::setw(10) << vscan << "\n";
            }
            scancord1[idx] = vscan;
            updateVarlist(var, vscan, elecP, seedP, unduP, radiP);

            FELNumerical tmpFELNum(seedP, unduP, elecP, radiP, cntlP);
            tmpFELNum.generateDistribution(-3.1415926, 3.1415926);
            tmpFELNum.initParams();
            tmpFELNum.FELsolverSingleFrequency1D();

            scancord2[idx] = tmpFELNum.get_maxExAmp();
            ++idx;
        }
    }
}

void scanpanel::dumpdata()
{
    std::ofstream soutfile(outfilename.c_str());
    if (soutfile.good())
    {
        for(int i = 0; i < nscan; i++)
        {
            soutfile << scancord1[i] << " " << scancord2[i] << std::endl;
        }
        soutfile.close();
    }
    else
    {
        std::cout << outfilename << " write ERROR!" << std::endl;
        exit(1);
    }
}

void scanpanel::info()
{
    std::cout << std::left;
    std::cout << "-------------------------------\n";
    std::cout << "scanpanel:\n";
    std::cout << std::setw(16) << "scanflag: "  << std::setw(10) << scanflag  << "\n";
    std::cout << std::setw(16) << "echoflag: "  << std::setw(10) << echoflag  << "\n";
    std::cout << std::setw(16) << "scanParam: " << std::setw(10) << paramName << "\n";
    std::cout << std::setw(16) << "scanRange: " << std::setw(10) << dbl2str(vbegin)
                                                                    + ":" + dbl2str(vstep)
                                                                    + ":" + dbl2str(vend) << "\n";
    std::cout << "-------------------------------\n";
    std::cout << std::endl;
}

bool scanpanel::get_scanflag()
{
    return scanflag;
}

void scanpanel::set_outfilename(std::string str)
{
    outfilename = str;
}

std::string scanpanel::get_outfilename()
{
    return outfilename;
}
