#include"roots.h"

matrix jacobian(const std::function<vector(vector)> F, const vector& x, vector fx, vector dx) {
    if(fx.isZeros()) fx = F(x);
    if(dx.isZeros()) dx = std::max(1.0, x.norm())*std::pow(2,-26);
    matrix J(x.size,x.size);
    for(int i = 0; i < x.size ; ++i) {
        vector df = F(x + dx) - fx;
        for(int j = 0; j < x.size; ++j) J(j,i) = df[i]/dx[j]; 
    }

    return J;
}


vector newton(const std::function<vector(vector)>& F, const vector& start, double acc, vector dx) {
    vector x = start.copy();
    vector fx = F(x);    

    return start;
}