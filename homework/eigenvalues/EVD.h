#ifndef HAVE_EVD_H
#define HAVE_EVD_H

#include"../include/matrix.h"
#include"../include/vector.h"

class EVD {
    public:
        matrix V, //Matrix of eigenvectors
               D; //Diagonal matrix of eigenvalues
            //    vector w; //vector of eigenvalues
        const matrix& M;
                
        EVD(const matrix& M_in) : M(M_in) {
            D = M_in.copy();
            V = identity(D.nrows);
            // w = vector(D.ncols);
        } // parametrized constructor


        EVD() = default; // default constructor
        EVD(const EVD&)=default; // copy constructor
        EVD(EVD&&)=default; // move constructor
        ~EVD()=default; // destructor
        EVD& operator=(const EVD&)=default; // copy assignment
        EVD& operator=(EVD&&)=default; // move assignment

        void timesJ(matrix&, int, int, double); //Multiply V with J from the right, update V
        void Jtimes(matrix&, int, int, double);
        void cyclic(); //Do cyclic sweeps over the matrix until convergence

};


#endif
