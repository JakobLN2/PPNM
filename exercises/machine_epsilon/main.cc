#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

static bool approx(double a, double b, double acc = 1e-9, double eps = 1e-9) {
    if(std::abs(a - b) <= acc || 
        std::abs(a - b) <= std::max(std::abs(a), std::abs(b))*eps) return true;
    return false;


}

int main() {
    // //Task 1:
    // int i = 0;
    // while(i + 1 > i) {
    //     i++;
    // }
    // std::cout << "max int = " << i << std::endl;

    // i = 0;
    // while(i - 1 < i) {i--;}
    // std::cout << "min int = " << i << std::endl;
    
    // //Task 2:
    // double x = 1;
    // while(1+x != 1) {x /= 2;}
    // std::cout << "double machine epsilon = " << 2*x << std::endl;

    // float y = 1;
    // while((float)1 + y != 1) { y /= 2; }
    // std::cout << "float machine epsilon = " << 2*y << std::endl;

    // //Task 3:
    // double tiny = x/2;
    // double tiny = std::pow(2,-52);
    // double a = 1 + tiny + tiny;
    // double b = tiny + tiny + 1;

    // bool test1 = a == b;
    // bool test2 = a > 1;
    // bool test3 = b > 1;

    // std::cout << "a == b : " << test1 << std::endl;
    // std::cout << "a > 1 : " << test2 << std::endl;
    // std::cout << "b > 1 : " << test3 << std::endl;

    //Task 4:
    double d1 = 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1,
           d2 = 8 * 0.1;
    bool test4 = d1 == d2;
    std::cout << std::setprecision(16) << std::fixed; //Set 16 significant digits when printing
    std::cout << "d1 = " << d1 << "\nd2 = " << d2 << "\nd1 == d2 ?= " << test4 << std::endl;
    //d1 and d2 are not equal :(

    bool test5 = approx(d1, d2);
    std::cout << "d1 \\approx d2 ?= " << test5 << std::endl;

    return 0;
}