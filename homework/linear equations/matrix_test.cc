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

    int nrows = 2,
        ncols = 3;
    matrix a(nrows, ncols);
    std::cout << "matrix a is a " << a.nrows() << " x " << a.ncols() << " matrix\n\n";

    //set method
    a.set(1,2,3.0);
    std::cout << "a[1][2] = " << a(1,2) << "\n\n";

    //print method
    a.print("a = ");
    std::cout << "\n";

    //getRow method
    for(int i = 0; i < 3 ; ++i) std::cout << a.getRow(1)[i] << ", ";
    std::cout << "\n\n";
    
    //setRow method
    a.setRow(0, a.getRow(0) += 2);
    std::cout << "a[0] += 2\n";
    a.print("a = ");
    
    //getCol method
    for(int i = 0; i < nrows ; ++i) std::cout << a.getCol(1)[i] << ", ";
    std::cout << "\n\n";
    //setCol method
    a.setCol(0, a.getCol(0) *= 1.5);
    std::cout << "a[:,0] *= 1.5\n";
    a.print("a = ");

    matrix b(nrows, ncols);
    b.print("b = ");
    b.setRow(0, (double[]){1,2,3});
    std::cout << "b[0] = [1,2,3]\n";
    b.print("b = ");

    return 0;
}