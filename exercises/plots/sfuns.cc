#include"sfuns.h"
#include<cmath>
#include<functional>
#include<string>
#include<iostream>
#include<complex>
typedef std::complex<double> complex;

namespace sfuns{ 
    double erf(double x) {
        const std::function<double(double)> erf_integrand = [=](double t){return std::exp(-t*t);};
        return 2/std::sqrt(M_PI) * simpson_int(erf_integrand, 0, x, std::pow(2,16));       
    }
    double gamma(double x) {
        //single precision gamma function (formula from Wikipedia)
        if(x < 0) return M_PI/sin(M_PI*x)/gamma(1-x);     //Euler's reflection formula
        if(x < 9) return gamma(x+1)/x;                   //Recurrence relation
        double lnfgamma = x*(log(x+1/(12*x-1/x/10)) - 1) + log(2*M_PI/x)/2; //Gergő Nemes algorithm

        return exp(lnfgamma);

            // Can also define it for numbers with a positive real part as an integral:
        // std::function<double(double)> gamma_integrand = [=](double t){return std::pow(t, x-1) * std::exp(-t);};
        // return simpson_int(gamma_integrand, 0, 10000, std::pow(2,18));
    }
    double lngamma(double x) {
        if(x <= 0) return nan("");
        if(x < 9) return lngamma(x+1) - log(x);
        double lnfgamma = x*(log(x+1/(12*x-1/x/10)) - 1) + log(2*M_PI/x)/2;
        return lnfgamma;
    }
    
    complex cgamma(complex x) {
        if(x.real() < 0) {
            return M_PI/sin(M_PI*x)/cgamma(complex(1.0 - x.real(), x.imag()));     //Euler's reflection formula
        }
        if(x.real() < 9) {
            return cgamma(complex(x.real() + 1.0, x.imag()))/x;                   //Recurrence relation
        }
        complex lnfgamma = x*log(x + 1.0/(12.0*x-1.0/x/10.0)) - x + log(2.0*M_PI/x)/2.0; //Gergő Nemes algorithm

        return exp(lnfgamma);
        // return x;
    }



    double simpson_int(const std::function<double(double)>& f, double a, double b, int n) {
        double h = (b - a)/n; //subdivision step length
        double xs[n + 1]; //x-values for subdivision borders
        
        for(int i = 0; i <= n ; ++i) xs[i] = a + h * i;
        //The last point is only weighed a factor 1, but the for-loop weighs it with a factor 2, subtract it once from the beginning.
        double res = f(a) - f(b); //integral value
        
        //loop over all subdivisions, evens have factor 2, odds have factor 4
        for(int i = 1; i < n ; i += 2) res += 4 * f(xs[i]) + 2 * f(xs[i+1]);
        return h/3 * res;
    }

    bool approx(double a, double b, double acc, double eps) {
        if(std::abs(a - b) <= acc || std::abs(a - b)/std::max(std::abs(a),(std::abs(b))) <= eps) {return true;}
            return false;
    }

    unsigned int test_simpson_int(std::function<double(double)> f, double a, double b, double test) {
        int n = 2;
        double val;
        double error;
        while(n < std::pow(2,30)) {
            val = simpson_int(f, a, b, n);
            error = test != 0 ? (val - test)/test : nan("");
            std::cerr << "n = " << n << ": " << val << " error: " << error <<"%\n";
            if(approx(val,test, 0.0001, 0.0001)) {
                return n;
            }
            n *= 2; //try more subdivisions
        }
        return 0;
    }

    bool test_simpson_int_list() {
        double test,
               a, b;
        bool pass = true;
        unsigned int n;
        std::string check;
        std::function<double(double)> f;

        //x^2
        a = -5.0 ; b = 10.0;
        f = [=](double x) {return x*x;};
        test = 1/3.0 * (std::pow(b, 3.0) - std::pow(a, 3.0));

        n = test_simpson_int(std::ref(f), a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "int_(" << a << ")^(" << b << ") x^2 = " << test << check << "\n";
        
        
        //e^2.1*x
        a = -5.0 ; b = 5.0;
        f = [=](double x) {return std::exp(2.1 * x);};
        test = 1/2.1 * (std::exp(2.1 * b) - std::exp(2.1 * a));
        
        n = test_simpson_int(f, a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "int_(" << a << ")^(" << b << ") e^2.1x = " << test << check << "\n";
        
        //1/x
        a = 0.0001 ; b = 5;
        f = [=](double x) {return 1/x;};
        test = std::log(b) - std::log(a);
        
        n = test_simpson_int(f, a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "int_(" << a << ")^(" << b << ") 1/x = " << test << check << "\n";
        
        //cos(x)
        a = 0; b = M_PI;
        f = [=](double x) {return std::cos(x);};
        test = 0;
        
        n = test_simpson_int(f, a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "int_(" << a << ")^(" << b << ") cos(x) = " << test << check << "\n";
        
        //1/sqrt(2pi)*e^(-1/2 * x^2)
        a = -1000; b = 1000;
        f = [=](double x) {return std::pow(2*M_PI, -0.5) * std::exp(-std::pow(x,2)/2);};
        test = 1;
        
        n = test_simpson_int(f, a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "int_(" << a << ")^(" << b << ") 1/sqrt(2pi)*e^(-1/2 * x^2) = " << test << check << "\n";
        
        // erf(1)
        a = 0; b = 1;
        f = [=](double x) {return std::exp(-x*x);};
        test = 0.842700793 * std::sqrt(M_PI)/2;
        
        n = test_simpson_int(f, a, b, test);
        if(n == 0) {check = " failed";} else {check = " passed in " + std::to_string(n) + " subdivisions";}
        std::cerr << "sqrt(pi)/2 * erf(" << b << ") = " << test << check << "\n";
        return pass;
    }

    
} //namespace sfuns
