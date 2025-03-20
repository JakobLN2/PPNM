#include"../include/vector.h"
#include"../include/matrix.h"
#include"qrsolver.h"
#include<iostream>
#include<string>
#include<assert.h>
#include<random>

int main(int argc, char** argv) {
    int n = 3,
        m = 2;

    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];

        if(arg == "-n" && i+1<argc) n = std::stoi(argv[i + 1]);
        if(arg == "-m" && i+1<argc) m = std::stoi(argv[i + 1]);
    }
    
    std::cout << "matrix of shape " << n << "," << m << " with uniform random values (0,1):\n";
    matrix A(n,m);
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m ; ++j) A(i,j) = unif(re);
    }
    A.print("A = ");

    QRSolver fac(A);

    std::cout << "QR factorization of A:\n";
    fac.decomp();
    fac.Q.print("Q = ");
    fac.R.print("R = ");
    
    matrix Q2 = transpose(fac.Q) * fac.Q;
    // std::cout << "Check if Q^TQ = I:\n";
    // Q2.print("Q^TQ = ");
    matrix I = identity(m);
    std::cout << "Q^TQ ?= I : " << approx(Q2, I) << "\n";
    
    vector b(n);
    for(int i = 0; i < n ; ++i) b[i] = unif(re);
    b.print("b = ");

    vector x = fac.solve(b);
    std::cout << "Solution to system of linear equations Ax = b is:\n";
    x.print("x = ");
    
    vector Ax = A * x;
    Ax.print("Ax = ");
    std::cout << "Ax ?= b : " << approx(Ax, b) << "\n";

    std::cout << "Inverse of A:\n";
    matrix Ainv = fac.inverse();
    (Ainv * A).print("A^-1A = ");
    std::cout << "A^-1A ?= I : " << approx(Ainv*A, I) << "\n";

    return 0;
}