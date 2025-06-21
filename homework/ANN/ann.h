#ifndef HAVE_ANN_H
#define HAVE_ANN_H

#include"../include/vector.h"
#include"../include/matrix.h"
#include"../minimization/minimizer.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>
#include<random>


class ann {
    public:
        int n; //Number of neurons
        matrix P; //matrix of weights
        // std::function<double(double)> F_act, dF_act; //Activation function used in hidden neurons and its derivative
        
        std::function<double(double)> F_act, dF_act;
        std::function<double(double,vector)> F_neuron;
        std::function<double(double,double,vector)> dL_da, dL_db, dL_dw;

        /*Gaussian wavelet*/
        // std::function<double(double)> F_act = [](double x){return x*std::exp(-x*x);}; 
        // std::function<double(double)> dF_act = [](double x){return (1 - 2*x*x)*std::exp(-x*x);};
        
        // std::function<double(double,vector)> F_neuron = [&](double x, vector p) {return F_act((x - p[0])/p[1])*p[2];}; //neuron activation function
        // /*Analytical loss function derivatives*/
        // std::function<double(double,double,vector)> dL_da = [&](double x,double y, vector p) {return -2*(F_neuron(x,p) - y) * p[2] * dF_act((x - p[0])/p[1])/p[1];};
        // std::function<double(double,double,vector)> dL_dw = [&](double x,double y, vector p) {return 2*(F_neuron(x,p) - y) * F_act((x - p[0])/p[1]);};
        // std::function<double(double,double,vector)> dL_db = [&](double x,double y, vector p) {return -2*(F_neuron(x,p) - y) * p[2] * dF_act((x - p[0])/p[1])*(x - p[0])/p[1]/p[1];};
        
        
        ann(int n) : n(n) {
            P = matrix(n,3);
            
            // /*Gaussian wavelet*/
            // F_act = [](double x){return x*std::exp(-x*x);};
            // dF_act = [](double x){return (1 - 2*x*x)*std::exp(-x*x);};

            /*Gaussian*/
            F_act = [](double x){return std::exp(-x*x);};
            dF_act = [](double x){return -2*x*std::exp(-x*x);};

            // /*Gaussian wavelet*/
            // F_act = [](double x){return std::cos(5*x)*std::exp(-x*x);};
            // dF_act = [](double x){return -(5*std::sin(5*x) + 2*x*std::cos(5*x)) * std::exp(-x*x);};
           
           
            F_neuron = [&](double x, vector p) {return F_act((x - p[0])/p[1])*p[2];};


            dL_da = [&](double x,double y, vector p) {return -2 * (F_neuron(x,p) - y) * p[2] * dF_act((x - p[0])/p[1])/p[1];};
            dL_db = [&](double x,double y, vector p) {return -2 * (F_neuron(x,p) - y) * p[2] * dF_act((x - p[0])/p[1])*(x - p[0])/p[1]/p[1];};
            dL_dw = [&](double x,double y, vector p) {return  2 * (F_neuron(x,p) - y) * F_act((x - p[0])/p[1]);};
        }
        ann(int n, vector x, vector y) : n(n) {
            P = matrix(n,3);
            train(x,y);
        } // parametrized constructor


        ann() = default; // default constructor
        ann(const ann&)=default; // copy constructor
        ann(ann&&)=default; // move constructor
        ~ann()=default; // destructor
        ann& operator=(const ann&)=default; // copy assignment
        ann& operator=(ann&&)=default; // move assignment

        double eval(double x); //Calculate network responce for input x
        void train(const vector& x, const vector& y);
        vector gradient(const vector&, const vector&, const vector&);
};



#endif