#include"EVD.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<random>
#include<iostream>

int main(int argc, char** argv) {
    double n = 3;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];

        if(arg == "-n" && i+1<argc) n = std::stoi(argv[i + 1]);
    }

    matrix A(n,n),
           I = identity(n);
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    for(int i = 0; i < n; ++i) for(int j = 0; j < i + 1 ; ++j) {
        double val = unif(re);
        A(i,j) = val; 
        A(j,i) = val;
    }
        A.print("A = ");
    
    EVD evd(A);
    evd.cyclic();
    evd.V.print("V = ");

    matrix VTV = transpose(evd.V) * evd.V;
    VTV.print("V^TV = ");
    (evd.V * transpose(evd.V)).print("VV^T = ");

    std::cout << "\nV^TV ?= I : " << approx(VTV, I) << "\n";


    matrix X = transpose(evd.V) * (evd.A * evd.V);
    X.print("V^TAV = ");


    return 0;
}