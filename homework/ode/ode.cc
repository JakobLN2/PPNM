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
std::tuple<vector, vector> rkstep12_midpoint(
    std::function<vector(double, vector)> F, 
    double h, double x, const vector y) {
    
    vector k0 = F(x, y);
    vector k1 = F(x + h/2, y + k0*h/2);

    vector dy_1 = k0*h;
    vector dy_2 = k1*h;
    return std::tuple(y + dy_2, dy_2 - dy_1);
}

std::tuple< vector , vector > rkstep3point
(std::function<vector(double,vector)> F,double h,double x,vector y ){
	double a=1.0/3,b=2.0/3;
	// double a=1.0/2,b=3.0/4;
	vector c ({0,a,b});
	vector a1({a,0,0});
	vector a2({b-b*b/2/a,b*b/2/a,0});
	vector G({1-1/a/2-1/b/b/3+1/a/b/3, 1/a/2-1/a/b/3, 1/b/b/3});
	vector B({1-1/a/2,1/a/2,0});
	vector k0 = F(x,y);
	vector k1 = F(x+c[1]*h,y+k0*(a1[0]*h));
	vector k2 = F(x+c[2]*h,y+k0*(a2[0]*h)+k1*(a2[1]*h));
	vector K = k0*G[0]+k1*G[1]+k2*G[2];
	vector k = k0*B[0]+k1*B[1]+k2*B[2];
	vector yh = y+K*h;
	vector er = (K-k)*h;
	return std::make_tuple(yh,er); }//rkstep23


// std::tuple<vector, vector, vector> rkstep34( //Bogacki-Shampine embedded method
//     std::function<vector(double, vector)> F, 
//     double h, double x, const vector y, vector k0) {
    
//     if(k0.isZeros()) k0 = F(x,y);
//     vector k1 = F(x + 1.0/2.0*h, y + 1.0/2.0*h*k0);
//     vector k2 = F(x + 3.0/4.0*h, y + 3.0/4.0*h*k1);
//     vector k3 = F(x + h , y + h*(2.0/9.0*k0 + 1.0/3.0*k1 + 4.0/9.0*k2));
    
//     vector dy_3 = h * (2.0/9.0*k0 + 1.0/3.0*k1 + 4.0/9.0*k2);
//     vector dy_2 = h * (7.0/24.0*k0 + 1.0/4.0 * k1 + 1.0/3.0*k2 + 1.0/8.0*k3);
    
//     // vector k3 = F(x + h, y + dy_3);
//     // vector dy_2 = h * (7.0/24.0*k0 + 0.25 * k1 + 1.0/3.0*k2 + 0.125*k3);
//     // vector dy_3 = h * k3;
//     return std::make_tuple(y + dy_3, dy_3 - dy_2, k3);
// }

std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0,
    double acc, double eps, int method
    ) {

    std::cerr << "driver: method=" << method << "\n";
    vector y = yinit.copy();
    double x = a, 
           h = h0;
    vector xlist;
    std::vector<vector> ylist;
    xlist.push_back(a); //Add initial point
    ylist.push_back(y);
    
    auto stepper = rkstep12;
    switch(method) {
        case 0:  stepper = rkstep12; break;
        case 1: stepper = rkstep3point; break;
        case 2: stepper = rkstep12_midpoint; break;
        // case 2:  stepper = rkstep23; break;
    }

    // if(method == 1) std::tuple<vector,vector,vector> res;
    // else std::tuple<vector,vector> res;
    // std::tuple<vector,vector,vector> res;
    // vector k(y.size);
    
    std::tuple<vector, vector> res;
    while(true) {
        if(x >= b) return std::make_tuple(xlist, ylist);
        if(x + h > b) h = b - x;

        res = stepper(F,h,x,y);
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
} //rkdriver
