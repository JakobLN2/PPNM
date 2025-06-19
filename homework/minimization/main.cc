#include"../include/vector.h"
#include"../include/matrix.h"
#include"minimizer.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>
#include<fstream>



std::function<double(vector)> F_well_off = [](vector x){return std::pow(x[0] - 4,2) + std::pow(x[1] + 9,2);}; //Minimum at (4,-9)
std::function<double(vector)> F_rosen = [](vector x){return (1-x[0])*(1-x[0]) + 100*std::pow(x[1] - x[0]*x[0],2);}; //Minimum at (1,1)
std::function<double(vector)> F_himmel = [](vector x){return std::pow(x[0]*x[0]+x[1]-11,2) + std::pow(x[0]+x[1]*x[1]-7,2);}; //Minimum at (3,2)
std::function<double(vector)> F_beale = [](vector x){return std::pow(1.5-x[0]+x[0]*x[1],2) + std::pow(2.25 - x[0] + x[0]*x[1]*x[1],2) + std::pow(2.625 - x[0] + x[0]*x[1]*x[1]*x[1],2);}; //Minimum at (3,0.5)



int main(int argc, char** argv) {
    std::string infile = " ",
                outfile = "higgs_fit.txt";
    for(int i = 0; i < argc ; ++i) {
        std::string arg = argv[i];
        if(arg == "--input" && i+1 < argc) infile = argv[i + 1];
        if(arg == "--output" && i+1 < argc) outfile = argv[i + 1];
    }
    std::cout << "infile = " << infile << "\noutfile = " << outfile << "\n\n";


    std::tuple<vector,int> res;
    vector sol, x0;
    int N;

    std::cout << "Task A test functions:\n";
    x0 = vector({1,1});
    res = newton(F_well_off, x0);
    sol = std::get<0>(res);
    N = std::get<1>(res);
    std::cout << "Calculated minimum of (x - 4)^2 + (y + 9)^2 is at:\n" << sol << "\nExpected: in " << N << " iterations from x0 = " << x0 << "\n\n";
    
    x0 = vector({10,10});
    res = newton(F_rosen, x0);
    sol = std::get<0>(res);
    N = std::get<1>(res);
    std::cout << "Calculated minimum of Rosenbrock's function:\n" << sol << "\nExpected: (1,1) in " << N << " iterations from x0 = " << x0 << "\n\n";
    
    x0 = vector({10,10});
    res = newton(F_himmel, x0);
    sol = std::get<0>(res);
    N = std::get<1>(res);
    std::cout << "Calculated minimum of Himmelblau's function:\n" << sol << "\nExpected: (3,2) in " << N << " iterations from x0 = " << x0 << "\n\n";
    
    x0 = vector({3,0});
    res = newton(F_beale, x0);
    sol = std::get<0>(res);
    N = std::get<1>(res);
    std::cout << "Calculated minimum of Baele's function:\n" << sol << "\nExpected: (3,0.5) in " << N << " iterations from x0 = " << x0 << "\n\n";

    if(infile != " ") {
        std::cout << "Task b: Higgs data\n";
        double Ei, si, dsi;
        vector E, s, ds;
        std::ifstream instream(infile);
        while(instream >> Ei >> si >> dsi) {
            E.push_back(Ei);
            s.push_back(si);
            ds.push_back(dsi);
        }
        instream.close();

        std::function<double(double,vector)> F_bw = [](double e, vector p){return p[2] / (std::pow(e - p[0],2) + p[1]*p[1]/4);};
        std::function<double(vector)> F_D = [=](vector p){
            double d = 0;
            for(int i = 0; i < E.size ; ++i) d += std::pow((F_bw(E[i], p) - s[i]) / ds[i],2);
            return d;
        };
        x0 = {125,4,15};
        res = newton(F_D, x0, 1e-5);
        sol = std::get<0>(res);
        N = std::get<1>(res);

        std::cout << "Higgs fit with initial guess x0 = " << x0 << "\n" <<
                     "Optimal parameters (m, Γ, a) = " << sol << " in " << N << " iterations\n" <<
                     "Mass of Higgs boson is " << sol[0] << " GeV/c^2, Experimental width is " << sol[1] << " GeV\n" <<
                     "Requires a really good guess, otherwise diverges to god knows where\n";

        std::ofstream outstream(outfile, std::ios::trunc); //erase file contents before we write to it
        int n = 5000;
        double dx = (E[E.size - 1] - E[0])/n;
        double e = E[0];
        for(int i = 0; i < n ; ++i) {
            outstream << e << " " << F_bw(e,sol) << "\n";
            e += dx;
        }
    }

    return 0;
}