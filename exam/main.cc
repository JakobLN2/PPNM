#include"../homework/include/vector.h"
#include"../homework/include/matrix.h"
#include"svd.h"
#include<iostream>
#include<cmath>
#include<string>
#include<random>


int test(int n, int m) {
    matrix A(n,m);
    std::uniform_real_distribution<double> unif(0,1);
    std::default_random_engine re(n*m);

    for(int i = 0; i < A.nrows; ++i) for(int j = 0; j < A.ncols ; ++j) {
        double val = unif(re);
        A(i,j) = val; 
    }
    std::cout << "Testing svd algorithm for matrix of size " << n << " x " << m << " with random values in [0,1]\n";
    if(m != n) std::cout << "The algorithm has been expanded for use with tall matrices, but remains the 'economical version', examples online give the SVD for tall matrices as\n" <<
                            "A is a tall matrix n x m, then\n\tU is a large square matrix of size n x n\n\tD is a tall matrix n x m\n\tV is a small square matrix m x m\n" <<
                            "However, in this implementation the additional elements are neglected\n";
    A.print("A = ");
    std::cout << "\nSVD factorization into A = UDV^T, where:\n" <<
                 "\tU : Semi-orthogonal matrix spanning the range of the matrix A\n" <<
                 "\tD : Diagonal matrix containing the singular values\n" <<
                 "\tV : Orthogonal matrix spanning the null space of A\n";

    svd sol(A);
    sol.U.print("U = ");
    sol.D.print("D = ");
    sol.V.print("V = ");

    std::cout << "\nThe pseudo-inverse of A can be found using SVD as A^- = V(S^-)U^T\n";
    matrix A_inv = sol.p_inverse(); //Pseudo-inverse of A
    A_inv.print("A^- = ");
    std::cout << "Expect that the pseudoinverse A^- fulfills: A(A^-)A = A:\n";
    (A*A_inv*A).print("A(A^-)A = ");
    std::cout << "A(A^-)A ?= A == " << approx(A*A_inv*A,A) << "\n\n";

    std::cout << "Pseudoinverse can give the least squares solution to the overdetermined system Ax = b\n" <<
                 "Random vector with entires in [0,8]:\n";
    vector b(A.nrows);
    for(int i = 0; i < b.size; ++i) b[i] = unif(re)*8;
    b.print("b = ");
    std::cout << "Solution to the system of equations:\n";
    (A_inv*b).print("x = ");
    std::cout << "\n\n\n";
    return 0;
}

int test2() {
    matrix A(3,3);
    A.setRow(0, vector({3,8,1})); //Singular matrix
    A.setRow(1, vector({-4,1,1}));
    A.setRow(2, vector({-4,1,1}));

    std::cout << "Testing svd algorithm for a singular matrix of size 3 x 3 with\n";
    A.print("A = ");
    std::cout << "\n";

    svd sol(A);
    sol.U.print("U = ");
    sol.D.print("D = ");
    sol.V.print("V = ");

    std::cout << "\nThe pseudo-inverse of A can be found using SVD as A^- = VS^-U^T\n";
    matrix A_inv = sol.p_inverse(); //Pseudo-inverse of A
    A_inv.print("A^- = ");
    std::cout << "Expect that the pseudoinverse A^- fulfills: A(A^-)A = A:\n";
    (A*A_inv*A).print("A(A^-)A = ");
    std::cout << "A(A^-)A ?= A == " << approx(A*A_inv*A,A) << "\n";

    std::cout << "\nThe columns of V correspond to the null space, such that it is expected that AV_i = 0 for the vanishing singular values D_ii = 0\n" <<
                 "where V_i corresponds to column i of V. Any linear combination of such columns obviously works as well:\n";
    int D_0 = 0;
    for(int i = 0; i < sol.D.nrows; ++i) if(sol.D(i,i) < 1e-10) {
        D_0 = i;
        break;
    }
    std::cout << "AV_" << D_0 << " = ";
    vector x = A*sol.V.getCol(D_0);
    std::cout << x << " ?= 0 : " << approx(x, vector(x.size)) << "\n";
    std::cout << "\n\n";
    return 0;
}

int main(int argc, char** argv) {
    int n = 0,
        m = -1;

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-n" && i+1<argc) n = std::stoi(argv[i + 1]);
        if(arg == "-m" && i+1<argc) m = std::stoi(argv[i + 1]);
    }
    if(m == -1) m = n; //m was not given -> assume square matrix

    if(n > 0) return test(n,m);
    else return test2();


    return 0;
}