#ifndef HAVE_ODE_H
#define HAVE_ODE_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<exception>
#include<cmath>
#include<functional>
#include<tuple>
#include<string>



std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> F, 
    double h, double x, vector y);

std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0 = 0.125,
    double acc = 0.01, double eps = 0.01, int method = 1
    );

#endif