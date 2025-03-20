#include"qrsolver.h"

void QRSolver::decomp() {
    vector Qcol;
    for(int j = 0; j < A.ncols ; ++j) {
        Qcol = A.getCol(j);
        
        for(int k = 0 ; k < j ; ++k) {
            // Qcol -= proj(Q.getCol(k), A.getCol(j));
            R(k,j) = dot(Q.getCol(k), A.getCol(j));
            Qcol -= R(k,j) * Q.getCol(k);
        }
        R(j,j) = Qcol.norm();
        Qcol /= R(j,j);

        Q.setCol(j, Qcol);
    }
}
vector QRSolver::solve(const vector& b) const {
    vector x(A.ncols);
    vector QTb = transpose(Q) * b;
    double sum;
    for(int i = A.ncols - 1; i >= 0 ; --i) {
        sum = 0;
        for(int k = i + 1; k < A.ncols ; ++k) sum += R(i,k) * x[k];
        x[i] = 1/R(i,i) * (QTb[i] - sum);
    }
    return x;
}
matrix& QRSolver::inverse() {
    double sum;
    for(int j = 0; j < R.ncols ; ++j) { //Solve for R^- by backsubstitution column by column.
        Rinv(j,j) = 1/R(j,j);
        for(int i = j - 1; i >= 0; --i) {
            sum = 0;
            for(int k = i + 1; k < R.ncols ; ++k) sum += R(i,k) * Rinv(k,j);
            Rinv(i,j) = -1/R(i,i) * sum;
        }
    }
    B = Rinv * transpose(Q);
    return B;
}
// double QRSolver::det() {
//     double res = 1;
//     for(int i = 0; i < R.ncols ; ++i) res *= R(i,i);
//     return res;
// } 