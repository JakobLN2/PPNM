#ifndef HAVE_QRSOLVER_H
#define HAVE_QRSOLVER_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<cmath>

class QRSolver {
    public:
        matrix Q,
               R;
        const matrix& A;
        matrix B; //inverse of A, if we wish
        matrix Rinv;
        
        QRSolver(const matrix& A_in) : A(A_in) {
            Q = A.copy();
            R = matrix(A.ncols, A.ncols);
            decomp();
            Rinv = matrix(R.nrows, R.nrows);
        } // parametrized constructor


        QRSolver() = default; // default constructor
        QRSolver(const QRSolver&)=default; // copy constructor
        QRSolver(QRSolver&&)=default; // move constructor
        ~QRSolver()=default; // destructor
        QRSolver& operator=(const QRSolver&)=default; // copy assignment
        QRSolver& operator=(QRSolver&&)=default; // move assignment

        void decomp(); //Calculate and set Q and R matrices
        vector solve(const vector&) const; //Sovle a system of linear equations Ax = b
        matrix& inverse(); //Calculate the inverse of A
        // double det(); //Calculate the determinant of A

};


#endif
