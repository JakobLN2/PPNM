#include<iostream>
#include"sfuns.h"
int main() {
    for(double x = -3; x <= 3; x += 1.0/8) {
        std::cout << x << " " << sfuns::erf(x) << std::endl;
    }
    std::cout << "\n\n";
    
    double dx = 1.0/16;
    for(double x = -5 + dx/2; x <= 5; x += dx) {
        std::cout << x << " " << sfuns::gamma(x) << std::endl;
    }
    
    // for(double x = dx; x <= 10; x += dx) {
    //     std::cout << x << sfuns::gamma(x) << std::endl;
    // }

    return 0;
}