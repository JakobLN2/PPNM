#ifndef HAVE_MCINT_H
#define HAVE_MCINT_H

#include"../include/vector.h"
#include<functional>
#include<random>
#include<vector>
#include<cmath>

std::tuple<double,double> plainMC(const std::function<double(vector)>&, vector, vector, int N);
std::tuple<double,double> quasiMC(const std::function<double(vector)>&, vector, vector, int N);
std::tuple<double,double> stratMC(const std::function<double(vector)>&, vector, vector, int N, int nmin = 4096);

#endif