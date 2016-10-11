#include "ex.h"
#include <iostream>

gendata::gendata()
{
    a = new double [10];
    b = new double [10];
    for(int i = 0; i<10; i++)
    {
        a[i] = i;
        b[i] = i*2;
    }
}

gendata::~gendata()
{
    std::cout << "destructor is called." << std::endl;
    delete[] a;
    delete[] b;
}

double* gendata::get_a()
{
    return a;
}

double* gendata::get_b()
{
    return b;
}
