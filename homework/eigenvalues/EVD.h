#ifndef HAVE_EVD_H
#define HAVE_EVD_H

#include"matrix.h"
#include"vector.h"

class EVD {
    public:
        matrix V; //matrix of eigenvectors
        matrix& A;
        vector w; //vector of eigenvalues
        
        matrix B; //inverse of A, if we wish
        
        EVD(matrix& A_in) : A(A_in) {
            V = A.copy();
            w = vector(A.ncols);
        } // parametrized constructor


        EVD() = default; // default constructor
        EVD(const EVD&)=default; // copy constructor
        EVD(EVD&&)=default; // move constructor
        ~EVD()=default; // destructor
        EVD& operator=(const EVD&)=default; // copy assignment
        EVD& operator=(EVD&&)=default; // move assignment

        void timesJ(int, int, double); //Multiply V with J from the right, update V
        void Jtimes(int, int, double);
        void cyclic(); //Do cyclic sweeps over the matrix until convergence

};


#endif
