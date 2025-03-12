#include"QRSolver.h"
#include"matrix.h"
#include"matrix.cc"
#include"vector.h"
#include"vector.cc"

void QRSolver::decomp() {
    matrix Qcol(A.nrows, 1);
    for(int j = 0; j < A.ncols ; ++j) {
        R(j,j) = 
        Qcol = A.getCol(j);
        for(int k = 1; k < j ; ++k)  Qcol -= Q.getCol(k); 

        Q.setCol(j, Qcol.normalize());
    }
}

void QRSolver::solve() {
    1 == 1;
}
void QRSolver::inverse() {
    1 == 1;
}
double QRSolver::det() {
    double res = 1;
    for(int i = 0; i < R.ncols ; ++i) res *= R(i,i);
    return res;
} 