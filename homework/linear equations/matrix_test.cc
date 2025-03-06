#include"vector.h"
#include"matrix.h"
#include<iostream>
#include<string>


int main() {
    // vector a(3),
    //        b(3);
    // std::cout << a.size << "\n";
    // a[0] = 1.0; a[1] = 3.0; a[2] = 9.0;
    // b[0] = 0.0; b[1] = 5.0; b[2] = 10.0;
    // a.print("a = ");
    // a *= 2.0;
    // a.print("a*=2 : a = ");
    // a /= 3.0;
    // a.print("a/=3 : a = ");

    // b.print("b = ");
    // auto c = a + b;
    // c.print("c = a + b = ");
    // a.print("a = ");

    // std::cout << "norm(a) = " << a.norm() << "\n";
    // std::cout << "a * a = " << dot(a,a) << "\n";
    // std::cout << "a * b = " << dot(a,b) << "\n";
    
    // b[0] = 0.0; b[1] = -30.0; b[2] = 10.0;
    // b.print("b = ");
    // std::cout << "a * b = " << dot(a,b) << "\n";

    matrix a(2,3);
    std::cout << "matrix a is a " << a.nrows() << " x " << a.ncols() << " matrix\n";
    
    a.set(1,2,3.0);
    std::cout << "a[1][2] = " << a[1][2] << "\n";
    // a.print("a = ");
    a[1].print("a[1] = ");

    for(double elem : a.getRow(1)) std::cout << elem << ", ";
    std::cout << "\n";


    return 0;
}