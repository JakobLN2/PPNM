#include"lsfit.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<iostream>
#include<vector>
#include<functional>
#include<cmath>

int main() {
    std::vector<double> t = {1,2,3,4,6,9,10,13,15},
                        y = {117,100,88,72,53,29.5,25.2,15.2,11.1},
                        dy= {6,5,4,4,4,3,3,2,2};
    
    std::vector<double> logy(y.size()),
                        logdy(y.size());

    //equation is ln(a) - l*t, so f_1 = const, f_2 = -t
    std::vector<std::function<double(double)>> f = {
        [](double t) {return 1.0;},
        [](double t) {return -t;}
    };
    
    for(int i = 0; i < (int)y.size(); ++i) {
        logy[i] = std::log(y[i]);
        logdy[i] = dy[i]/y[i];
    }

    auto res =  lsfit(f, t, logy, logdy);
    vector par = std::get<0>(res);
    matrix cov = std::get<1>(res);

    std::cout << "Optimal parameters (a, lambda):\n";
    par.print("par = ");
    cov.print("cov = ");
    std::cout << "parameter errors: " << std::sqrt(cov(0,0)) 
    double half_life = std::log(2)/par[1];
    double half_life_err = std::log(2)/par[1]/par[1] * std::sqrt(cov(1,1)); //Error calculated by the law of accumulation
    std::cout << "ThX has measured half life : " << half_life << " +/- " << half_life_err << " days\n";
    std::cout << "224Ra has half life : 3.6319 +/- days" << "\n";
    std::cout << "The experimental data is " << (half_life - 3.6319)/half_life_err << " standard deviations from the modern value\n";
    return 0;
}