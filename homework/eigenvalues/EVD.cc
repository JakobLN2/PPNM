#include"EVD.h"
#include"matrix.h"
#include"vector.h"
#include<cmath>

void EVD::timesJ(int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int i = 0; i < V.nrows; ++i) {
        double vip = V(i,p),
               viq = V(i,q);
		V(i,p) = c * vip - s * viq;
		V(i,q) = s * vip + c * viq;
    }
}
void EVD::Jtimes(int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int j = 0; j < V.ncols; ++j) {
        double vpj = V(p,j),
               vqj = V(q,j);
		V(p,j) = c * vpj + s * vqj;
		V(q,j) = - s * vpj + c * vqj;
    }
}

void EVD::cyclic() {
    // bool converged = false;
    // int it = 0;
    // do {
    //     std::cout << "iteration # " << it++ << "\n";
    //     for(int i = 0; i < V.nrows; ++i) {
    //         for(int j = 0 ; j < V.ncols; ++j) {
    //             double vij = V(i,j), //vji = V(j,i),
    //                    vii = V(i,i), vjj = V(j,j);
    //             double theta = 0.5 * std::atan2(2*vij, vjj - vii);
    //             double c = std::cos(theta),
    //                    s = std::sin(theta);
                
    //             double new_vii = c*c * vii - 2*s*c * vij + s*s * vjj,
    //                    new_vjj = s*s * vii + 2*s*c * vij + c*c * vjj;
    //                 if(vii != new_vii || vjj != new_vjj) {
    //                     timesJ(i,j,-theta);
    //                     Jtimes(i,j,theta); //-theta is the same as transposing
                
                
                

    //             } else {converged = true;}
    //         }
    //     }
    // } while(!converged);

    for(int k = 0; k < 100000 ; ++k) {
        // std::cout << "iteration # " << it++ << "\n";
        for(int i = 0; i < V.nrows; ++i) {
            // for(int j = i + 1 ; j < V.ncols; ++j) {
            for(int j = 0 ; j < i; ++j) {
                // if(j == i) continue;
                double vij = V(i,j), //vji = V(j,i),
                       vii = V(i,i), vjj = V(j,j);
                double theta = 0.5 * std::atan2(2*vij, vjj - vii);
                double c = std::cos(theta),
                       s = std::sin(theta);
                
                double new_vii = c*c * vii - 2*s*c * vij + s*s * vjj,
                       new_vjj = s*s * vii + 2*s*c * vij + c*c * vjj;
                if(vii != new_vii && vjj != new_vjj) {
                    timesJ(i,j,-theta);
                    Jtimes(i,j,theta); //-theta is the same as transposing
                
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
                
                }      
            }
        }
    }
}