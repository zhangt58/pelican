#include <iostream>
#include "ex.h"

using namespace std;

int main(int argc, char **argv)
{

    gendata abins;
    double *A = abins.get_a();
    double *B = abins.get_b();
    for (int i = 0; i<10; i++)
        cout << A[i] << " " << B[i] << endl;

    return 0;
}
