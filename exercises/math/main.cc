#include<iostream>
#include<cmath>     //Here the <> marks means look at the system directory
#include"sfuns.h"   //Here the "" marks means look at the current directory

int main() {
    //Task 1
    std::cout << "Task 1" << std::endl;
    double a = std::sqrt(2);
    double b = std::pow(2, 0.2);
    double c = std::exp(M_PI);
    double d = std::pow(M_PI, std::exp(1));
    std::cout << "a^2 = " << a*a << " should be equal to 2" << std::endl;;
    std::cout << "b^5 = " << std::pow(b, 5) << " should be equal to 2" << std::endl;
    std::cout << "ln(c) = " << log(c) << " should be equal to pi" << std::endl;
    std::cout << "log_PI(d) = " << std::log(d)/std::log(M_PI) << " should be equal to e \n" << std::endl;

    //Task 2
    std::cout << "Task 2" << std::endl;
    for(int i = 1; i<=10; i++) {
        double gamma = sfuns::fgamma(i);
        std::cout << "Γ(" << i << ") = " << gamma << std::endl; 
    }
    std::cout << "" << std::endl;

    //Task 3
    std::cout << "Task 3" << std::endl;
    for(int i = 1; i<=10; i++) {
        double lngamma = sfuns::lngamma(i);
        std::cout << "Γ(" << i << ") = " << lngamma << std::endl; 
    }
    
    return 0;
}