#include "readinput.h"
#include "elements.h"
#include "methods.h"
#include <cstdlib>
#include <iostream>

#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char **argv)
{
    //!< read input parameters from external namelist file
    std::map <std::string, std::string> varlist; //!< namelist map variable
    std::ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        std::cout << "File open error!" << std::endl;
        exit(1);
    }
    //!< store all (name,value) pairs into map variable: varlist
    getfield(infile, varlist);
    //!< show all the read parameters
    //!<printlist(varlist);
    infile.close();

    //!< set up elements with varlist,
    //!< or use the default parameters defined in class defaultParams, which is defined in constants.{h,cpp}
/*
    // by default
    seedfield       seedfieldParams;
    undulator       undulatorParams;
    electronBeam electronBeamParams;
    FELradiation FELradiationParams;
    controlpanel controlpanelParams;
*/

    //!< read from varlist
    seedfield       seedfieldParams(varlist);
    undulator       undulatorParams(varlist);
    electronBeam electronBeamParams(varlist);
    FELradiation FELradiationParams(varlist);
    controlpanel controlpanelParams(varlist);
    scanpanel       scanpanelParams(varlist);
/*
    // print information of each element
    seedfieldParams.info();
    undulatorParams.info();
    electronBeamParams.info();
    FELradiationParams.info();
    controlpanelParams.info();
*/

    //!< do FEL analytical calculation
    FELAnalysis FELAnalysisParams(undulatorParams, electronBeamParams, FELradiationParams);
    double Lg1D  = FELAnalysisParams.get_FELgainlength1D();
    double Lg3D  = FELAnalysisParams.get_FELgainlength3D();
    double rho1D = FELAnalysisParams.get_FELparameter1D ();
    double rho3D = FELAnalysisParams.get_FELparameter3D ();
    double Psat  = FELAnalysisParams.get_FELsatpower    ();

    cout << "Lg1D : " << Lg1D  << " m"  << endl;
    cout << "Lg3D : " << Lg3D  << " m"  << endl;
    cout << "rho1D: " << rho1D          << endl;
    cout << "rho3D: " << rho3D          << endl;
    cout << "Psat : " << Psat  << " GW" << endl;

    //!< do FEL numerical simulation
    FELNumerical FELNumericalParams(seedfieldParams, undulatorParams, electronBeamParams, FELradiationParams, controlpanelParams);
    FELNumericalParams.generateDistribution(-3.1415926, 3.1415926);

/*
    //double *psiins = FELNumericalParams.get_psi();
    double *gamins = FELNumericalParams.get_gam();
    double s = 0;
    for (int i = 0; i < FELNumericalParams.get_npart(); i++)
        s += gamins[i];
    cout << std::left << std::setprecision(12) << s/FELNumericalParams.get_npart() << endl;

    // output psi-gam distribution
    ofstream ofid("tmp");
    for (int i = 0; i < FELNumericalParams.get_npart(); i++)
        ofid << psiins[i] << " " << gamins[i] << endl;
    ofid.close();
*/

    FELNumericalParams.initParams();
    //FELNumericalParams.FELsolverSingleFrequency1D0();
    //FELNumericalParams.FELsolverSingleFrequency1D("EU1");
    //FELNumericalParams.FELsolverSingleFrequency1D("EU2");
    FELNumericalParams.FELsolverSingleFrequency1D("RK4");

    FELNumericalParams.dumpResults();

    scanpanelParams.info();
    if (scanpanelParams.get_scanflag())
    {
        scanpanelParams.paramScan(varlist,
                              electronBeamParams,
                              seedfieldParams,
                              undulatorParams,
                              FELradiationParams,
                              controlpanelParams);
        scanpanelParams.dumpdata();
    }

    return 0;
}
