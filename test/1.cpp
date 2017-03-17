#include <cmath>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

double f(double a, double b=1);

enum flagtype {ABC = 0, BCD = 1}; 

flagtype str2enum(string str)
{
    if (str.compare("ABC") == 0)
        return ABC;
    else if (str.compare("BCD") == 0)
        return BCD;
}

class efield
{
    private:
        double realpart, imagpart;

    public:
        efield();
        efield(string);
        efield(double &x, double &y);
        void set_efield(double &x, double &y);
        efield get_efield();
        double get_real();
        double get_imag();
        double get_phase();
        double get_amp();
        void dumpdata(std::ofstream &);
};

efield::efield()
{
    realpart = imagpart = 0;
}

efield::efield(string str)
{  
    size_t pos1 = str.find(",");
    istringstream sstr(str.replace(pos1,1," "));
    double a1,b1;
    sstr >> a1;
    sstr >> b1;
    realpart = a1;
    imagpart = b1;
}

efield::efield(double &x, double &y)
{
    realpart = x;
    imagpart = y;
}

void efield::set_efield(double &x, double &y)
{
    realpart = x;
    imagpart = y;
}

efield efield::get_efield()
{
    return efield(realpart, imagpart);
}

double efield::get_real()
{
    return realpart;
}

double efield::get_imag()
{
    return imagpart;
}

double efield::get_phase()
{
    return atan(imagpart/realpart);
}

double efield::get_amp()
{
    return sqrt(realpart*realpart+imagpart*imagpart);
}

void efield::dumpdata(std::ofstream &ofile)
{
    ofile << realpart << " + i" << imagpart << std::endl;
}


class doEx
{
    public:
        void set_Ex(double x, double y);
        efield get_Ex();
    private:
        efield Ex;
};

void doEx::set_Ex(double x, double y)
{
    Ex.set_efield(x, y);
}

efield doEx::get_Ex()
{
    return Ex;
}

efield str2efield(string str)
{
    size_t pos1 = str.find(",");
    istringstream sstr(str.replace(pos1,1," "));
    double a1,b1;
    sstr >> a1;
    sstr >> b1;
    return efield(a1,b1);
}

int main(int argc, char **argv)
{
    efield Ex;
    doEx *ins = new doEx;
    ins->set_Ex(0,-1);
    Ex = ins->get_Ex();
    cout << "realpart of Ex: " << Ex.get_real()  << endl;
    cout << "imagpart of Ex: " << Ex.get_imag()  << endl;
    cout << "phase of Ex: "    << Ex.get_phase() << endl;
    cout << "amp of Ex: "      << Ex.get_amp()   << endl;

    double x;
    double b(0);
    if (x = Ex.get_amp() > b) b = x;
    cout << x << endl;

    string str = "1,2";
    efield Ex1=str2efield(str);
    cout << Ex1.get_amp() << endl;

    efield *ExArr = new efield [2];
    ExArr[0] = efield("2,3");
    ExArr[1] = efield("3,4");
    cout << ExArr[0].get_amp() << endl;
    cout << ExArr[1].get_amp() << endl;

    string filename = "tmp";
    ofstream outfile1;
    outfile1.open(filename.c_str());
//    ofstream outfile1(filename.c_str());
//    ofstream outfile2(argv[1]);

    ExArr[0].dumpdata(outfile1);

    cout << f(2.0) << endl;
    

    flagtype myflag = str2enum("ABC");

    switch (myflag)
    {
        case ABC:
            cout << "strflag is ABC" << endl;
            cout << "strflag is ABC" << endl;
            break;
        case BCD:
            cout << "strflag is BCD" << endl;
            break;
        default:
            cout << "strflag is not correct" << endl;
    }

    bool ab = 4%2;

    cout << ab << endl;

    if (ab == 0)
        cout << "OK" << endl;


    return 0;
}

double f(double a, double b)
{
    return a+b;
}
