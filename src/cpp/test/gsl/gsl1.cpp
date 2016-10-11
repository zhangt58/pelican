#include <iostream>
#include <cstdlib>
#include <cmath>
#include <gsl/gsl_sf_bessel.h>

using namespace std;

int main(int argc, char **argv)
{
    double a = atof(argv[1]);

    cout << "J0(" << a << ") = " << gsl_sf_bessel_J0(a) << endl;
    cout << "J1(" << a << ") = " << gsl_sf_bessel_J1(a) << endl;
    cout << "J2(" << a << ") = " << gsl_sf_bessel_Jn(2,a) << endl;


    cout << "2^{1/3}" << pow(2,1.0/3.0) << endl;
    return 0;
}

