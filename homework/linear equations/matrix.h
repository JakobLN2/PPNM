#ifndef HAVE_matrix_H
#define HAVE_matrix_H

#include"vector.h"
#include<vector>
#include<string>
#include<iostream>
#include<stdexcept>

class matrix {
    // private:    
    public:
        std::vector<double> cols;
        int nrows,
            ncols;

        matrix(int n, int m) : cols(m * n) {nrows = n; ncols = m;} // parametrized constructor
        matrix() = default; // default constructor
        matrix(const matrix&)=default; // copy constructor
        matrix(matrix&&)=default; // move constructor
        ~matrix()=default; // destructor
        matrix& operator=(const matrix&)=default; // copy assignment
        matrix& operator=(matrix&&)=default; // move assignment
        
        // void reshape(int n, int m) //TODO: implement reshape
        // std::vector<double> getRow(int);
        vector getRow(int) const;
        // matrix getRow(int) const;
        // void setRow(int, std::vector<double>);
        // void setRow(int, vector);
        void setRow(int, matrix);
        void setRow(int, vector);
        void setRow(int, double);

        // std::vector<double> getCol(int);
        matrix getCol(int) const;
        // void setCol(int, std::vector<double>);
        void setCol(int, matrix);
        void setCol(int, double);

        // vector& operator[](int i) {return cols[i];}; //Has to be single indexing? a[1][2] - I dont have C++23?
        double& operator()(int i, int j) {return cols[i + j * nrows];}; //double indexing
        double operator()(int i, int j) const {return cols[i + j * nrows];};

        matrix& operator*=(double);
        matrix& operator/=(double);
        matrix& operator+=(const matrix&);
        matrix& operator-=(const matrix&);

        void print(std::string s = "") const; //for debugging
        matrix copy(); //not sure if A = B does it right
    };
matrix operator+(const matrix& a, const matrix& b);
matrix operator-(const matrix& a);
matrix operator-(const matrix& a, const matrix& b);
matrix operator/(const matrix& a, double);
matrix operator*(const matrix& a, double);
matrix operator*(double, const matrix& a);
matrix operator*(const matrix& a, const matrix& b);
matrix transpose(const matrix& a);

// bool approx(const matrix& a, const matrix& b, double acc=1e-6,double eps=1e-6);
void prod_compatible_exception(const matrix& a, const matrix& b); //Check if two matrices are compatible for matrix multiplication, if not throw an exception.
void sum_compatible_exception(const matrix& a, const matrix& b); //Check if two matrices are compatible for addition (+ subtraction)

#endif