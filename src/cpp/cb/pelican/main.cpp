#include "readinput.h"
#include "elements.h"
#include "methods.h"
#include <cstdlib>
#include <iostream>

#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    // read input parameters from external namelist file
    std::map <std::string, std::string> varlist; // namelist map variable
    std::ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        std::cout << "File open error!" << std::endl;
        exit(1);
    }
    // store all (name,value) pairs into map variable: varlist
    getfield(infile, varlist);
    // show all the read parameters
    printlist(varlist);
    infile.close();

    // set up elements with varlist,
    // or use the default parameters defined in class defaultParams in constants.{h,cpp}
    /*
    // with default
    seedfield       seedfieldParams;
    undulator       undulatorParams;
    electronBeam electronBeamParams;
    FELradiation FELradiationParams;
    */
    // with varlist
    seedfield       seedfieldParams(varlist);
    undulator       undulatorParams(varlist);
    electronBeam electronBeamParams(varlist);
    FELradiation FELradiationParams(varlist);

    // print information of each element
    seedfieldParams.info();
    undulatorParams.info();
    electronBeamParams.info();
    FELradiationParams.info();

    // do FEL analytical calculation
    FELAnalysis FELAnalysisParams(undulatorParams, electronBeamParams, FELradiationParams);
    double Lg1D  = FELAnalysisParams.get_FELgainlength1D();
    double Lg3D  = FELAnalysisParams.get_FELgainlength3D();
    double rho1D = FELAnalysisParams.get_FELparameter1D ();
    double rho3D = FELAnalysisParams.get_FELparameter3D ();
    double Psat  = FELAnalysisParams.get_FELsatpower    ();

    cout << "Lg1D : " << Lg1D  << " m"  << endl;
    cout << "Lg3D : " << Lg3D  << " m"  << endl;
    cout << "rho1D: " << rho1D << endl;
    cout << "rho3D: " << rho3D << endl;
    cout << "Psat : " << Psat  << " GW" << endl;

    // do FEL numerical simulation
    FELNumerical FELNumericalParams(undulatorParams, electronBeamParams, FELradiationParams);
    cout << FELNumericalParams.get_npart() << endl;
    FELNumericalParams.generateDistribution(-10, 10);
    double *psiins = FELNumericalParams.get_psi();
    double *gamins = FELNumericalParams.get_gam();

    ofstream ofid("tmp");
    for (int i = 0; i < FELNumericalParams.get_npart(); i++)
        ofid << psiins[i] << " " << gamins[i] << endl;
    ofid.close();
    return 0;
}

