#include"../include/matrix.h"
#include"../include/vector.h"
#include"ode.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::function<vector(double,vector)> harm = [](double x, const vector& y) {
    x += 1; //Cheat unused variable warning
    vector res(2);
    res[0] = y[1];
    res[1] = -y[0];
    return res;
};
std::function<vector(double,vector)> harm_damp = [](double x, const vector& y) {
    x += 1; //Cheat unused variable warning
    vector res(2);
    res[0] = y[1];
    res[1] = -(0.25*y[1] + 5.0 * std::sin(y[0]));
    return res;
};


std::function<vector(double,vector)> bessel = [](double x, const vector& y) {
    /* Differential equation for the radial part of the schrödinger equation for a free particle*/
    int l = 2;
    double alpha = l*(l-1);
    vector res(2);
    res[0] = y[1];
    res[1] = -(2*y[1]/x + (1 - alpha/x/x) * y[0]);
    return res;
};

std::function<vector(double,vector)> thirdOrder = [](double x, const vector& y) {
    /* y'' = 2x */
    vector res(2);
    res[0] = y[1];
    res[1] = 2*x;
    return res;
};

int main() {
    vector y0(2);
    vector y_last, y_analytic;
    double eps, acc, tol;
    double a,b;
    
    /*Harmonic oscillator*/
    y0[0] = 0.0; y0[1] = 1.0;
    acc = 0.01; eps = 0.01;
    a = 0.0, b = 10.0;
    std::tuple<vector, std::vector<vector>> res_harm = rkdriver(harm, a, b, y0, 0.125,acc,eps,2);
    vector xlist_harm = std::get<0>(res_harm);
    std::vector<vector> ylists_harm = std::get<1>(res_harm);
    y_last = ylists_harm[xlist_harm.size - 1];
    y_analytic = vector({std::sin(b), std::cos(b)});
    tol = acc + eps*y_analytic.norm();
    
    std::cout << "Harmonic oscillator y'' = -y from [" << a << ":" << b << "] with "; y0.print("y0 = ");
    std::cout << "Error from analytic solution: " << (y_last - y_analytic).norm() + (y_last - y_analytic).norm()/y_analytic.norm() << " promised tolerance: " << tol << "\n";

    // res_harm = rkdriver(harm, 0.0, 10.0, y0, 0.125,0.01,0.01,1);
    // vector xlist_harm_0 = std::get<0>(res_harm);
    // std::vector<vector> ylists_harm_0 = std::get<1>(res_harm);
    // std::cerr << "method=1 x size: " << xlist_harm_0.size << "\n";
    // std::cerr << "method=0 x size: " << xlist_harm.size << "\n";
    
    /*Damped harmonic oscillator (scipy odeint example)*/
    y0[0] = M_PI - 0.1; y0[1] = 0.0;
    a = 0.0, b = 10.0;
    acc = 0.005, eps = 0.005;
    std::tuple<vector, std::vector<vector>> res_dharm = rkdriver(harm_damp, a, b, y0, 0.125,acc,eps);
    vector xlist_dharm = std::get<0>(res_dharm);
    std::vector<vector> ylists_dharm = std::get<1>(res_dharm);


    /*Bessel function*/
    y0[0] = 0.0; y0[1] = 1.0;
    acc = 0.01, eps = 0.01;
    a = 0.0001, b = 15.0;
    std::tuple<vector, std::vector<vector>> res_bes = rkdriver(bessel, a, b, y0, 0.125,acc,eps,2);
    vector xlist_bes = std::get<0>(res_bes);
    std::vector<vector> ylists_bes = std::get<1>(res_bes);

    y_last = ylists_bes[xlist_bes.size - 1];
    y_analytic = vector({std::sin(b)/b/b - std::cos(b)/b, 2*std::cos(b)/b/b+std::sin(b)/b*(1-2/b/b)});
    tol = acc + eps*y_analytic.norm();

    std::cout << "\nRadial Schrödinger equation for a free particle y'' + 2y'/x + (1 - l(l-1)/x/x)y = 0 for l = 2 from [" << a << ":" << b << "] with "; y0.print("y0 = ");
    // std::cout << "absolute error from analytic solution: " << std::abs(ylast - y_analytic) << ", promised error: 0.01\n";
    // std::cout << "Relative error: " << std::abs(ylast - y_analytic)/std::abs(y_analytic) << ", promised error: 0.01\n";
    std::cout << "Error from analytic solution: " << (y_last - y_analytic).norm() + (y_last - y_analytic).norm()/y_analytic.norm() << " promised tolerance: " << tol << "\n";
 
    // /*y'' = 2x*/
    // y0[0] = 0.0; y0[1] = 0.0;
    // b = 5;
    // auto res_c1 = rkdriver(thirdOrder, 0.0, b, y0, 0.125,0.01,0.01);
    // vector xlist_c1 = std::get<0>(res_c1);
    // std::vector<vector> ylists_c1 = std::get<1>(res_c1);
    // // vector hlist = xlist_c1.diff();

    // ylast = ylists_c1[xlist_c1.size - 1][0];
    // y_analytic = b*b*b/3.0;

    // std::cout << "\nThird order pylonomial y'' = 2x from [0:" << b << "] with "; y0.print("y0 = ");
    // std::cout << "absolute error from analytic solution: " << std::abs(ylast - y_analytic) << ", promised error: 0.01\n";
    // std::cout << "Relative error: " << std::abs(ylast - y_analytic)/std::abs(y_analytic) << ", promised error: 0.01\n";
    // // hlist.print("Step sizes = ");


    std::cout << "\n\n";
    for(int i = 0; i < xlist_harm.size; ++i) std::cout << xlist_harm[i] << ", " << ylists_harm[i][0] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_harm.size; ++i) std::cout << xlist_harm[i] << ", " << ylists_harm[i][1] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_dharm.size; ++i) std::cout << xlist_dharm[i] << ", " << ylists_dharm[i][0] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_dharm.size; ++i) std::cout << xlist_dharm[i] << ", " << ylists_dharm[i][1] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_bes.size; ++i) std::cout << xlist_bes[i] << ", " << ylists_bes[i][0] << "\n";
    
    // std::cout << "\n\n";
    // for(int i = 0; i < xlist_c1.size; ++i) std::cout << xlist_c1[i] << ", " << ylists_c1[i][0] << "\n";

    
    return 0;
};
