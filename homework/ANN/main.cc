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
std::function<double(double)> F_cube = [](double x){return x*x*x;};
std::function<double(double)> F_lin = [](double x){return 5*x;};

void makeTrainAnn(std::function<double(double)> F, double xmin, double xmax, int N_sample, int N_nodes, std::string F_act, std::string outfile) {
    vector x_func = linspace(xmin - 1, xmax + 1, 2500);
    vector y_func(x_func.size);
    for(int i = 0; i < x_func.size; ++i) y_func[i] = F(x_func[i]); //Used to compare extrapolation

    vector x = linspace(xmin, xmax, N_sample);
    vector y(N_sample);
    for(int i = 0; i < N_sample; ++i) y[i] = F(x[i]);

    ann A(N_nodes, F_act,x,y);

    vector x_fit = linspace(xmin - 1, xmax + 1, 5000);
    vector y_fit(x_fit.size);
    for(int i = 0; i < x_fit.size; ++i) y_fit[i] = A.eval(x_fit[i]);
    
    std::cerr << "Saving output to " << outfile << "...";
    std::ofstream outstream(outfile, std::ios::trunc); //erase file contents before we write to it
    for(int i = 0; i < x_func.size ; ++i) outstream << x_func[i] << " " << y_func[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < N_sample ; ++i) outstream << x[i] << " " << y[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << y_fit[i] << "\n";
    outstream.close();
    std::cerr << " Output saved.\n";
}

void makeTrainAnnb(std::function<double(double)> F, double xmin, double xmax, int N_sample, int N_nodes, std::string outfile) {
    vector x_func = linspace(xmin - 1, xmax + 1, 5000);
    vector y_func(x_func.size);
    for(int i = 0; i < x_func.size; ++i) y_func[i] = F(x_func[i]);


    vector x = linspace(xmin, xmax, N_sample),
           y(N_sample);
    for(int i = 0; i < N_sample; ++i) y[i] = F(x[i]);

    ann A(N_nodes,"gaussian wavelet",x,y);

    vector x_fit = linspace(xmin - 1, xmax + 1, 5000),
           y_fit(x_fit.size), //Interpolated function values
           dy_fit(x_fit.size), ddy_fit(x_fit.size), //First and second order derivative
           Y_fit(x_fit.size); //Integrated function
    for(int i = 0; i < x_fit.size; ++i) {
        vector res = A.eval_derivs(x_fit[i]);
        y_fit[i] = res[0];
        dy_fit[i] = res[1];
        ddy_fit[i] = res[2];
        Y_fit[i] = res[3];
    }

    std::cerr << "Saving output to " << outfile << "...";
    std::ofstream outstream(outfile, std::ios::trunc); //erase file contents before we write to it
    for(int i = 0; i < x_func.size ; ++i) outstream << x_func[i] << " " << y_func[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < N_sample ; ++i) outstream << x[i] << " " << y[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << y_fit[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << dy_fit[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << ddy_fit[i] << "\n";
    outstream  << "\n\n";
    for(int i = 0; i < x_fit.size ; ++i) outstream << x_fit[i] << " " << Y_fit[i] << "\n";
    outstream.close();
    std::cerr << " Output saved.\n";
}

int main() {
    double xmin = -1,
           xmax = 1;
    int N_sample = 600,
        N_node = 5;
    std::string F_act = "gaussian wavelet"; //Which activation function to use, only gaussian wavelet has derivatives and antiderivatives implemented

    std::cout << "Interpolating a cos(5x - 1)*exp(-x*x) from -1 to 1 using " << F_act << " as the activation function\n";
    makeTrainAnn(F_cosexp, xmin, xmax, N_sample, N_node, F_act, "cosexp_data.txt");
    std::cout << "Output is graphed in 'Plot.cosexp.svg'\n";

    F_act = "gaussian";
    std::cout << "\nInterpolating a cos(5x - 1)*exp(-x*x) from -1 to 1 using " << F_act << " as the activation function\n";
    makeTrainAnn(F_cosexp, xmin, xmax, N_sample, N_node, F_act, "cosexp_data_2.txt");
    std::cout << "Output is graphed in 'Plot.cosexp_2.svg'\n";
    std::cout << "The two activation fucntions both seem able to describe the function adequately, though the gaussian wavelet is slightly better at extrapolating." <<
                 "Which is expected as the training function is also a wavelet.\n";
    
    F_act = "gaussian wavelet";
    N_node = 12;
    N_sample = 600;
    std::cout << "\n\nInterpolating a x*x using " << F_act << " as the activation function\n";
    makeTrainAnnb(F_lin, xmin, xmax, N_sample, N_node, "square_data.txt");
    std::cout << "Derivatives and antiderivative is estimated, output is graphed in 'Plot.square.svg'\n";
    std::cout << "Requires significantly more nodes to be usable and it is terrible at extrapolating, which is as expected.\n";
    return 0;
}