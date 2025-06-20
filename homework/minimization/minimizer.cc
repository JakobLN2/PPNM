#include"minimizer.h"

std::tuple<vector,int> newton(std::function<double(vector)> F, vector start, double acc, int method) {
    if(method != 0 && method != 1) throw std::invalid_argument("unknown method " + std::to_string(method) + "\n0 for forward difference\n1 for central difference\n");
    vector x = start.copy();
    int N = 0;

    do {
        vector gx = gradient(F,x,method);
        if(gx.norm() < acc) break;

        matrix Hx(x.size, x.size);
        if(method == 0) Hx = hessian(F,x,gx);
        else if(method == 1) Hx = centralHess(F,x);

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

    return std::make_tuple(x,N);
}


vector gradient(const std::function<double(vector)>& F, vector x, int method) {
    vector dFx = vector(x.size); //Gradient at the point x
    double dxi, Fp;
    if(method == 0) {
        for(int i = 0; i < x.size ; ++i) {
            dxi = (1 + std::abs(x[i])) * std::pow(2.0,-26);
            x[i] += dxi;  Fp = F(x);
            x[i] -= dxi;
            dFx[i] = (Fp - F(x))/dxi;
        }
    } else if(method == 1) {
        double Fn;
        for(int i = 0; i < x.size ; ++i) {
            dxi = (1 + std::abs(x[i])) * std::pow(2.0,-26);
            x[i] += dxi;   Fp = F(x);
            x[i] -= 2*dxi; Fn = F(x);
            x[i] += dxi;
            dFx[i] = (Fp - Fn)/2/dxi;
        }
    }
    return dFx;
}

matrix hessian(const std::function<double(vector)> F, vector x, vector dFx) {
    matrix H(x.size, x.size);
    for(int i = 0; i < x.size; ++i) {
        double dxi = (1 + std::abs(x[i])) * std::pow(2.0,-13);
        x[i] += dxi;
        vector ddFxi = gradient(F, x,0) - dFx;
        for(int j = 0; j < x.size ; ++j) H(j,i) = ddFxi[j]/dxi;
        x[i] -= dxi;
    }
    return H;
}

matrix centralHess(const std::function<double(vector)> F, vector x) {
    matrix H(x.size, x.size);
    double Fpp, Fnp, Fpn, Fnn;
    double dxi, dxj;

    for(int i = 0; i < x.size; ++i) { 
        dxi = (1 + std::abs(x[i])) * std::pow(2.0,-13);
        
        x[i] += 2*dxi; Fpp = F(x);
        x[i] -= 4*dxi; Fnn = F(x);
        x[i] += 2*dxi;
        H(i,i) = (Fpp-2*F(x)+Fnn)/4/dxi/dxi; //Hessian is symmetric so we first calculate the diagonal

        for(int j = i + 1; j < x.size; ++j) { //Calculate the upper triangle
            dxj = (1 + std::abs(x[j])) * std::pow(2.0,-13);
            x[i] += dxi; x[j] += dxj; Fpp = F(x);
            x[i] -= 2*dxi;            Fnp = F(x);
            x[j] -= 2*dxj;            Fnn = F(x);
            x[i] += 2*dxi;            Fpn = F(x);
            x[i] -= dxi; x[j] += dxj;
            
            H(i,j) = (Fpp - Fnp - Fpn + Fnn)/4/dxi/dxj;
            H(j,i) = H(i,j); //Hesian is symmetric
        }
    }
    return H;
}