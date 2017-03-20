#include <cmath>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    unsigned int N = 100000000;
    double s = 0;
    for (int i = 0; i < N; i++)
        s += sqrt(i);
    cout << s << endl;
    return 0;
}

