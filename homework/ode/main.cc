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
    double ylast, y_analytic;
    
    /*Harmonic oscillator*/
    y0[0] = 0.0; y0[1] = 1.0;
    std::tuple<vector, std::vector<vector>> res_harm = rkdriver(harm, 0.0, 10.0, y0, 0.125,0.01,0.01);
    vector xlist_harm = std::get<0>(res_harm);
    std::vector<vector> ylists_harm = std::get<1>(res_harm);
    ylast = ylists_harm[xlist_harm.size - 1][0];
    
    std::cout << "Harmonic oscillator y'' = -y from [0:10] with "; y0.print("y0 = ");
    std::cout << "absolute error from analytic solution: " << std::abs(ylast - std::sin(10.0)) << ", promised error: 0.01\n";
    std::cout << "Relative error: " << std::abs(ylast - std::sin(10))/std::abs(std::sin(10)) << ", promised error: 0.01\n";

    res_harm = rkdriver(harm, 0.0, 10.0, y0, 0.125,0.01,0.01,1);
    vector xlist_harm_0 = std::get<0>(res_harm);
    std::vector<vector> ylists_harm_0 = std::get<1>(res_harm);
    std::cerr << "method=1 x size: " << xlist_harm_0.size << "\n";
    std::cerr << "method=0 x size: " << xlist_harm.size << "\n";
    
    /*Damped harmonic oscillator (scipy odeint example)*/
    y0[0] = M_PI - 0.1; y0[1] = 0.0;
    std::tuple<vector, std::vector<vector>> res_dharm = rkdriver(harm_damp, 0.0, 10.0, y0, 0.125,0.005,0.005);
    vector xlist_dharm = std::get<0>(res_dharm);
    std::vector<vector> ylists_dharm = std::get<1>(res_dharm);
    // ylast = ylists_dharm[xlist_dharm.size - 1][0];
    // y_analytic = 

    // std::cout << "\nDamped harmonic oscillator y'' + 0.25y' + 5sin(y) = 0  from [0:10] \n";
    // std::cout << "absolute error from analytic solution: " << std::abs(ylast - std::sin(10.0)) << ", promised error: 0.005\n";
    // std::cout << "Relative error: " << std::abs(ylast - std::sin(10))/std::abs(std::sin(10)) << ", promised error: 0.005\n";

    /*Bessel function*/
    y0[0] = 0.0; y0[1] = 1.0;
    double b = 15.0;
    std::tuple<vector, std::vector<vector>> res_bes = rkdriver(bessel, 0.001, b, y0, 0.125,0.01,0.01);
    vector xlist_bes = std::get<0>(res_bes);
    std::vector<vector> ylists_bes = std::get<1>(res_bes);
    ylast = ylists_bes[xlist_bes.size - 1][0];
    y_analytic = std::sin(b)/b/b - std::cos(b)/b;

    std::cout << "\nRadial Schrödinger equation for a free particle y'' + 2y'/x + (1 - l(l-1)/x/x)y = 0 for l = 2 from [0:" << b << "] with "; y0.print("y0 = ");
    std::cout << "absolute error from analytic solution: " << std::abs(ylast - y_analytic) << ", promised error: 0.01\n";
    std::cout << "Relative error: " << std::abs(ylast - y_analytic)/std::abs(y_analytic) << ", promised error: 0.01\n";
 
 
    /*y'' = 2x*/
    y0[0] = 0.0; y0[1] = 0.0;
    b = 5;
    auto res_c1 = rkdriver_step(thirdOrder, 0.0, b, y0, 0.125,0.01,0.01);
    vector xlist_c1 = std::get<0>(res_c1);
    std::vector<vector> ylists_c1 = std::get<1>(res_c1);
    vector hlist = std::get<2>(res_c1);

    ylast = ylists_c1[xlist_c1.size - 1][0];
    y_analytic = b*b*b/3.0;

    std::cout << "\nThird order pylonomial y'' = 2x from [0:" << b << "] with "; y0.print("y0 = ");
    std::cout << "absolute error from analytic solution: " << std::abs(ylast - y_analytic) << ", promised error: 0.01\n";
    std::cout << "Relative error: " << std::abs(ylast - y_analytic)/std::abs(y_analytic) << ", promised error: 0.01\n";
    hlist.print("Step sizes = ");


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
    
    std::cout << "\n\n";
    for(int i = 0; i < xlist_c1.size; ++i) std::cout << xlist_c1[i] << ", " << ylists_c1[i][0] << "\n";

    
    return 0;
};
