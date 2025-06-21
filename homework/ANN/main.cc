#include"../include/vector.h"
#include"../include/matrix.h"
#include"ann.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>
#include<fstream>



std::function<double(double)> F_cosexp = [](double x){return std::cos(5*x - 1)*std::exp(-x*x);};
std::function<double(double)> F_cos = [](double x){return std::cos(x);};
std::function<double(double)> F_square = [](double x){return x*x;};
std::function<double(double)> F_lin = [](double x){return 5*x;};

void makeTrainAnn(std::function<double(double)> F, double xmin, double xmax, int N_sample, int N_nodes, std::string outfile) {
    vector x = linspace(xmin, xmax, N_sample);
    vector y(N_sample);
    for(int i = 0; i < N_sample; ++i) y[i] = F(x[i]);

    ann A(N_nodes);
    A.train(x,y);

    vector x_fit = linspace(xmin, xmax, 5000);
    vector y_fit(x_fit.size);
    for(int i = 0; i < x_fit.size; ++i) y_fit[i] = A.eval(x_fit[i]);
    
    std::cerr << "Saving output to " << outfile << "...\n";
    std::ofstream outstream(outfile, std::ios::trunc); //erase file contents before we write to it
    for(int i = 0; i < N_sample ; ++i) outstream << x[i] << " " << y[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << y_fit[i] << "\n";
    outstream.close();
    std::cerr << "Output saved.\n";
}

int main() {
    int N_sample = 1000,
        N_node = 3;
    double xmin = -3,
           xmax = 3;
    // makeTrainAnn(F_cos, xmin, xmax, N_sample, N_node, "cosexp_data.txt");
    makeTrainAnn(F_cosexp, xmin, xmax, N_sample, N_node, "cosexp_data.txt");
    // N_sample = 600;
    // N_node = 10;
    // makeTrainAnn(F_square, xmin, xmax, N_sample, N_node, "cosexp_data.txt");
    return 0;
}