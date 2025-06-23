#ifndef HAVE_MATRIX_H
#define HAVE_MATRIX_H

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
        // matrix getRow(int) const;
        vector getRow(int) const;
        void setRow(int, matrix);
        void setRow(int, vector);
        void setRow(int, double);


        // matrix getCol(int) const;
        vector getCol(int) const;
        void setCol(int, matrix);
        void setCol(int, vector);
        void setCol(int, double);

        // vector& operator[](int i) {return cols[i];}; //Has to be single indexing? a[1][2] - I dont have C++23?
        inline double& operator()(int i, int j) {return cols[i + j * nrows];}; //double indexing
        inline double operator()(int i, int j) const {return cols[i + j * nrows];};

        matrix& operator*=(double);
        matrix& operator/=(double);
        matrix& operator+=(const matrix&);
        matrix& operator-=(const matrix&);

        // void print(std::string s = "") const; //for debugging
        void print(std::string s = "", std::ostream& = std::cout) const; //for debugging
        matrix copy() const; //not sure if A = B does it right
    };
matrix operator+(const matrix& a, const matrix& b);
matrix operator-(const matrix& a);
matrix operator-(const matrix& a, const matrix& b);
matrix operator/(const matrix& a, double);
matrix operator*(const matrix& a, double);
matrix operator*(double, const matrix& a);
matrix operator*(const matrix& a, const matrix& b);
vector operator*(const matrix& a, const vector& b); //Note: vectors have no shape, therefore I simply trust that you know if it is a row or column vector.
vector operator*(const vector& a, const matrix& b); //Note: Also unable to calculate the outer product TODO, perchance?
matrix transpose(const matrix& a);

matrix reshape(const vector, int,int);
matrix identity(int); //Create identity matrix of size n
bool approx(const matrix& a, const matrix& b, double acc=1e-6,double eps=1e-6);
void prod_compatible_exception(const matrix& a, const matrix& b); //Check if two matrices are compatible for matrix multiplication, if not throw an exception.
void sum_compatible_exception(const matrix& a, const matrix& b); //Check if two matrices are compatible for addition (+ subtraction)

#endif