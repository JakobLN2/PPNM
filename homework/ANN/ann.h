#ifndef HAVE_ANN_H
#define HAVE_ANN_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../minimization/minimizer.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>


class ann {
    public:
        int n; //Number of neurons
        matrix P; //matrix of weights
        std::function<double(double)> F_act = [](double x){return x*std::exp(-x*x);}; //Output layer activation function
        std::function<double(double,vector)> F_neuron = [&](double x, vector p) {return F_act((x - p[0])/p[1])*p[2];};
        
        ann(int n) : n(n) {
            P = matrix(n,3);
        } // parametrized constructor


        ann() = default; // default constructor
        ann(const ann&)=default; // copy constructor
        ann(ann&&)=default; // move constructor
        ~ann()=default; // destructor
        ann& operator=(const ann&)=default; // copy assignment
        ann& operator=(ann&&)=default; // move assignment

        double eval(double x); //Caculate network responce for input x
        void train(const vector& x, const vector& y);
};



#endif