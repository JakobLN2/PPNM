#include"../include/vector.h"
#include"../include/matrix.h"
#include<iostream>


int main() {
    matrix a(2,3);
    std::cout << "matrix a is a " << a.nrows << " x " << a.ncols << " matrix\n";
    
    //indexing
    a(1,2) = 3.0;
    std::cout << "a[1][2] = " << a(1,2) << "\n";
    a.print("a = ");
    
    //getRow and setRow
    a.setRow(1, 4.5);
    a.print("a[1][:] = 4.5 = ");
    vector testRow = a.getRow(1);
    testRow *= 2;
    a.setRow(0, testRow);
    a.print("a[0][:] = a[1][:] * 2 = ");

    try {
        matrix badRow(1,2);
        badRow.print("badRow = ");
        a.setRow(0, badRow);
    } catch(std::invalid_argument& e) {std::cout << "cannot insert badRow into matrix a :)\n";}

    vector testCol = a.getCol(2);
    testCol /= 8;
    a.setCol(0, testCol);
    a.print("a = ");


//     std::cout << "a[1][:] *= 2\n";
//     a.print("a = ");

//     std::cout << "a /= 3\n";
//     a /= 3;
//     a.print("a = ");

//     std::cout << "a(1,1) = " << a(1,1) << ", a(0,2) = " << a(0,2) << "\n";

//     matrix b(2,3);
//     b.setRow(0, 9.0); b.setRow(1, 0.01);
//     b.print("b = ");
//     matrix c = a + b;
//     c.print("c = a + b = ");
//     c = a - b;
//     c.print("c = a - b = ");
//     c = b * 2;
//     c.print("c = b * 2 = ");
//     c = 2 * b;
//     c.print("c = 2 * b = ");
//     c = a / 2;
//     c.print("c = a / 2 = ");
//     transpose(b).print("transpose(b) = ");

//     matrix d(2,2),
//             e(2,2);
//     d(0,0) = 1; d(1,1) = 1; d(1,0) = 0.5; d(0,1) = 0.5;
//     e.setRow(0,42); e.setRow(1,8);
//     d.print("d = ");
//     e.print("e = ");
//     matrix res = d * e;
//     res.print("res = d * e = ");

//     matrix f(2,3),
//             g(3,1);
//     f.setRow(0, 2.5); f(1,0) = 4; f(1,2) = 1;
//     f.print("f = ");
//     g(0,0) = 1; g(1,0) = 2; g(2,0) = 3;
//     g.print("g = ");
//     try{res = g * f;}
//     catch(std::invalid_argument& e) {std::cout << "g * f is illegal :)\n";}
//     res = f * g;
//     res.print("res = f * g = ");





    return 0;
}