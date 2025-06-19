#include"minimizer.h"

std::tuple<vector,int> newton(std::function<double(vector)> F, vector start, double acc) {
    vector x = start.copy();
    int N = 0;

    do {
        vector gx = gradient(F,x);
        // gx.print("gradient = ");
        if(gx.norm() < acc) break;
        matrix Hx = hessian(F,x,gx);
        vector dx = QRSolver(Hx).solve(-gx);

        double l = 1,
               Fx = F(x);
        while(l >= 1.0/1024.0) {
            if(F(x + l*dx) < Fx) break;
            l /= 2.0; 
        }
        x += l*dx;
        N += 1;
    } while(N < 50000);

    // std::cout << "minimization completed in " << N << " iterations\n";
    return std::make_tuple(x,N);
}


vector gradient(const std::function<double(vector)>& F, vector x) {
    double Fx = F(x);
    vector dFx = vector(x.size);
    for(int i = 0; i < x.size ; ++i) {
        double dxi = (1 + std::abs(x[i])) * std::pow(2.0,-26);
        x[i] += dxi;
        dFx[i] = (F(x) - Fx)/dxi;
        x[i] -= dxi;
    }
    return dFx;
}


matrix hessian(const std::function<double(vector)> F, vector x, vector dFx) {
    matrix H(x.size, x.size);
    for(int i = 0; i < x.size; ++i) {
        double dxi = (1 + std::abs(x[i])) * std::pow(2.0,-13);
        x[i] += dxi;
        vector dFxi = gradient(F, x) - dFx;
        for(int j = 0; j < x.size ; ++j) H(j,i) = dFxi[j]/dxi;
        x[i] -= dxi;
    }
    return H;
}