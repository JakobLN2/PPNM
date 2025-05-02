#include"quad.h"

std::tuple<double,double, int> integrate(
    const std::function<double(double)>& F, double a, double b,
    double acc, double eps,
    double f2, double f3
) {
    int evals = 2;
    double h = b - a;
    if(std::isnan(f2)) {
        f2 = F(a + 2.0*h/6.0);
        f3 = F(a + 4.0*h/6.0);
        evals += 2;
    }
    double f1 = F(a + h/6.0);
    double f4 = F(a + 5.0*h/6.0);
    
    double Q = (2.0*f1 + f2 + f3 + 2.0*f4)/6.0 * h;
    double q = (f1 + f2 + f3 + f4)/4.0 * h;
    double err = std::abs(Q - q);
    double tol = acc + eps * std::abs(Q);
    if(err <= tol) return std::make_tuple(Q,err,evals);
    else {
        auto inte1 = integrate(F,a,(a + b)/2.0,acc/std::sqrt(2.0),eps,f1,f2);
        auto inte2 = integrate(F,(a + b)/2.0,b,acc/std::sqrt(2.0),eps,f3,f4);
        double inte = std::get<0>(inte1) + std::get<0>(inte2);
        double err1 = std::get<1>(inte1), err2 = std::get<1>(inte2);
        double err = std::sqrt(err1*err1 + err2*err2);
        int eval_fin = evals + std::get<2>(inte1) + std::get<2>(inte2);

        return std::make_tuple(inte, err, eval_fin);
    }
};


std::tuple<double,double,int> integrate_CC(
    const std::function<double(double)>& F, double a, double b,
    double acc, double eps
) {
    if(a == b) {return std::make_tuple(0.0, 0.0, 0);}
    if(std::isinf(a) && std::isinf(b)) {
        std::function<double(double)> integrand = [&](double t) {
            // return std::sin(t) * F(std::cos(t) * (1 + std::cos(t)*std::cos(t))/std::pow(std::sin(t),4));
            return F(std::cos(t)/std::sin(t)/std::sin(t)) * (1 + std::cos(t)*std::cos(t))/std::pow(std::sin(t),3);
        };
        return integrate(integrand, 0.0, M_PI, acc, eps);
        
    // } else if(std::isinf(a)) {
    } else if(std::isinf(b)) {
        std::function<double(double)> integrand = [&](double t) {
            return F(a + (1 + std::cos(t))/(1 - std::cos(t))) * 2*std::sin(t)/std::pow(1 - std::cos(t),2);
        };
        return integrate(integrand, 0.0, M_PI, acc, eps);

    } else {
        std::function<double(double)> integrand = [&](double t){
            return F((a + b)/2 + (b - a)/2*std::cos(t))*std::sin(t)*(b - a)/2;
        };
        return integrate(integrand, 0, M_PI, acc, eps);
    }
    
    
};
