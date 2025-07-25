#include"roots.h"

matrix jacobian(const std::function<vector(vector)> F, vector& x, vector fx, vector dx) {
    if(fx.isZeros()) fx = F(x);
    if(dx.isZeros()) {
        for(int i = 0; i < x.size ; ++i) dx[i] = std::max(1.0, std::abs(x[i]))*std::pow(2,-26);
    }
    matrix J(x.size,x.size);
    for(int i = 0; i < x.size ; ++i) {
        x[i] += dx[i];
        vector df = F(x) - fx;
        for(int j = 0; j < x.size; ++j) J(j,i) = df[j]/dx[i]; 
        x[i] -= dx[i];
    }

    return J;
}


vector newton(const std::function<vector(vector)>& F, const vector& start, double acc, vector dx) {
    vector x = start.copy();
    if(dx.isZeros()) dx = vector(x.size); //Ensure that dx is the same size as x 
    vector fx = F(x);
    vector f_step;

    while(true) {
        if(fx.norm() <= acc) break;
        matrix J = jacobian(F, x, fx, dx);
        QRSolver JQR(J);
        vector x_step = JQR.solve(-fx);
        double l = 1;
        while(l >= 1.0/128.0) {
            f_step = F(x + l*x_step);
            if(f_step.norm() < (1 - l/2)*fx.norm()) break;
            l /= 2;
        }
        x = x + l*x_step;
        fx = f_step;
    }

    return x;
}