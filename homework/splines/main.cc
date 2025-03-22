#include"interp.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include"interp.h"
#include<random>
#include<iostream>
#include<cmath>

int main() {
    int N = 10;
    vector xs(N), ys(N);
    for(int i = 0; i < N; ++i) {
        xs[i] = 10.0/N * i;
        ys[i] = std::cos(10.0/N * i);
    }
    
    std::cout << "Integral of linear spline of cos(x) from 0 to 2pi: " << linterpInteg(xs, ys, 3.1415 * 2) << " expected approx: 0\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 0.5: " << linterpInteg(xs, ys, 0.5) << " expected exactly: " << 0.25*(1 + std::cos(0.5)) << "\n";
    std::cout << "Integral of linear spline of cos(x) from 0 to 9: " << linterpInteg(xs, ys, 9) << "\n";

    
    std::cout << "\n\n";
    for(int i = 0; i < N; ++i) std::cout << xs[i] << " " << ys[i] << "\n";
    std::cout << "\n\n";
    for(double i = 0; i <= 9 ; i += 0.25) {
        std::cout << i << " " << linterp(xs, ys, i) << "\n";
    }

    return 0;
}