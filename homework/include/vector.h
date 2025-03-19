#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

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
        
        inline double& operator[](int i) {return data[i];}
        inline double operator[](int i) const {return data[i];}
        
        vector& operator*=(double);
        vector& operator/=(double);

        vector& operator+=(const vector&);
        vector& operator-=(const vector&);

        double norm();
        void normalize();
        void print(std::string s = "") const; //for debugging
        vector copy() const;
        
    };
vector operator+(const vector&, const vector&);
vector operator-(const vector&);
vector operator-(const vector&, const vector&);
vector operator*(const vector&, double);
vector operator*(double, const vector&);
vector operator/(const vector&, double);

/*Project vector a onto b*/
vector proj(const vector&, const vector&);

double dot(const vector&, const vector&); //inner product
bool approx(const vector& a, const vector& b, double acc=1e-6,double eps=1e-6);
bool compatible_exception(const vector&, const vector&); //Check if two vecs are compatible, if not throw an exception.


#endif