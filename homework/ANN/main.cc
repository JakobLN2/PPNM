#include"../include/vector.h"
#include"../include/matrix.h"
#include"ann.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>
#include<fstream>



std::function<double(double)> F_cos = [](double x){return std::cos(5*x-1)*std::exp(-x*x);};

void makeTrainAnn(std::function<double(double)> F, double xmin, double xmax, int N_sample, int N_nodes, std::string outfile) {
    double dx = (xmax - xmin)/N_sample;
    vector x(N_sample), y(N_sample);
    for(int i = 0; i < N_sample; ++i) {
        x[i] = xmin + i*dx;
        y[i] = F(x[i]);
    }
    ann A(N_nodes);
    A.train(x,y);

    vector x_fit(5000);
    vector y_fit(x_fit.size);
    double dx_fit = dx*N_sample/x_fit.size;
    for(int i = 0; i < x_fit.size; ++i) {
        x_fit[i] = xmin + i * dx_fit;
        y_fit[i] = A.eval(x_fit[i]);
    }
    std::ofstream outstream(outfile, std::ios::trunc); //erase file contents before we write to it
    for(int i = 0; i < N_sample ; ++i) outstream << x[i] << " " << y[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << y_fit[i] << "\n";
    outstream.close();

}

int main() {
    int N_sample = 100,
        N_node = 4;
    double xmin = -3,
           xmax = 3;
    makeTrainAnn(F_cos, xmin, xmax, N_sample, N_node, "cosexp_data.txt");
    
    return 0;
}