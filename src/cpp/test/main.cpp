#include "readinput.h"
#include "elements.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char** argv)
{
    std::map <std::string, std::string> varlist; // namelist map variable
    std::ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        std::cout << "File open error!" << std::endl;
        exit(1);
    }

    getfield(infile, varlist);
    printlist(varlist);

    seedfield       seedfieldParams;
    seedfieldParams.info();

    return 0;
}

