#ifndef HAVE_INTERP_H
#define HAVE_INTERP_H

#include"../include/matrix.h"
#include"../include/vector.h"
#include<exception>
#include<cmath>

int binsearch(vector, double);
double linterp(vector, vector, double);
double linterpInteg(vector, vector, double);

class qspline {
    public:
        vector x,y,b,c;        
        
        qspline(const vector& x, const vector& y) : x(x), y(y) {
            b = vector(x.size - 1);
            c = vector(x.size - 1);
            buildSpline();
        } // parametrized constructor


        qspline() = default; // default constructor
        qspline(const qspline&)=default; // copy constructor
        qspline(qspline&&)=default; // move constructor
        ~qspline()=default; // destructor
        qspline& operator=(const qspline&)=default; // copy assignment
        qspline& operator=(qspline&&)=default; // move assignment

        void buildSpline(); //Calculate the quadratic spline and set b and c
        double eval(double) const;
        double integ(double);
        double deriv(double);
        inline double operator()(double z) const {return eval(z);}

};

class cubspline {
    public:
        vector x,y,b,c,d;

    cubspline(const vector& x, const vector& y) : x(x), y(y) {
        b = vector(x.size - 1);
        c = vector(x.size - 1);
        d = vector(x.size - 1);

        buildSpline();
    } // parametrized constructor


    cubspline() = default; // default constructor
    cubspline(const cubspline&)=default; // copy constructor
    cubspline(cubspline&&)=default; // move constructor
    ~cubspline()=default; // destructor
    cubspline& operator=(const cubspline&)=default; // copy assignment
    cubspline& operator=(cubspline&&)=default; // move assignment

    void buildSpline(); //Calculate the cubic spline and set b, c and d
    double eval(double) const;
    double integ(double) const;
    double deriv(double) const;
    inline double operator()(double z) const {return eval(z);}

};


#endif
