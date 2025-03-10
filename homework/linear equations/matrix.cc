#include"vector.h"
#include"vector.cc"
#include"matrix.h"
#include<string>
#include<iostream>
#include<cmath>
#include<vector>
#include<stdexcept>
#include<array>

matrix& matrix::operator*=(double n) {
    for(int i = 0 ; i < size1 ; ++i) {
        for(int j = 0; j < size2 ; ++j) cols[i][j] *= n; //TODO: this is not quite right
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

// std::vector<double> matrix::getRow(int i) {
    //     // TODO: Maybe make a copy of this without the index check for internal use (so we only have to check once)?
    //     if(i >= size1) throw std::invalid_argument("index " + std::to_string(i) + " out of range for matrix with " + std::to_string(size1) + " rows");
    //     std::vector<double> res;
    //     for(int j = 0; j < size2 ; ++j) res.push_back(get(i,j));
    //     return res;
    // }
    
    
// TODO: I dont know how to make my own vector class contain references to the doubles in the cols - cannot modify the row directly
vector matrix::getRow(int i) {
    //maybe make a copy of this without the index check for internal use (so we only have to check once)?
    if(i >= size1) throw std::invalid_argument("index " + std::to_string(i) + " out of range for matrix with " + std::to_string(size1) + " rows");
    
    vector res(size2);
    for(int j = 0; j < size2 ; ++j) res[j] = get(i,j);
    return res;
}

void matrix::setRow(int i, vector& v) {
    if(v.size != size2) throw std::invalid_argument("row of length " + std::to_string(v.size) + " incompatible with matrix with " + std::to_string(size2) + " cols");
    for(int j = 0; j < size2; ++j) get(i,j) = v[j];
}
// void matrix::setRow(int i, double v[]) {
//     // if(v.size != size2) throw std::invalid_argument("row of length " + std::to_string(v.size) + " incompatible with matrix with " + std::to_string(size2) + " cols");

//     for(int j = 0; j < size2; ++j) get(i,j) = v[j];
// }
void matrix::setRow(int i, std::tuple<double> v) {
    // if(v.size != size2) throw std::invalid_argument("row of length " + std::to_string(v.size) + " incompatible with matrix with " + std::to_string(size2) + " cols");

    for(int j = 0; j < size2; ++j) get(i,j) = v[j];
}

//we dont really need these, by my own construction it is much easier to modify columns than rows
vector matrix::getCol(int i) {
    if(i >= size2) throw std::invalid_argument("index " + std::to_string(i) + " out of range for matrix with " + std::to_string(size2) + " cols");    
    return cols[i];
}
void matrix::setCol(int j, vector& v) {
    if(v.size != size1) throw std::invalid_argument("col of length " + std::to_string(v.size) + " incompatible with matrix with " + std::to_string(size1) + " rows");
    for(int i = 0; i < size1; ++i) get(i,j) = v[i];
}
    

// Incredibly ugly (but functional) print function for debugging
void matrix::print(std::string s) const {
    std::string pad;
    for(int i = 0; i < (int)s.size() + 1 ; ++i) pad += " ";

    for(int i = 0; i < size1 ; ++i) {
        if(i == 0) std::cout << s << "("; //align matrix with the initial text
        else std::cout << pad;
        
        for(int j = 0; j < size2 ; ++j) std::cout << get(i,j) << ", ";
        if(i == size1 - 1) std::cout << "\b\b)\n"; //Make end parentheses and delete comma after last element
        else std::cout << "\b\b \n";
    }
        
}

// void matrix::print(std::string s) {
//     std::cout << s;
    // for(const vector& col : cols) col.print("");
    // vector col;
    // for(int i = 0 ; i < size1 ; ++i) {
    //     //  col = cols[i];
    //     for(int j = 0; j < size2 ; ++j) std::cout << cols[i][j] << ", ";
    //     std::cout << "\n";
    // }
    
// }

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
