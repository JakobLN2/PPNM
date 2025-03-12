#include"vector.h"
#include<iostream>
#include<string>
#include<stdexcept>
#include<assert.h>


int main() {
    vector a(3),
           b(3);
    std::cout << a.size << "\n";
    a[0] = 1.0; a[1] = 3.0; a[2] = 9.0;
    b[0] = 0.0; b[1] = 5.0; b[2] = 10.0;
    a.print("a = ");
    a *= 2.0;
    a.print("a*=2 : a = ");
    a /= 3.0;
    a.print("a/=3 : a = ");

    b.print("b = ");
    auto c = a + b;
    c.print("c = a + b = ");
    a.print("a = ");

    std::cout << "norm(a) = " << a.norm() << "\n";
    std::cout << "a * a = " << dot(a,a) << "\n";
    std::cout << "a * b = " << dot(a,b) << "\n";

    vector f(2); f[0] = 3; f[1] = 4;
    f.print("f = ");
    std::cout << "norm(f) = " << f.norm() << "\n";
    
    b[0] = 0.0; b[1] = -30.0; b[2] = 10.0;
    b.print("b = ");
    std::cout << "a * b = " << dot(a,b) << "\n";
    assert(std::abs(dot(a,b)) < 1e-6); 

    vector d(4); d[0] = 1.0; d[1] = 2.0; d[2] = 3.0; d[3] = 4.0;
    d.print("d = ");
    try {
        a += d;
    } catch(std::invalid_argument& e) {
        std::cout << "a += d is illegal :)\n";
    }
    try {
        a -= d;
    } catch(std::invalid_argument& e) {
        std::cout << "a -= d is illegal :)\n";
    }
    
    vector e;
    try {
        a + d;
    } catch(std::invalid_argument& e) {
        std::cout << "a + d  is illegal :)\n";
    }



    return 0;
}