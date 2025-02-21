#ifndef has_sfnus_h
#define has_sfuns_h

#include<cmath>
#include<functional>
#include<complex>
namespace sfuns{ 
    double erf(double);
    double gamma(double);
    double lngamma(double);
    std::complex<double> cgamma(std::complex<double>);
    

    //high level documentation example: should allegedly be in the header file, a lower level one may be in the source file
    /*
    * Numerically calculate a integral of a function in one variable from a to b via Simpson's 1/3 rule
    *
    * @param f (real) function in one variable to be integrated
    * @param a,b lower and upper limit
    * @param n number of subdivisions in Simpson's rule, must be an even number 
    *   2^18/x seems to be the upper limit before numerical precision ruins my life (where x is the xrange) [maybe; if segmentation fault, reduce n]
    * @return numerical integral value, there are no guarantees on accuracy since n is not infinite
    */
    double simpson_int(const std::function<double(double)>& f, double a, double b, int n = 1048576);
    bool approx(double a, double b,  double acc=1e-6, double eps=1e-6);
    unsigned int test_simpson_int(std::function<double(double)>, double, double, double);
    bool test_simpson_int_list();
}

#endif