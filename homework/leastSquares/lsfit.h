#ifndef HAVE_LSFIT_H
#define HAVE_LSFIT_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include"../linearEquations/qrsolver.h"
#include<functional>
#include<vector>
#include<tuple>

std::tuple<vector, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);


#endif
