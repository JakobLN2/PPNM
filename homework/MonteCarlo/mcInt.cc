#include"mcInt.h"

std::tuple<double,double> plainMC(const std::function<double(vector)>& F, vector a, vector b, int N) {
    double V = 1;
    for(int i = 0; i < a.size ; ++i) V *= b[i] - a[i];
    
    // std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;
    std::vector<std::uniform_real_distribution<double>> unifs(a.size);
    for(int i = 0; i < a.size ; ++i) unifs[i] = std::uniform_real_distribution<double>(a[i],b[i]); 
    
    vector x(a.size);
    double fx,sum1 = 0,sum2 = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < a.size ; ++j) x[j] = unifs[j](re);
        fx = F(x);
        sum1 += fx;
        sum2 += fx*fx;
    }
    double mean = sum1/N;
    double variance = sum2/N-mean*mean;
    return std::make_tuple(V*mean, V * std::sqrt(variance/N));
}