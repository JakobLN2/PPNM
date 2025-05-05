#include"../include/vector.h"
#include"mcInt.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

auto f_const = [](vector x){return 1;};
auto f_ucirc = [](vector x){
    if(x.norm() <= 1.0) return 1;
    else return 0;
};

auto f_coses = [](vector x) {
    if((0 <= x[0] && x[0] <= M_PI) ||
        (0 <= x[1] && x[1] <= M_PI) ||
        (0 <= x[2] && x[2] <= M_PI)) return 1/(1 - std::cos(x[0])*std::cos(x[1])*std::cos(x[2]));
    return 0.0;
};

int main() {
    vector a,b;
    int N;
    double q,err;
    double q_analytic;
    std::tuple<double,double> res;

    /* Constant function */
    a = vector({-1,-1,-1});
    b = vector({1,1,1});
    N = 1000;
    res = plainMC(f_const, a,b,N);
    q = std::get<0>(res);
    err = std::get<1>(res);
    std::cout << "∫_-1^1∫_-1^1∫_-1^1const = " << q << " +/- " << err << "\n"; 
    std::cout << "\twith " << N << " samples\n";

    
    /* Unit circle */
    a = vector({-1,-1});
    b = vector({1,1});
    N = 1e5;
    res = plainMC(f_ucirc, a,b,N);
    q = std::get<0>(res);
    err = std::get<1>(res);
    std::cout << "\n∫unit circle = " << q << " +/- " << err << ", expected: " << M_PI << "\n"; 
    std::cout << "\twith " << N << " samples\n";
    std::cout << "\t|MC - analytic| <= err ?= " << (std::abs(q - M_PI) <= err) << "\n";
    std::cout << "Error as a function of sample points is plotted in Plot.err.svg, the estimated error nicely follows a 1/sqrt(N) dependency.\n" <<
                "Though it seems underestimated for N <~ 1e5, where the law of large numbers may not have kicked in yet.\n";
    
    /* unit sphere */
    a = vector({-1.05,-1.05,-1.05});
    b = vector({1.05,1.05,1.05});
    N = 1e6;
    res = plainMC(f_ucirc, a,b,N);
    q = std::get<0>(res);
    err = std::get<1>(res);
    q_analytic = 4.0/3.0*M_PI;
    std::cout << "\n∫unit sphere = " << q << " +/- " << err << ", expected: " << q_analytic << "\n"; 
    std::cout << "\twith " << N << " samples\n";
    std::cout << "\t|MC - analytic| <= err ?= " << (std::abs(q - q_analytic) <= err) << "\n";
    
    /* unit sphere 4D*/
    a = vector({-1.05,-1.05,-1.05,-1.05});
    b = vector({1.05,1.05,1.05,1.05});
    N = 5e6;
    res = plainMC(f_ucirc, a,b,N);
    q = std::get<0>(res);
    err = std::get<1>(res);
    q_analytic = 0.5*M_PI*M_PI;
    std::cout << "\n∫4D unit sphere = " << q << " +/- " << err << ", expected: " << q_analytic << "\n"; 
    std::cout << "\twith " << N << " samples\n";
    std::cout << "\t|MC - analytic| <= err ?= " << (std::abs(q - q_analytic) <= err) << "\n";

    /*Task A integral*/
    a = vector({0,0,0});
    b = vector({M_PI, M_PI, M_PI});
    N = 1e8;
    res = plainMC(f_coses, a,b,N);
    q = std::get<0>(res) * std::pow(M_PI,-3);
    err = std::get<1>(res) * std::pow(M_PI,-3);
    q_analytic = 1.3932039296856768591842462603255;
    std::cout << "\n1/pi^3∫_0^pi dx∫_0^pi dy∫_0^pi dz [1-cos(x)cos(y)cos(z)]^-1 = " << q << " +/- " << err << ", expected: " << q_analytic << "\n";
    std::cout << "\twith " << N << " samples\n";
    std::cout << "\t|MC - tabulated| <= err ?= " << (std::abs(q - q_analytic) <= err) << "\n";

    std::cout << "\n\n";
    a = vector({-1,-1});
    b = vector({1,1});
    for(int i = 10; i < 25 ; ++i) {
        double N = std::pow(2,i);
        res = plainMC(f_ucirc, a,b,N);
        q = std::get<0>(res);
        err = std::get<1>(res);
        std::cout << N << ", " << err << ", " << std::abs(q - M_PI) << "\n";
    }
    return 0;
};
