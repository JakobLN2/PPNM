#ifndef HAVE_MATRIX_H
#define HAVE_MATRIX_H

// #ifdef LONG_DOUBLE
//     #define NUMBER long double
// #else
//     #define NUMBER double
// #endif
#include"vector.h"
#include<vector>
#include<string>
#include<iostream>
#include<stdexcept>
#include<array>
#include<tuple>


class matrix {
    // private:    
    public:
        std::vector<vector> cols;
        int size1 = cols.empty() ? 0 : cols[0].size; // # of rows
        int size2 = cols.size(); // # of cols

        matrix(int n, int m) : cols(m, vector(n)) {} // parametrized constructor
        matrix() = default; // default constructor
        matrix(const matrix&)=default; // copy constructor
        matrix(matrix&&)=default; // move constructor
        ~matrix()=default; // destructor
        matrix& operator=(const matrix&)=default; // copy assignment
        matrix& operator=(matrix&&)=default; // move assignment
        
        int nrows() const {return cols.empty() ? 0 : cols[0].size;};
        int ncols() const {return cols.size();};
        
        // std::vector<std::reference_wrapper<double>> getRow(int);
        
        // std::vector<double> getRow(int);
        vector getRow(int);
        void setRow(int, vector&);
        // void setRow(int, double[]);
        void setRow(int, std::array<double>);
        
        vector getCol(int);
        void setCol(int, vector&);

        // double& operator[](int i, int j) {return cols[j][i];}; //This does not work on my machine?
        double& operator()(int i, int j) {return cols[j][i];}; //double indexing has to be with parentheses? a(1,2)
        double& get(int i, int j) {return cols[j][i];};
        double get(int i, int j) const {return cols.at(j)[i];};
        
        void set(int i, int j, double n) {cols[j][i] = n;};

        matrix& operator*=(double);
        matrix& operator/=(double);

//         double norm();
        
        void print(std::string s = "") const; //for debugging
    };
// vector operator+(const vector&, const vector&);
// vector operator-(const vector&);
// vector operator-(const vector&, const vector&);
// vector operator*(const vector&, double);
// vector operator*(double, const vector&);
// vector operator/(const vector&, double);

// double dot(const vector&, const vector&); //inner product(?)
// // int size() return size;
// // const double& operator[](int i) const {return data[i];}


// // friend vector<T> operator+(const vector<T>&, const vector<T>&);
// // vector operator-(const vector&);
// // vector operator*(const vector&, double);
// // vector operator*(double, const vector&);
// // vector operator/(const vector&, double);
// // bool approx(const vector&, const vector&, double acc=1e-6,double eps=1e-6);
// // double dot(const vector&, const vector&);
bool prod_compatible_exception(const matrix&, const matrix&); //Check if two matrices are compatible for matrix multiplication, if not throw an exception.
bool add_compatible_exception(const matrix&, const matrix&); //Check if two matrices are compatible for addition (+ subtraction)

#endif