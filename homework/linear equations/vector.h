#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

// #ifdef LONG_DOUBLE
//     #define NUMBER long double
// #else
//     #define NUMBER double
// #endif
#include"vector"
#include<string>
#include<iostream>

template<typename T>
class vector {
    // private:    
    public:
        std::vector<T> data;
        int size = data.size();

        vector(int n) : data(n) {} // parametrized constructor
        vector() = default; // default constructor
        vector(const vector&)=default; // copy constructor
        vector(vector&&)=default; // move constructor
        ~vector()=default; // destructor
        vector& operator=(const vector&)=default; // copy assignment
        vector& operator=(vector&&)=default; // move assignment
        
        T& operator[](int i) {return data[i];}
        vector<T>& operator*=(double n);
        
        // void print(std::string s = "") const; //for debugging
        void print(std::string s) const {
            std::cout << s;
            std::cout << "mojn gutter";
            // for(T d : data) std::cout << d << ", ";
            // for(int i = 0 ; i < size ; ++i) std::cout << data[i] << ", ";
            std::cout << std::endl;
        };
        
    };
template<typename T>
vector<T> operator+(const vector<T>&, const vector<T>&);
// int size() return size;
// const T& operator[](int i) const {return data[i];}


// friend vector<T> operator+(const vector<T>&, const vector<T>&);
// vector operator-(const vector&);
// vector operator*(const vector&, double);
// vector operator*(double, const vector&);
// vector operator/(const vector&, double);
// bool approx(const vector&, const vector&, double acc=1e-6,double eps=1e-6);
// double dot(const vector&, const vector&);

#endif