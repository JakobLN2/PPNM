#ifndef HAVE_QUAD_H
#define HAVE_QUAD_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<exception>
#include<cmath>
#include<functional>
#include<tuple>
#include<string>

std::tuple<double,double, int> integrate(
    const std::function<double(double)>& F, double a, double b,
    double acc = 0.01, double eps = 0.01,
    double f2 = NAN, double f3 = NAN
);

std::tuple<double,double,int> integrate_CC(
    const std::function<double(double)>& F, double a, double b,
    double acc = 0.01, double eps = 0.01
);

#endif