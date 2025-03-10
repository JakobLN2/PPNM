#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

// #ifdef LONG_DOUBLE
//     #define NUMBER long double
// #else
//     #define NUMBER double
// #endif
#include"vector"
#include<vector>
#include<string>
#include<iostream>

class vector {
    // private:    
    public:
        std::vector<double> data;
        int size = data.size();

        vector(int n) : data(n) {} // parametrized constructor
        vector() = default; // default constructor
        vector(const vector&)=default; // copy constructor
        vector(vector&&)=default; // move constructor
        ~vector()=default; // destructor
        vector& operator=(const vector&)=default; // copy assignment
        vector& operator=(vector&&)=default; // move assignment
        
        // int size() {return data.size();};

        double& operator[](int i) {return data[i];}
        double operator[](int i) const {return data[i];}

        vector& operator*=(double n);
        vector& operator/=(double n);

        vector& operator+=(double);
        vector& operator-=(double);

        vector& operator+=(const vector&);
        vector& operator-=(const vector&);

        double norm();
        
        void print(std::string s = "") const; //for debugging
        
    };
vector operator+(const vector&, const vector&);
vector operator-(const vector&);
vector operator-(const vector&, const vector&);
vector operator*(const vector&, double);
vector operator*(double, const vector&);
vector operator/(const vector&, double);

double dot(const vector&, const vector&); //inner product
bool compatible_exception(const vector&, const vector&); //Check if two vectors are compatible, if not throw an exception.

// int size() return size;
// const double& operator[](int i) const {return data[i];}


// friend vector<T> operator+(const vector<T>&, const vector<T>&);
// vector operator-(const vector&);
// vector operator*(const vector&, double);
// vector operator*(double, const vector&);
// vector operator/(const vector&, double);
// bool approx(const vector&, const vector&, double acc=1e-6,double eps=1e-6);
// double dot(const vector&, const vector&);

#endif