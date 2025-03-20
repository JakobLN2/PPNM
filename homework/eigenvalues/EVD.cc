#include"EVD.h"
#include<cmath>

void EVD::timesJ(matrix& K, int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int i = 0; i < K.nrows; ++i) {
        double kip = K(i,p),
               kiq = K(i,q);
		K(i,p) = c * kip - s * kiq;
		K(i,q) = s * kip + c * kiq;
    }
}
void EVD::Jtimes(matrix& K, int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int j = 0; j < K.ncols; ++j) {
        double kpj = K(p,j),
               kqj = K(q,j);
		K(p,j) = c * kpj + s * kqj;
		K(q,j) = - s * kpj + c * kqj;
    }
}

void EVD::cyclic() {
    bool changed = false;
    int it = 1;
    // for(int k = 0; k < 100000 ; ++k) {
    do {
        changed = false;
        std::cout << "iteration # " << it++ << "\n";
        for(int i = 0; i < A.nrows; ++i) {
            for(int j = i + 1 ; j < A.nrows; ++j) {
                double aij = A(i,j), //vji = V(j,i),
                aii = A(i,i), ajj = A(j,j);
                double theta = 0.5 * std::atan2(2*aij, ajj - aii);
                double c = std::cos(theta),
                       s = std::sin(theta);
                
                double new_aii = c*c * aii - 2*s*c * aij + s*s * ajj,
                       new_ajj = s*s * aii + 2*s*c * aij + c*c * ajj;
                if(aii != new_aii || ajj != new_ajj) {
                    changed = true;
                    timesJ(A,i,j,theta);
                    Jtimes(A,i,j,-theta);
                    timesJ(V,i,j,theta);

                    // Jtimes(i,j,theta); //-theta is the same as transposing
            
                } //else {converged = true;}
            }
        }
    } while(changed);
    // }

    //     // std::cout << "iteration # " << it++ << "\n";
    //     for(int i = 0; i < V.nrows; ++i) {
    //         // for(int j = i + 1 ; j < V.ncols; ++j) {
    //         for(int j = 0 ; j < i; ++j) {
    //             // if(j == i) continue;
    //             double vij = V(i,j), //vji = V(j,i),
    //                    vii = V(i,i), vjj = V(j,j);
    //             double theta = 0.5 * std::atan2(2*vij, vjj - vii);
    //             double c = std::cos(theta),
    //                    s = std::sin(theta);
                
    //             double new_vii = c*c * vii - 2*s*c * vij + s*s * vjj,
    //                    new_vjj = s*s * vii + 2*s*c * vij + c*c * vjj;
    //             if(vii != new_vii && vjj != new_vjj) {
    //                 timesJ(i,j,-theta);
    //                 Jtimes(i,j,theta); //-theta is the same as transposing
                
                    // for(int k = 0; k < V.ncols ; ++k) {

                    //     double vki = V(k, i);
                    //     double vkj = V(k, j);
                    //     V(k,i) = c * vki - s * vkj;
                    //     V(k,j) = c * vkj + s * vki;
                    // }
                
                    // for(int k = 0; k < V.nrows ; ++k) {

                    //     double vik = V(i,k);
                    //     double vjk = V(j,k);
                    //     V(i,k) = c * vik - s * vjk;
                    //     V(j,k) = c * vjk + s * vik;
                    // }
                
    //             }      
    //         }
    //     }
    // }
}