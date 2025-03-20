#include"lsfit.h"

std::tuple<vector, matrix> lsfit(const std::vector<std::function<double(double)>>& f, const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& dy) {
    matrix A(x.size(), f.size());
    vector b(y.size());
    for(int i = 0; i < (int)x.size() ; ++i) {
        for(int j = 0; j < (int)f.size() ; ++j) {
            A(i,j) = f[j](x[i])/dy[i];
        }
        b[i] = y[i]/dy[i];
    }
    QRSolver fac(A);
    fac.decomp();
    vector par = fac.solve(b);

    matrix Ainv = fac.inverse();
    matrix cov = fac.Rinv * transpose(fac.Rinv);

    return std::make_tuple(par, cov);
}