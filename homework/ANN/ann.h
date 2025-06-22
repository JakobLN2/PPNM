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
#include<exception>

class ann {
    public:
        int n; //Number of neurons
        vector px; //Vector of weights used during training
        matrix P; //matrix of weights for a nice representation
        std::string act; //which activation function to use
        
        std::function<double(double)> F_act, dF_act; //Activation function used in hidden neurons and its derivative
        std::function<double(double,vector)> F_neuron;
        std::function<double(double,double)> a_k;
        std::function<double(double,double,vector)> dL_da, dL_db, dL_dw; //Derivatives of loss function

        
        ann(int n, std::string act) : n(n), act(act) {
            P = matrix(n,3);
            px = vector(3*n);
            
            if(act == "gaussian wavelet") {  /*Gaussian wavelet*/
                F_act = [](double x){return x*std::exp(-x*x);};
                dF_act = [](double x){return (1 - 2*x*x)*std::exp(-x*x);};
            } else if(act == "gaussian") { /*Gaussian*/
                F_act = [](double x){return std::exp(-x*x);};
                dF_act = [](double x){return -2*x*std::exp(-x*x);};
            } else if(act == "wavelet") { /*Wavelet*/
                F_act = [](double x){return std::cos(5*x)*std::exp(-x*x);};
                dF_act = [](double x){return -(5*std::sin(5*x) + 2*x*std::cos(5*x)) * std::exp(-x*x);};
            } else {throw std::invalid_argument("Unknown activation function, accepted values are: 'gaussian wavelet', 'gaussian', 'wavelet'");};

            F_neuron = [&](double x, vector p) {return F_act((x - p[0])/p[1])*p[2];};

            a_k = [&](double x, double y) {
                double a = -y;
                for(int i = 0; i < px.size/3; ++i) a+= F_act((x - px[3*i])/px[3*i+1])*px[3*i+2];
                return a;
            };
            dL_da = [&](double x,double y, vector p) {return -2 * a_k(x,y) * p[2]/p[1] * dF_act((x - p[0])/p[1]);};
            dL_db = [&](double x,double y, vector p) {return -2 * a_k(x,y) * p[2]/p[1]/p[1] * dF_act((x - p[0])/p[1])*(x - p[0]);};
            dL_dw = [&](double x,double y, vector p) {return  2 * a_k(x,y) * F_act((x - p[0])/p[1]);};
        }
        ann(int n, vector x, vector y) : ann(n, "gaussian wavelet") {train(x,y);} //additional parametrized constructors
        ann(int n) : ann(n, "gaussian wavelet") {}
        ann(int n, std::string act, vector x, vector y) : ann(n, act) {train(x,y);}

        ann() = default; // default constructor
        ann(const ann&)=default; // copy constructor
        ann(ann&&)=default; // move constructor
        ~ann()=default; // destructor
        ann& operator=(const ann&)=default; // copy assignment
        ann& operator=(ann&&)=default; // move assignment

        double eval(double x) const; //Calculate network response for input x
        vector eval2(double x) const;
        void train(const vector& x, const vector& y, double acc = 1e-5); //There is diminishing returns so we add an acc, if the cost improves less than acc, terminate stop training
        vector gradient(const vector&, const vector&, const vector&);
};



#endif