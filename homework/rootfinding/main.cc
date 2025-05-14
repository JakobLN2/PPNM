#include"../include/vector.h"
#include"../include/matrix.h"
#include"roots.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>


std::function<vector(vector)> F_self = [](vector x){return x;}; //root at x = 0
std::function<vector(vector)> F_lin = [](vector x){return x - 1.0;}; //root at x = 1
std::function<vector(vector)> F_sphere = [](vector x){
    double val = x.norm();
    return vector({val,val,val});
}; //root at x = 0 (all elements)

int main() {
    vector a, res;

    // a = vector({15.0});
    // res = newton(F_lin,a,0.001);
    // res.print("res = ");
    
    // a = vector({2.5, 5.0, -6.0});
    // res = newton(F_sphere,a,0.001);
    // res.print("res = ");
    
    a = vector({2.5, 5.0, -6.0});
    res = newton(F_self,a,0.001);
    res.print("res = ");

    return 0;
}