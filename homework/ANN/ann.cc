#include"ann.h"

double ann::eval(double x) {
    double res = 0;
    for(int i = 0; i < n; ++i) res += F_neuron(x,P.getRow(i));
    return res;
}

void ann::train(const vector& x, const vector& y) {
    std::function<double(vector)> F_cost = [&](vector p){
        double cost = 0;
        for(int i = 0; i < x.size ; ++i) {
            double res = 0;
            for(int j = 0; j < n; ++j) res += F_neuron(x[i], vector({p[3*j],p[3*j+1],p[3*j+2]}));
            cost += std::pow(res - y[i],2);
        }
        return cost;
    };
    std::cerr << "Training network with " << n << " neurons for " << x.size << " datapoints\n";
    
    std::uniform_real_distribution<double> unif(-1,1);
    std::default_random_engine re(5);
    
    vector p0(3*n);
    for(int i = 0; i < 3*n ; ++i) p0[i] = unif(re)*64; //Random start guess
    reshape(p0,n,3).print("p0 = ",std::cerr);
    std::cerr << "Initial cost: " << F_cost(p0) << "\n";


    std::tuple<vector,int> res = newton(F_cost,p0,1e-3,1);
    vector p_opt = std::get<0>(res);
    int N = std::get<1>(res);

    std::cerr << "Training complete in " << N << " iterations\nFinal cost: " << F_cost(p_opt) << "\n";
    
    P = reshape(p_opt, n, 3);
    P.print("P = ", std::cerr);
}