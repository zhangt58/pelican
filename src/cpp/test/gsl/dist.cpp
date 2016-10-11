#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    const gsl_rng_type *T;
    gsl_rng *r;
    r = gsl_rng_alloc(gsl_rng_taus);
    gsl_rng_set(r,time(NULL));
    double sigma = 1;
    double mu = 10;
    int N = 20000;
    double *v = new double [N];
    for(int i = 0; i < N; i++)
    {
        v[i] = mu+gsl_ran_gaussian(r, sigma);
    }

    gsl_rng_free(r);

    for (int i = 0; i < N; i++)
        cout << v[i] << endl;
    return 0;
}

