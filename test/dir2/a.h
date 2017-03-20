#ifndef A_H_
#define A_H_

#include <complex>

class FELnumerical
{
    private:
        int npart;
        double gamma0, sigmag;
        double *psi, *gam; 
        std::complex <double> *cplxArr;
    public:
        FELnumerical(int N, double g0, double dg0);
        void gendis(double,double);
        double* get_psi();
        double* get_gam();
        int get_npart();

        double fmean();
};
  
double* normrand(int N, double mu, double sigma);

#endif // A_H_
