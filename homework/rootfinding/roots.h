#include"../include/vector.h"
#include"../include/matrix.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

matrix jacobian(const std::function<vector(vector)>, const vector&, vector fx = vector({0.0}), vector dx = vector({0.0}));

vector newton(const std::function<vector(vector)>&, const vector&, double acc = 0.01, vector dx = vector({0,0}));