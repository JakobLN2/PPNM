#include<complex>
#include<iostream>

#include<math.h>
#include"sfuns.h"

int main() {
    std::complex<double> a;
    std::complex<double> test;
    std::string check;

    //sqrt(-1)
    a = std::sqrt(std::complex<double>(-1,0)); //It seemingly cannot promote to complex within the square root?
    test.real(0); test.imag(1);
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //sqrt(i)
    a = std::sqrt(std::complex<double>(0,1));
    test.real(std::cos(M_PI_4)); test.imag(std::sin(M_PI_4));
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //e^i
    a = std::exp(std::complex<double>(0,1));
    test.real(std::cos(1)); test.imag(std::sin(1));
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //e^i*pi
    a = std::exp(std::complex<double>(0,M_PI));
    test.real(-1); test.imag(0);
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //i^i 
        // i = e^i pi/2
        // i^i = e^(i pi/2)^i = e^(-pi/2)
    a = std::pow(std::complex<double>(0,1), std::complex<double>(0,1));
    test.real(std::exp(-M_PI_2)); test.imag(0);
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //ln(i)
        // i = e^i pi/2
        // ln(i) = i pi/2
    a = std::log(std::complex<double>(0,1));
    test.real(0); test.imag(M_PI_2);
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    //sin(i pi)
        // sin(x) = (e^ix - e^-ix)/2i
        // sin(i pi) = (e^-pi - e^pi)/2i = i/2 ( e^pi - e^-pi)
    a = std::sin(std::complex<double>(0,M_PI));
    test.real(0); test.imag((std::exp(M_PI) - std::exp(-M_PI))/2);
    check = sfuns::complex_approx(a, test) ? "passed" : "failed";
    std::cout << "sqrt(-1) = " << test << " ?= " << a << "  " << check << "\n";
    
    return 0;
}




