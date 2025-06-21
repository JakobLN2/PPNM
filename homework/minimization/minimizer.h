#ifndef HAVE_MINIMIZER_H
#define HAVE_MINIMIZER_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linearEquations/qrsolver.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::tuple<vector,int> newton(const std::function<double(vector)>&, vector, double acc=1e-3, int method=0);

vector gradient(const std::function<double(vector)>&, vector, int);

matrix hessian(const std::function<double(vector)>, vector, vector);

matrix centralHess(const std::function<double(vector)>, vector);

#endif