#include"vector.h"
#include"vector.cc"
#include"matrix.h"
#include<string>
#include<iostream>
#include<cmath>
#include<vector>


matrix& matrix::operator*=(double n) {
    for(int i = 0 ; i < size1 ; ++i) {
        for(int j = 0; j < size2 ; ++j) cols[i][j] *= n;
    }
    return *this;
}
matrix& matrix::operator/=(double n) {
    *this *= 1/n;
    // for(int i = 0 ; i < size ; ++i) data[i] /= n;
    // for(auto& d : data) d /= n;
    return *this;
}
// double vector::norm() {
//     double res;
//     for(auto& d : data) res += d*d;
//     return std::sqrt(res);
// }
std::vector<double&> matrix::getRow(int i) {
    std::vector<double&> res(size2);
    for(int j = 0; j < size1 ; ++j) res.push_back(std::ref(cols[j][i]));
    return res;
}

// void matrix::print(std::string s) const {
//     std::cout << s << "(";
//     std::string pad = "";
//     // for(unsigned long int i = 0; i < s.size() + 1 ; ++i) pad += " ";
//     for(const vector& col : cols) col.print("");
        
//     std::cout << "\n";
// }

void matrix::print(std::string s) const {
    std::cout << s;
    // for(const vector& col : cols) col.print("");
    vector col;
    for(int i = 0 ; i < size1 ; ++i) {
        col = cols[i];
        for(int j = 0; j < size2 ; ++j) std::cout << col[j] << ", ";
        std::cout << "\n";
    }
    
}

// vector operator+(const vector& a, const vector& b) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] + b.data[i];
//     return res;
// }
// vector operator-(const vector& a, const vector& b) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] - b.data[i];
//     return res;
// }
// vector operator-(const vector& a) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = -a.data[i];
//     return res;
// }

// vector operator*(const vector& a, double n) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] * n;
//     return res;
// }
// vector operator*(double n, const vector& a) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] * n;
//     return res;
// }
// vector operator/(double n, const vector& a) {
//     vector res(a.size);
//     for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] / n;
//     return res;
// }


// double dot(const vector& a, const vector& b) {
//     // assert(a.size == b.size); //Check that they are compatible
//     double res = 0;
//     for(int i = 0 ; i < a.size ; ++i) res += a.data[i] * b.data[i];
//     return res;
// }

bool prod_compatible_exception(const matrix& a, const matrix& b) { //matrix product compatible check
    if(a.ncols() != b.nrows()) {
        throw std::invalid_argument("operand shapes do not match (" 
                                    + std::to_string(a.nrows()) + "," + std::to_string(a.ncols()) + ") , ("
                                    + std::to_string(b.nrows()) + "," + std::to_string(b.ncols()) + ")");
    }
    return true;
}

bool add_compatible_exception(const matrix& a, const matrix& b) {
    if(a.ncols() != b.ncols() && a.nrows() != b.nrows()) {
        throw std::invalid_argument("operand shapes do not match (" 
            + std::to_string(a.nrows()) + "," + std::to_string(a.ncols()) + ") , ("
            + std::to_string(b.nrows()) + "," + std::to_string(b.ncols()) + ")");
    }
    return true;
}
