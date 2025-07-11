#include"../include/matrix.h"
#include"../include/vector.h"
#include"ode.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>



std::function<vector(double,vector)> grMotion_eps(double eps) {
    std::function<vector(double,vector)> F = [=](double x, const vector& y) {
        /*Equatorial motion of a planet around a star in General Relativity*/
        vector res(2);
        res[0] = y[1];
        res[1] = 1 + y[0] * (eps*y[0] - 1);
        // res[1] = 1 + y[1] * (eps*y[1] - 1);
        return res;
    };
    return F;
}



int main() {
    vector y0(2);
    double a = 0.0,
           b = 25.0;
    double acc = 0.001,
           eps = 0.001;
   
    /*Circular orbit*/
    y0[0] = 1.0; y0[1] = 0.01;
    std::tuple<vector, std::vector<vector>> res_1 = rkdriver(grMotion_eps(0.0), a, b, y0, 0.125, acc,eps);
    vector xlist_1 = std::get<0>(res_1);
    std::vector<vector> ylists_1 = std::get<1>(res_1);
    
    /*Elliptical orbit*/
    y0[0] = 1.0; y0[1] = -0.5;
    std::tuple<vector, std::vector<vector>> res_2 = rkdriver(grMotion_eps(0.0), a, b, y0, 0.125,acc,eps);
    vector xlist_2 = std::get<0>(res_2);
    std::vector<vector> ylists_2 = std::get<1>(res_2);
    
    acc = 0.01; eps = 0.01;
    /*Relativistic precession of planetary orbit*/
    y0[0] = 1.0; y0[1] = -0.5;
    std::tuple<vector, std::vector<vector>> res_3 = rkdriver(grMotion_eps(0.1), a, b, y0, 0.125,acc,eps);
    vector xlist_3 = std::get<0>(res_3);
    std::vector<vector> ylists_3 = std::get<1>(res_3);
    

    for(int i = 0; i < xlist_1.size; ++i) std::cout << xlist_1[i] << ", " << ylists_1[i][0] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_2.size; ++i) std::cout << xlist_2[i] << ", " << ylists_2[i][0] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < xlist_3.size; ++i) std::cout << xlist_3[i] << ", " << ylists_3[i][0] << "\n";

    return 0;
};