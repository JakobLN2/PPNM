#include"svd.h"

// void svd::giv(matrix& K, int p, int q, double theta) { //Can be written as a Jacobi rotation
//     // Jtimes(K,p,q,theta);
//     double c = std::cos(theta),
//            s = std::sin(theta);
//     for(int j = 0; j < K.ncols; ++j){
//         double kpj = K(p,j);
//         K(p,j) = c * kpj - s * K(q,j);
//         K(q,j) = s * kpj + c * K(q,j);
//     }
// }

void svd::timesJ(matrix& K, int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int i = 0; i < K.nrows; ++i) {
        double kip = K(i,p),
               kiq = K(i,q);
		K(i,p) = c * kip - s * kiq;
		K(i,q) = s * kip + c * kiq;
    }
}
void svd::Jtimes(matrix& K, int p, int q, double theta) {
    double c = std::cos(theta),
           s = std::sin(theta);
    
    for(int j = 0; j < K.ncols; ++j) {
        double kpj = K(p,j),
               kqj = K(q,j);
		K(p,j) =   c * kpj + s * kqj;
		K(q,j) = - s * kpj + c * kqj;
    }
}

void svd::cyclic() {
    bool changed = false;
    int N = 0;
    std::cerr << "Cyclic function started for\n"; M.print("input = ", std::cerr);
    do {
        changed = false;
        for(int i = 0; i < D.nrows; ++i) {
            for(int j = i + 1 ; j < D.nrows; ++j) {
                double dii = D(i,i), djj = D(j,j); //record diagonal elements for convergence check.

                double theta_giv = std::atan2(D(i,j) - D(j,i), (D(i,i) + D(j,j))); 
                Jtimes(D,i,j,-theta_giv); //G^TD

                vector Di = D.getCol(i), Dj = D.getCol(j);
                double x = 2 * dot(Di,Dj),
                       y = dot(Di,Di) - dot(Dj,Dj);
                double theta_J = -0.5 * std::atan2(x,y);

                timesJ(D,i,j,theta_J); //G^TDJ
                Jtimes(D,i,j,-theta_J); //-theta is the same as transposing

                timesJ(V,i,j,theta_J); //Set V -> VJ

                timesJ(U,i,j,theta_giv); //Set U -> UGJ
                timesJ(U,i,j,theta_J);

                if(dii != D(i,i) && djj != D(j,j)) changed = true;
                //If an entire cyclic iteration did not update the diagonal elements once, we are done
            }
        }
        N += 1;
    } while(changed);
    std::cerr << "Factorization done in " << N << " iterations\n";
    
    //Make (functionally) zero-elements actually zero for cleaner output. I don't know how, but some off-diagonals in D are ~10^-300.
    // for(int i = 0; i < D.nrows; ++i) for(int j = 0; j < D.ncols; ++j) if(D(i,j) < 1e-200) D(i,j) = 0;

    for(int i = 0; i < D.ncols; ++i) if(D(i,i) < 0) { //Make negative singular values positive
        D(i,i) *= -1;
        for(int j = 0; j < U.nrows; ++j) U(j,i) *= -1; //Invert the relevant column in U
    }
}

matrix svd::p_inverse() {
    matrix res(D.ncols, D.ncols);
    for(int i = 0; i < D.ncols; ++i) if(D(i,i) > 0) res(i,i) = 1/D(i,i); //All non-zero singular elements are inverted
    return V*res*transpose(U);
}