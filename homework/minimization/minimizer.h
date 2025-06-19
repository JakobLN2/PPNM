#include"../include/vector.h"
#include"../include/matrix.h"
#include"../linearEquations/qrsolver.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::tuple<vector,int> newton(std::function<double(vector)>, vector, double acc=1e-3);

vector gradient(const std::function<double(vector)>&, vector);

matrix hessian(const std::function<double(vector)>, vector x, vector dFx);