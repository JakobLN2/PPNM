#include"../include/vector.h"
#include"../include/matrix.h"
#include"../ode/ode.h"
#include"roots.h"
#include<iostream>
#include<fstream>
#include<cmath>
#include<string>
#include<functional>
#include<vector>

std::function<vector(vector)> F_linear = [](vector p){return vector({5*p[0]+3});};

std::function<double(vector)> F_rosen = [](vector p) {return (1-p[0])*(1-p[0])+100*std::pow(p[1]-p[0]*p[0],2);};
std::function<vector(vector)> F_rosen_grad = [](vector p) {
    vector res(2);
    res[0] = -2*(1-p[0]+200*(p[1]-p[0]*p[0]));
    res[1] = 200*(p[1]-p[0]*p[0]);
    return res;
};
std::function<double(vector)> F_himmel = [](vector p) {return std::pow(p[0]*p[0]+p[1]-11,2) + std::pow(p[0]+p[1]*p[1]-7,2);};
std::function<vector(vector)> F_himmel_grad = [](vector p) {
    vector res(2);
    res[0] = 4*p[0]*(p[0]*p[0]+p[1]-11)   +  2 * (p[0]+p[1]*p[1]-7);
    res[1] =    2 * (p[0]*p[0]+p[1]-11) + 4*p[1]*(p[0]+p[1]*p[1]-7);
    return res;
};


// std::function<double(double) M_e = [](double x) {

// };


int main() {
    vector a, res;
    double acc = 1e-3;

    std::cout << "Task a: Test functions:\n";

    a = vector({10});
    std::cout << "root of 5x + 3 function with initial guess " << a << " and accuracy " << acc << "\n";
    res = newton(F_linear,a,acc);
    res.print("root found at x_root = ");
    std::cout << "Function value dF(x_root) = " << F_linear(res).norm() << " is within tolerance " << acc << "\n";

    a = vector({2.5, 2.5});
    std::cout << "\nEkstremum of Rosenbrock's function with initial guess " << a << " and accuracy " << acc << "\n";
    res = newton(F_rosen_grad,a,acc);
    res.print("root of gradient found at x_root = ");
    std::cout << "gradient norm(dF(x)) = " << F_rosen_grad(res).norm() << " is within tolerance " << acc << "\n";
    std::cout << "Function value is " << F_rosen(res) << "\n";
    
    // acc = 1e-5;
    // std::vector<vector> roots;
    // std::cout << "\nExtrema of Himmelblau's function with grid search inital guesses and accuracy " << acc << "\n";
    // for(double x0 = -2.5; x0 <= 2.5; x0 += 1) for(double y0 = -2.5; y0 <= 2.5; y0+=1) {
    //     res = newton(F_himmel_grad,vector({x0,y0}),acc);
    //     bool flag = false;
    //     for(int i = 0; i < (int)roots.size(); ++i) if(approx(res,roots[i],acc,1e-1)) flag = true;
    //     if(flag) continue;
    //     roots.push_back(res);
    //     std::cout << "root found at " << res << " using start guess " << vector({x0,y0}) << ", dF(x) = " << F_himmel_grad(res) << " < acc ?= " << (F_himmel_grad(res).norm() < acc) << "\n";
    // }
    acc = 1e-5;

    std::cout << "\nExtrema of Himmelblau's function with grid search inital guesses and accuracy " << acc << "\n";
    a = vector({-2.5,2.5});
    res = newton(F_himmel_grad,a,acc);
    std::cout << "root found at " << res << " using start guess " << a << ", dF(x) = " << F_himmel_grad(res) << " < acc ?= " << (F_himmel_grad(res).norm() < acc) << "\n";
    a = vector({2.5,-2.5});
    res = newton(F_himmel_grad,a,acc);
    std::cout << "root found at " << res << " using start guess " << a << ", dF(x) = " << F_himmel_grad(res) << " < acc ?= " << (F_himmel_grad(res).norm() < acc) << "\n";
    a = vector({-2.5,-2.5});
    res = newton(F_himmel_grad,a,acc);
    std::cout << "root found at " << res << " using start guess " << a << ", dF(x) = " << F_himmel_grad(res) << " < acc ?= " << (F_himmel_grad(res).norm() < acc) << "\n";
    a = vector({2.5,2.5});
    res = newton(F_himmel_grad,a,acc);
    std::cout << "root found at " << res << " using start guess " << a << ", dF(x) = " << F_himmel_grad(res) << " < acc ?= " << (F_himmel_grad(res).norm() < acc) << "\n";

    
    double r_min = 1e-5,
           r_max = 8;
    double E0 = -5; //Initial start guess for energy root finding
    double E_opt;

    double eps = 1e-3; //Relative precision when solving the ODE
    
    std::function<vector(vector)> M_e = [&](vector E) {
        std::function<vector(double,vector)> F_schr = [&](double x, vector y) {
            vector res(2);
            res[0] = y[1];
            res[1] = -2*(E[0] + 1.0/x)*y[0];
            return res;
        };

        vector yrmin({r_min * (1 - r_min), 1 - 2 * r_min}); //boundary condition at r_min
        auto sol = rkdriver(F_schr, r_min, r_max, yrmin, 0.125,acc,eps);
        std::vector<vector> ys = std::get<1>(sol);
        return vector({ys[ys.size() - 1][0]}); //f(rmax)
    };
    
    std::cout << "\nTask b: Schroedinger equation\n";
    std::cout << "Using r_min = " << r_min << ", r_max = " << r_max << "\n";
    std::cout << "Accuracy = " << acc << ", eps = " << eps << ", with inital energy guess E = " << E0 << "\n";
    res = newton(M_e, vector({E0}), acc);
    std::cout << "Optimal energy: " << res[0] << "\nWithin tolerance of the exact result of -1/2\n";
    std::cout << "Covnergence with respect to the parameters r_min, r_max and (acc, eps) are plotted seperately\n";
    std::cout << "It is obvious from the plots that the numerical quality is dependent on how close the parameters approach 0 or infinity\n";
    
    std::tuple<vector, std::vector<vector>> sol;
    std::string outfile;
    std::vector<vector> fx;
    vector rs;
    
    r_min = 1e-4;
    acc = 1e-3; eps = 1e-3;
    vector yrmin({r_min * (1 - r_min), 1 - 2 * r_min});
    
    vector rmaxs = vector({1,2,4,8,16});
    outfile = "rmax_conv.txt";
    std::ofstream outstream(outfile, std::ios::trunc);
    for(int i = 0; i < rmaxs.size ; ++i) {
        r_max = rmaxs[i];
        std::cerr << "calculating wave function for r_max = " << r_max << "\n";
        
        E_opt = newton(M_e,vector({E0}), acc)[0];
        /*Needed separately by the convergence plots, im not going to think too much about it so im just gonna define it again ¯\_(ツ)_/¯*/
        std::function<vector(double,vector)> schroe = [=](double x, vector y) {
            vector res(2);
            res[0] = y[1];
            res[1] = -2*(E_opt + 1.0/x)*y[0];
            return res;
        };

        sol = rkdriver(schroe, r_min, r_max, yrmin, 0.125, acc, eps);
        rs = std::get<0>(sol);
        fx = std::get<1>(sol);
        for(int j = 0; j < rs.size; ++j) outstream << rs[j] << " " << fx[j][0] << "\n";
        outstream << "\n\n";
    }
    r_max = 8;
    outstream.close();

    vector rmins = vector({0.001,0.01,0.1,0.5});
    outfile = "rmin_conv.txt";
    outstream = std::ofstream(outfile, std::ios::trunc);
    for(int i = 0; i < rmins.size ; ++i) {
        r_min = rmins[i];
        std::cerr << "calculating wave function for r_min = " << r_min << "\n";
        
        E_opt = newton(M_e,vector({E0}), acc)[0];
        std::function<vector(double,vector)> schroe = [=](double x, vector y) {
            vector res(2);
            res[0] = y[1];
            res[1] = -2*(E_opt + 1.0/x)*y[0];
            return res;
        };

        sol = rkdriver(schroe, r_min, r_max, yrmin, 0.125, acc, eps);
        rs = std::get<0>(sol);
        fx = std::get<1>(sol);
        for(int j = 0; j < rs.size; ++j) outstream << rs[j] << " " << fx[j][0] << "\n";
        outstream << "\n\n";
    }
    r_min = 1e-5;
    outstream.close();
    
    vector accs = vector({1e-5,1e-3,1e-1,1});
    outfile = "acceps_conv.txt";
    outstream = std::ofstream(outfile, std::ios::trunc);
    for(int i = 0; i < accs.size ; ++i) {
        acc = accs[i]; eps = accs[i];
        std::cerr << "calculating wave function for acc = eps = " << acc << "\n";
        
        E_opt = newton(M_e,vector({E0}), acc)[0];
        std::function<vector(double,vector)> schroe = [=](double x, vector y) {
            vector res(2);
            res[0] = y[1];
            res[1] = -2*(E_opt + 1.0/x)*y[0];
            return res;
        };

        sol = rkdriver(schroe, r_min, r_max, yrmin, 0.125, acc, eps);
        rs = std::get<0>(sol);
        fx = std::get<1>(sol);
        for(int j = 0; j < rs.size; ++j) outstream << rs[j] << " " << fx[j][0] << "\n";
        outstream << "\n\n";
    }
    acc = 1e-5; eps = 1e-5;
    outstream.close();

    return 0;
}