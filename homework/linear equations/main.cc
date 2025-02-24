#include"vector.h"
#include<iostream>
#include<string>


int main() {
    vector<double> a(3),
                   b(3);
    std::cout << a.size << "\n";
    a[0] = 1; a[1] = 3; a[2] = 9;
    b[0] = 0; b[1] = 5; b[2] = 10;
    std::cout << a[0] << ", " << a[1] << ", " << a[2] << "\n";
    // a *= 2.0;
    // std::cout << a[0] << ", " << a[1] << ", " << a[2] << "\n";
    std::cout << b[0] << ", " << b[1] << ", " << b[2] << "\n";
    
    auto c = a + b;
    // std::cout << c[0] << ", " << c[1] << ", " << c[2] << "\n";
    a.print("a = ");
    // std::cout << a[0] << " " << a[1] << " " << a[2] << std::endl;
    // vector<double> b(3);
    // std::cout << a.size << " " << b.size << std::endl;

    return 0;
}