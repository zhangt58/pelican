#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(int argc, char **argv)
{

    int n = 17600;
    double *psi = new double [n];
    double *gam = new double [n];
    ifstream fidin;
    fidin.open("../pelican.dis",ifstream::in);
    if (fidin.good())
    {
        for (int i = 0; i < n; i++)
            fidin >> psi[i] >> gam[i];
        fidin.close();
    }
    else
    {
        cout << "read error!" << endl;
        exit(1);
    }

    for (int i = 0; i < n; i++)
        cout << psi[i] << " " << gam[i] << endl;

    return 0;
}

