#ifndef HAVE_MCINT_H
#define HAVE_MCINT_H

#include"../include/vector.h"
#include<functional>
#include<random>
#include<vector>
#include<cmath>

std::tuple<double,double> plainMC(const std::function<double(vector)>&, vector, vector, int N);

#endif