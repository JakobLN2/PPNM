#ifndef HAVE_SVD_H
#define HAVE_SVD_H

#include"../homework/include/vector.h"
#include"../homework/include/matrix.h"
#include"../homework/linearEquations/qrsolver.h"
#include<iostream>
#include<cmath>
#include<string>

class svd {
    public:
        matrix U, //Semi-ortogonal matrix spanning the non-vanishing singular values
               D, //Diagonal matrix of singular values
               V; //Orhogonal matrix spanning the null space of A
        const matrix& M; //Input matrix
        
        svd(const matrix& M_in) : M(M_in) {
            if(M_in.nrows == M_in.ncols) {
                D = M_in.copy();
                V = identity(D.nrows);
                U = identity(D.nrows);
                cyclic();
            } else if(M_in.nrows > M_in.ncols) {
                QRSolver qr(M_in);
                svd sol(qr.R);
                U = qr.Q*sol.U;
                D = sol.D;
                V = sol.V;
            } else throw std::invalid_argument("SVD factorization via QR cannot be performed for long matrices cols > rows");
        } // parametrized constructor

        svd() = default; // default constructor
        svd(const svd&)=default; // copy constructor
        svd(svd&&)=default; // move constructor
        ~svd()=default; // destructor
        svd& operator=(const svd&)=default; // copy assignment
        svd& operator=(svd&&)=default; // move assignment


        // void giv(matrix&, int, int, double); //Use givens rotation to symmetrize two diagonal elements
        
        void timesJ(matrix&, int, int, double); //In place multiplication of a matrix with J from the right
        void Jtimes(matrix&, int, int, double); //From the left
        void cyclic(); //Do cyclic sweeps over the matrix until convergence
        
        matrix p_inverse(); //Calculate the pseudo-inverse of input matrix M
};

#endif