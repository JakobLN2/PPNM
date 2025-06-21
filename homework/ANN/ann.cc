#include"ann.h"

double ann::eval(double x) {
    double res = 0;
    for(int i = 0; i < n; ++i) res += F_neuron(x,P.getRow(i));
    return F_act(res);
}

void ann::train(const vector& x, const vector& y) {
    std::function<double(vector)> F_cost = [&](vector p){
        double cost = 0;
        for(int i = 0; i < x.size ; ++i) {
            double res = 0;
            for(int j = 0; j < 3*n; j += 3) res += F_neuron(x[i], vector({p[j],p[j+1],p[j+2]}));
            cost += std::pow(F_act(res) - y[i],2);
        }
        return cost;
    };
    std::cout << "1\n";
    vector p0 = vector(3*n) + 1;
    std::tuple<vector,int> res = newton(F_cost,p0,1e-2,0);
    vector p_opt = std::get<0>(res);
    std::cout << "2\n";
    
    for(int i = 0; i < 3*n; i += 3) P.setRow(i/3,vector({p_opt[i], p_opt[i+1],p_opt[i+2]}));
}