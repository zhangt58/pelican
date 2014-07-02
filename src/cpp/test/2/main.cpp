#include <iostream>
#include "a.h"

using namespace std;

int main(int argc, char **argv)
{
    int npart = 10000;
    double g0 = 1.0, deltg = 0.001;
    double pi = 3.1415926;

    FELnumerical fclass(npart, g0, deltg);

    fclass.gendis(-pi,pi);

    double *a = fclass.get_psi();
    double *b = fclass.get_gam();
//    cout << a << endl;
//    cout << b << endl;

    for (int i = 0; i < fclass.get_npart(); i++)
        cout << a[i] << " " << b[i] << endl;

    return 0;
}

