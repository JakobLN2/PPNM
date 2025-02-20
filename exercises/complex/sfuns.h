#ifndef HAVE_SFUNS_H
#define HAVE_SFUNS_H

#include<complex>
namespace sfuns {
    bool approx(double, double, double acc=1e-6, double eps=1e-6);
    bool complex_approx(std::complex<double>, std::complex<double>, double acc=1e-6,double eps=1e-6);
};
#endif