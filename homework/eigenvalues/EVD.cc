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
    do {
        changed = false;
        for(int i = 0; i < D.nrows; ++i) {
            for(int j = i + 1 ; j < D.nrows; ++j) {
                double dij = D(i,j), //vji = V(j,i),
                dii = D(i,i), djj = D(j,j);
                double theta = 0.5 * std::atan2(2*dij, djj - dii);
                double c = std::cos(theta),
                       s = std::sin(theta);
                
                double new_dii = c*c * dii - 2*s*c * dij + s*s * djj,
                       new_djj = s*s * dii + 2*s*c * dij + c*c * djj;
                if(dii != new_dii || djj != new_djj) {
                    changed = true;
                    timesJ(D,i,j,theta);
                    Jtimes(D,i,j,-theta); //-theta is the same as transposing
                    timesJ(V,i,j,theta);

            
                } //else {converged = true;}
            }
        }
    } while(changed);

    // for(int i = 0; i < D.ncols ; ++i) w[i] = D(i,i);
}