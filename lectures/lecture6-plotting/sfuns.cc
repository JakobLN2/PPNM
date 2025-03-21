#include<cmath>
#include"sfuns.h" //Just to check that they match, check that the prototype is correct

namespace sfuns{ 
    double erf(double x) {
        return x;
    }

    //Call it f for float
    double gamma(double x) {
        if(x < 0)return M_PI/sin(M_PI*x)/gamma(1-x);
        if(x < 9)return gamma(x+1)/x;
        double lnfgamma=x*log(x+1/(12*x-1/x/10))-x+log(2*M_PI/x)/2;
        return exp(lnfgamma);
    }
} //namespace sfuns
