#include <iostream>
#include "a.h"
#include <cstdlib>
#include <complex>

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));
    int npart = 10000;
    double g0 = 1.0, deltg = 0.001;
    double pi = 3.1415926;

    FELnumerical fclass(npart, g0, deltg);

    fclass.gendis(-pi,pi);

    double *a = fclass.get_psi();
    double *b = fclass.get_gam();
//    cout << a << endl;
//    cout << b << endl;

//    for (int i = 0; i < fclass.get_npart(); i++)
//        cout << a[i] << " " << b[i] << endl;

    double cm = fclass.fmean();
    cout << cm << endl;

    double *AA = new double [10]();

    for (int i = 0; i<10; i++)
        cout << AA[i] << endl;

    std::complex <double> AAA;
    std::complex <double> icplx(0,1);
    AAA = exp(icplx*3.120);
    cout << AAA.real() << endl;
    cout << icplx << endl;
    cout << -icplx << endl;


    return 0;
}

