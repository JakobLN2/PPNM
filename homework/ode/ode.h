#ifndef HAVE_ODE_H
#define HAVE_ODE_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<exception>
#include<cmath>
#include<functional>
#include<tuple>


// class rungeKutta {
//     public:
//         std::function<vector(double, vector)> F;
                
        
//         rungeKutta(std::function<vector(double, vector)>) : F(F) {
//             // b = vector(x.size - 1);
//             // c = vector(x.size - 1);
//             // buildSpline();
//         } // parametrized constructor


//         rungeKutta() = default; // default constructor
//         rungeKutta(const rungeKutta&)=default; // copy constructor
//         rungeKutta(rungeKutta&&)=default; // move constructor
//         ~rungeKutta()=default; // destructor
//         rungeKutta& operator=(const rungeKutta&)=default; // copy assignment
//         rungeKutta& operator=(rungeKutta&&)=default; // move assignment

//         std::pair<vector, vector> rkstep12

// };

std::tuple<vector, vector> rkstep12(
    std::function<vector(double, vector)> F, 
    double h, double x, vector y);

std::tuple<vector, std::vector<vector>> rkdriver(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0 = 0.125,
    double acc = 0.01, double eps = 0.01
    );
std::tuple<vector, std::vector<vector>, vector> rkdriver_step(
    std::function<vector(double, vector)> F,
    double a, double b,
    vector yinit,
    double h0 = 0.125,
    double acc = 0.01, double eps = 0.01
    );

#endif
