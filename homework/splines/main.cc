#include"interp.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include"interp.h"
#include<random>
#include<iostream>
#include<cmath>
#include<string>

int main(int argc, char** argv) {
    std::string p = "";
    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-p" && i+1<argc) p = argv[i + 1];
    }
    
    int N = 10;
    vector xs(N), ys(N);
    for(int i = 0; i < N; ++i) {
        xs[i] = 10.0/N * i;
        ys[i] = std::cos(xs[i]);
    }
    
    std::cout << "Linear spline:\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 2pi: " << linterpInteg(xs, ys, 3.1415 * 2) << " expected approx: 0\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 0.5: " << linterpInteg(xs, ys, 0.5) << " expected exactly: " << 0.25*(1 + 1 + 0.5*(std::cos(1) - 1)) << " by explicit calcualtion\n"; //assuming there is no sample point between 0 and 0.5
    std::cout << "Integral of linear spline of cos(x) from 0 to 9: " << linterpInteg(xs, ys, 9) << "\n";

    std::cout << "\nQuadratic spline:\n";
    vector ys1(N), ys2(N), ys3(N);
    for(int i = 0; i < N; ++i) {ys1[i] = 1; ys2[i] = i; ys3[i] = i*i;}
    qspline inter1(xs,ys1);
    std::cout << "Coefficients for constant function f(x) = 1:\n";
    inter1.b.print("b = ");
    inter1.c.print("c = ");
    std::cout << "Expected b_i = 0, c_i = 0 for all i\n";
    
    qspline inter2(xs,ys2);
    std::cout << "\nCoefficients for linear function f(x) = x:\n";
    inter2.b.print("b = ");
    inter2.c.print("c = ");
    std::cout << "Expected b_i = 1, c_i = 0 for all i\n";
    
    qspline inter3(xs,ys3);
    std::cout << "\nCoefficients for quadratic function f(x) = x^2:\n";
    inter3.b.print("b = ");
    inter3.c.print("c = ");
    std::cout << "Expected b = [1,1,5,5,9,9,...] and c = [0,2,0,2,...]\n";


    if(p == "lin") {
        std::cout << "\n\n"; //Sampled points from cos(x):
        for(int i = 0; i < N; ++i) std::cout << xs[i] << " " << ys[i] << "\n";

        std::cout << "\n\n"; //Linear spline points for plotting:
        for(double i = 0; i <= 9 ; i += 1.0/8) std::cout << i << " " << linterp(xs, ys, i) << "\n";

        std::cout << "\n\n"; //Linear spline antiderivative for plotting:
        for(double i = 0; i <= 9 ; i += 1.0/8) std::cout << i << " " << linterpInteg(xs, ys, i) << "\n";
    }
    if(p == "quad") {
        qspline inter(xs,ys);

        std::cout << "\n\n"; //Sampled points from cos(x):
        for(int i = 0; i < N; ++i) std::cout << xs[i] << " " << ys[i] << "\n";

        std::cout << "\n\n"; //Quadratic spline points for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter(i) << "\n";

        std::cout << "\n\n"; //Quadratic spline derivative for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter.deriv(i) << "\n";

        std::cout << "\n\n"; //Quadratic spline antiderivative for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter.integ(i) << "\n";
        

    }

    if(p == "cubic") {
        cubspline inter(xs,ys);

        std::cout << "\n\n"; //Sampled points from cos(x):
        for(int i = 0; i < N; ++i) std::cout << xs[i] << " " << ys[i] << "\n";
        std::cout << "\n\n"; //cubic spline points for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter(i) << "\n";
        std::cout << "\n\n"; //Cubic spline derivative for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter.deriv(i) << "\n";
        std::cout << "\n\n"; //Cubic spline antiderivative for plotting:
        for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter.integ(i) << "\n";
        
        // std::cout << "\n\n"; //Sampled points from f(x) = 1:
        // for(int i = 0; i < N; ++i) std::cout << xs[i] << " " << ys[i] << "\n";
        // std::cout << "\n\n"; //Quadratic spline points for plotting:
        // for(double i = 0; i <= 9.0 ; i += 1/8.0) std::cout << i << " " << inter1(i) << "\n";
    }
    return 0;

}