#include"sfuns.h"
#include<iostream>
#include<functional>
#include<cmath>
#include<complex>
#include<fstream>
typedef std::complex<double> complex;

int main() {

    //task 1
    for(double x = -4; x <= 4; x += 1.0/8) {
        std::cout << x << " " << sfuns::erf(x) << "\n";
    }
    std::cout << "\n" << std::endl;
    
    //task 2
    double dx = 1.0/64;
    // The gamma function is not defined for non-positive integers, so we shift our start point half a step
    for(double x = -5 + dx/2; x <= 6.2; x += dx) {
        std::cout << x << " " << sfuns::gamma(x) << "\n";
    }
    std::cout << "\n" << std::endl;
    
    //task 3
    for(double x = dx; x <= 7; x += dx) {
        std::cout << x << " " << sfuns::lngamma(x) << "\n";
    }
    std::cout << "\n" << std::endl;
    
    //extra task
    std::ofstream outstream("3dData.txt", std::ios::trunc); 
    double da = 1.0/128,
           db = 1.0/32;
    for(double a = -5 + da/2; a <= 5; a += da) {
        for(double b = -3 + db/2 ; b <= 3 ; b += db) {
            outstream << a << " " << b << " " << std::abs(sfuns::cgamma(complex(a,b))) << "\n";
        }
        outstream << std::endl;
    }

    // sfuns::test_simpson_int_list(); // Passes the tests :)
    return 0;
}