#ifndef HAVE_INTERP_H
#define HAVE_INTERP_H

#include"../include/matrix.h"
#include"../include/vector.h"

int binsearch(vector, double);
double interp(vector, vector, double);

// class qspline {
//     public:
//         matrix V, A; //matrix of eigenvectors
//         matrix& M;
//         vector w; //vector of eigenvalues
        
//         // matrix B; //inverse of A, if we wish
        
//         EVD(matrix& M_in) : M(M_in) {
//             A = M_in.copy();
//             V = identity(A.nrows);
//             w = vector(V.ncols);
//         } // parametrized constructor


//         EVD() = default; // default constructor
//         EVD(const EVD&)=default; // copy constructor
//         EVD(EVD&&)=default; // move constructor
//         ~EVD()=default; // destructor
//         EVD& operator=(const EVD&)=default; // copy assignment
//         EVD& operator=(EVD&&)=default; // move assignment

//         void timesJ(matrix&, int, int, double); //Multiply V with J from the right, update V
//         void Jtimes(matrix&, int, int, double);
//         void cyclic(); //Do cyclic sweeps over the matrix until convergence

// };




#endif
