#include"vector.h"
#include"matrix.h"
#include<string>
#include<iostream>
#include<cmath>


matrix& matrix::operator*=(double n) {
    for(int i = 0 ; i < nrows ; ++i) {
        for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] *= n;
    }
    return *this;
}
matrix& matrix::operator/=(double n) {
    *this *= 1/n;
    return *this;
}
matrix& matrix::operator+=(const matrix& b) {
    sum_compatible_exception(*this, b);
    for(int i = 0 ; i < nrows ; ++i) {
        for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] += b(i,j);
    }
    return *this;
}

matrix& matrix::operator-=(const matrix& b) {
    sum_compatible_exception(*this, b);
    for(int i = 0 ; i < nrows ; ++i) {
        for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] -= b(i,j);
    }
    return *this;
}

vector matrix::getRow(int i) const {
    vector res(ncols);
    for(int j = 0; j < ncols ; ++j) res[j] = cols[i + j * nrows];
    return res;
}
// matrix matrix::getRow(int i) const {
//     matrix res(1,ncols);
//     for(int j = 0; j < ncols ; ++j) res(0,j) = cols[i + j * nrows];
//     return res;
// }
void matrix::setRow(int i, matrix setrow) {
    if(i >= nrows) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(nrows) + " rows.");}
    if(setrow.ncols != ncols) {throw std::invalid_argument("operand shape does not match, setting row of length " + std::to_string(setrow.ncols) + " into matrix of " + std::to_string(ncols) + " columns.");}
    for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] = setrow(i,j);
}
void matrix::setRow(int i, vector setrow) {
    if(i >= nrows) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(nrows) + " rows.");}
    if(setrow.size != ncols) {throw std::invalid_argument("operand shape does not match, setting row of length " + std::to_string(setrow.size) + " into matrix of " + std::to_string(ncols) + " columns.");}
    for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] = setrow[j];
}
void matrix::setRow(int i, double n) {
    for(int j = 0; j < ncols ; ++j) cols[i + j * nrows] = n;
}

// matrix matrix::getCol(int j) const {
//     matrix res(nrows, 1);
//     for(int i = 0; i < nrows ; ++i) res(i,0) = cols[i + j * nrows];
//     return res;
// }
vector matrix::getCol(int j) const {
    vector res(nrows);
    for(int i = 0; i < nrows ; ++i) res[i] = cols[i + j * nrows];
    return res;
}
// void matrix::setCol(int j, matrix setcol) {
//     if(j >= ncols) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(ncols) + " columns.");}
//     if(setcol.nrows != nrows) {throw std::invalid_argument("operand shape does not match, setting column of length " + std::to_string(setcol.nrows) + " into matrix of " + std::to_string(nrows) + " rows.");}
//     for(int i = 0; i < nrows ; ++i) cols[i + j * nrows] = setcol(i,j);
// }
void matrix::setCol(int j, vector setcol) {
    if(j >= ncols) {throw std::invalid_argument("index out of range for matrix with " + std::to_string(ncols) + " columns.");}
    if(setcol.size != nrows) {throw std::invalid_argument("operand shape does not match, setting column of length " + std::to_string(setcol.size) + " into matrix of " + std::to_string(nrows) + " rows.");}
    for(int i = 0; i < nrows ; ++i) cols[i + j * nrows] = setcol[i];
}
void matrix::setCol(int j, double n) {
    for(int i = 0; i < nrows ; ++j) cols[i + j * nrows] = n;
}

void matrix::print(std::string s) const {
    std::cout << s << "( ";
    std::string pad((int)s.size() + 2, ' ');
    for(int i = 0 ; i < nrows ; ++i) {
        for(int j = 0; j < ncols ; ++j) std::cout << cols[i + j * nrows] << " ";
        if(i == nrows - 1) std::cout << ")\n";
        else std::cout << "\n" << pad;
    }
}
matrix matrix::copy() {
    matrix res(nrows, ncols);
    for(int i = 0; i < nrows ; ++i) {
        for(int j = 0 ; j < ncols ; ++j) res(i,j) = cols[i + j * nrows];
    }
    return res;
}

matrix operator+(const matrix& a, const matrix& b) {
    sum_compatible_exception(a,b);
    matrix res(a.nrows, a.ncols);
    for(int i = 0 ; i < a.nrows ; ++i) {
        for(int j = 0 ; j < a.ncols ; ++j) res(i,j) = a(i,j) + b(i,j); 
    }
    return res;
}
matrix operator-(const matrix& a, const matrix& b) {
    sum_compatible_exception(a,b);
    matrix res(a.nrows, a.ncols);
    for(int i = 0 ; i < a.nrows ; ++i) {
        for(int j = 0 ; j < a.ncols ; ++j) res(i,j) = a(i,j) - b(i,j); 
    }
    return res;
}
matrix operator-(const matrix& a) {
    matrix res(a.nrows, a.ncols);
    for(int i = 0 ; i < a.nrows ; ++i) {
        for(int j = 0 ; j < a.ncols ; ++j) res(i,j) = -a(i,j); 
    }
    return res;
}
matrix operator/(const matrix& a, double n) {
    matrix res(a.nrows, a.ncols);
    for(int i = 0 ; i < a.nrows ; ++i) {
        for(int j = 0 ; j < a.ncols ; ++j) res(i,j) = a(i,j)/n; 
    }
    return res;
}
matrix operator*(const matrix& a, double n) {
    matrix res(a.nrows, a.ncols);
    for(int i = 0 ; i < a.nrows ; ++i) {
        for(int j = 0 ; j < a.ncols ; ++j) res(i,j) = a(i,j) * n; 
    }
    return res;
}
matrix operator*(double n, const matrix& a) {return a * n;}
matrix operator*(const matrix& a, const matrix& b) {
    prod_compatible_exception(a,b);
    matrix c(a.nrows, b.ncols);
    double sum;
    for(int i = 0; i < c.nrows ; ++i) {
        for(int j = 0; j < c.ncols ; ++j) {
            sum = 0;
            for(int k = 0; k < a.ncols ; ++k) sum += a(i,k) * b(k,j);
            c(i,j) = sum;
        }
    }
    return c;
}
vector operator*(const matrix& a, const vector& b) {
    if(a.ncols != b.size) {throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") * " + std::to_string(b.size));}
    vector res(a.nrows);
    for(int i = 0; i < a.nrows ; ++i) res[i] = dot(a.getRow(i), b);
    return res;
}
vector operator*(const vector& a, const matrix& b) {
    if(a.size != b.ncols) {throw std::invalid_argument("operand shapes do not match " + std::to_string(a.size) + " * (" + std::to_string(b.nrows) + "," + std::to_string(b.ncols));}
    vector res(b.ncols);
    for(int j = 0; j < b.ncols ; ++j) res[j] = dot(a, b.getCol(j));
    return res;
}

matrix transpose(const matrix& a) {
    matrix res(a.ncols, a.nrows);
    for(int i = 0; i < res.nrows ; ++i) {
        for(int j = 0; j < res.ncols; ++j) res(i,j) = a(j,i);
    }
    return res;
}

matrix identity(int n) {
    matrix res(n,n);
    for(int i = 0; i < n ; ++i) res(i,i) = 1;
    return res;
}

bool approx(const matrix& a, const matrix& b, double acc,double eps) {
    sum_compatible_exception(a,b);
    for(int i = 0; i < a.nrows ; ++i) {
        for(int j = 0; j < a.ncols ; ++j) {
            if(std::abs(a(i,j) - b(i,j)) <= acc) {
                if(a(i,j) != 0 && b(i,j) != 0 && std::abs(a(i,j) - b(i,j))/std::max(std::abs(a(i,j)),(std::abs(b(i,j)))) > eps) return false;
            } else {return false;}
        }
    }
    return true;    
}
// bool approx(const matrix& a, const vector& b, double acc,double eps) { //holy ugly
//     if(a.ncols == b.size && a.nrows == 1) {
//         for(int j = 0; j < a.ncols ; ++j) {
//             if(std::abs(a(0,j) - b[j]) < acc) {
//                 if(a(0,j) != 0 && b[j] != 0 && std::abs(a(0,j) - b[j])/std::max(std::abs(a(0,j)),(std::abs(b[j]))) > eps) return false;
//             } else {return false;}
//         }
//     } else if(a.nrows == b.size && a.ncols == 1) {
//         for(int i = 0 ; i < a.nrows ; ++i) {
//             if(std::abs(a(i,0) - b[i]) < acc) {
//                 if(a(i,0) != 0 && b[i] != 0 && std::abs(a(i,0) - b[i])/std::max(std::abs(a(i,0)),(std::abs(b[i]))) > eps) return false;
//             } else {return false;}
//         }
//     } else {
//         throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + " ?= " + std::to_string(b.size));
//     }
//     return true;
// }

void prod_compatible_exception(const matrix& a, const matrix& b) { //matrix product compatible check
    if(a.ncols != b.nrows) {
        throw std::invalid_argument("operand shapes do not match (" 
                                    + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") , ("
                                    + std::to_string(b.nrows) + "," + std::to_string(b.ncols) + ")");
    }
}
void sum_compatible_exception(const matrix& a, const matrix& b) {
    if(a.ncols != b.ncols && a.nrows != b.nrows) {
        throw std::invalid_argument("operand shapes do not match (" 
            + std::to_string(a.nrows) + "," + std::to_string(a.ncols) + ") , ("
            + std::to_string(b.nrows) + "," + std::to_string(b.ncols) + ")");
    }
}
