#include"vector.h"
#include"matrix.h"
#include<iostream>
#include<string>


int main() {
    vector a(3),
           b(3);
    std::cout << a.size << "\n";
    a[0] = 1; a[1] = 3; a[2] = 9;
    b[0] = 0; b[1] = 5; b[2] = 10;
    a.print("a = ");
    a *= 2.0;
    a.print("a*=2 : a = ");
    a /= 3.0;
    a.print("a/=3 : a = ");

    b.print("b = ");
    auto c = a + b;
    c.print("c = a + b = ");
    a.print("a = ");
    
    return 0;
}