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
    std::cout << "Random " << n << " x " << n << " matrix with values [0,1]\n";
    A.print("A = ");
    
    
    std::cout << "\nEigendecomposition of A into V^T D V:\n";
    EVD evd(A);
    evd.cyclic();
    evd.V.print("V = ");
    evd.D.print("D = ");
    
    
    std::cout << "\nTests:\n";
    std::cout << "V^TV  ?= I : " << approx(transpose(evd.V) * evd.V, I) << "\n";
    std::cout << "VV^T  ?= I : " << approx(evd.V * transpose(evd.V), I) << "\n";
    
    matrix X = evd.V * (evd.D * transpose(evd.V));
    std::cout << "V^TAV ?= D : " << approx(transpose(evd.V)*(A * evd.V), evd.D) << "\n";
    std::cout << "VDV^T ?= A : " << approx(X,A) << "\n";
    



    return 0;
}