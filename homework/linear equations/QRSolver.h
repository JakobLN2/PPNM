#ifndef HAVE_QRSOLVER_H
#define HAVE_QRSOLVER_H

#include"matrix.h"
#include"matrix.cc"
#include"vector.h"

class QRSolver {
    public:
        matrix Q,
               R;
        matrix& A;
        
        QRSolver(matrix& A) : A(A) {
            Q = A.copy();
            R(A.ncols, A.ncols);
        } // parametrized constructor

        QRSolver() = default; // default constructor
        QRSolver(const QRSolver&)=default; // copy constructor
        QRSolver(QRSolver&&)=default; // move constructor
        ~QRSolver()=default; // destructor
        QRSolver& operator=(const QRSolver&)=default; // copy assignment
        QRSolver& operator=(QRSolver&&)=default; // move assignment

        void decomp(); //Calculate and set Q and R matrices
        void solve(); //Sovle a system of linear equations Ax = b
        void inverse(); //Calculate the inverse of A
        double det(); //Calculate the determinant of A

};


#endif
