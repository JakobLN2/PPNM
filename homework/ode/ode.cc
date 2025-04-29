#include"ode.h"

std::tuple<vector, vector> rkstep12( //Heun-Euler embedded method
    std::function<vector(double, vector)> F, 
    double h, double x, const vector y) {
    
    vector k0 = F(x, y);
    vector k1 = F(x + h, y + k0*h);

    vector dy_1 = h * k0;
    vector dy_2 = 0.5 * h * (k0 + k1);
    return std::tuple(y + dy_2, dy_2 - dy_1);
}

std::tuple<vector, vector> rkstep23( //Bogacki-Shampine embedded method
    std::function<vector(double, vector)> F, 
    double h, double x, const vector y) {
    
    vector k0 = F(x, y);
    vector k1 = F(x + 0.5*h, y + 0.5*h*k0);
    vector k2 = F(x + 0.75*h, y + 0.75*h*k1);
    // vector k3 = F(x + h , y + h*(2.0/9.0*k0 + 1.0/3.0*k1 + 4.0/9.0*k2));

    vector dy_3 = h * (2.0/9.0*k0 + 1.0/3.0*k1 + 4.0/9.0*k2);;
    vector k3 = F(x + h, y + dy_3);
    vector dy_2 = h * (7.0/24.0*k0 + 0.25 * k1 + 1.0/3.0*k2 + 0.125*h*k3);
    
    // vector dy_2 = h * (7.0/24.0*k0 + 0.25 * k1 + 1.0/3.0*k2 + 0.125*k3);
    // vector dy_3 = h * k3;
    return std::tuple(y + dy_3, dy_3 - dy_2);
}

std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0,
    double acc, double eps
    ) {

    vector y = yinit.copy();
    double x = a, 
           h = h0;
    vector xlist;
    std::vector<vector> ylist;
    xlist.push_back(a); //Add initial point
    ylist.push_back(y);

    while(true) {
        if(x >= b) return std::make_tuple(xlist, ylist);
        if(x + h > b) h = b - x;

        std::tuple<vector,vector> res = rkstep23(F, h, x, y);
        vector yh = std::get<0>(res); //New y-value
        vector dy = std::get<1>(res); //Error estimate
        double tol = (acc + eps*yh.norm()) * std::sqrt(h/(b - a)); //Calculate tolerance based on step size
        double err = dy.norm();
        if(err <= tol){
            x += h; y = yh;
            xlist.push_back(x);
            ylist.push_back(y);
            }
        if(err>0) h *= std::min( std::pow(tol/err,0.25)*0.95 , 2.0); // readjust stepsize
        else h*=2.0;
    };
}

std::tuple<vector, std::vector<vector>, vector> rkdriver_step(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0,
    double acc, double eps
    ) {

    vector y = yinit.copy();
    double x = a, 
           h = h0;
    vector xlist, 
            hlist; //vector of accepted step sizes
    std::vector<vector> ylist;
    xlist.push_back(a); //Add initial point
    ylist.push_back(y);

    while(true) {
        if(x >= b) return std::make_tuple(xlist, ylist,hlist);
        if(x + h > b) h = b - x;

        std::tuple<vector,vector> res = rkstep23(F, h, x, y);
        vector yh = std::get<0>(res); //New y-value
        vector dy = std::get<1>(res); //Error estimate
        double tol = (acc + eps*yh.norm()) * std::sqrt(h/(b - a)); //Calculate tolerance based on step size
        double err = dy.norm();
        if(err <= tol){
            x += h; y = yh;
            xlist.push_back(x);
            ylist.push_back(y);
            hlist.push_back(h);
            }
        if(err>0) h *= std::min( std::pow(tol/err,0.25)*0.95 , 2.0); // readjust stepsize
        else h*=2.0;
    };
}