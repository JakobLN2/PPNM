#include"../include/matrix.h"
#include"../include/vector.h"
#include"quad.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

std::function<double(double)> f_sqrt = [](double x){return std::sqrt(x);};
std::function<double(double)> f_sqrt_inv = [](double x){return 1.0/std::sqrt(x);};
std::function<double(double)> f_3 = [](double x){return std::sqrt(1-x*x);};
std::function<double(double)> f_4 = [](double x){return std::log(x)/std::sqrt(x);};

std::function<double(double)> erf_1 = [] (double x) {return std::exp(-x*x);};
std::function<std::function<double(double)>(double)> erf_2 = [](double x) {return [=](double t) {return std::exp(-std::pow(x + (1-t)/t,2))/t/t;};};
double erf(double x, double acc = 0.01, double eps = 0.01) {
    if(x < 0) return -erf(-x, acc, eps);
    if(0 <= x && x <= 1) return M_2_SQRTPI*std::get<0>(integrate(erf_1, 0.0, x, acc, eps));
    return 1 - M_2_SQRTPI*std::get<0>(integrate(erf_2(x), 0, 1, acc, eps));
};

std::function<double(double)> f_gauss = [](double x) {return 1/std::sqrt(2*M_PI)*std::exp(-0.5*x*x);};
std::function<double(double)> f_xx = [](double x) {return 1/x/x;};
std::function<double(double)> f_xsqrtx = [](double x) {return 1/(1 + x)/std::sqrt(x);};

int main() {
    std::tuple<double,double,int> res;
    double acc, eps,tol,tol_num;
    double a,b;
    double inte, err;
    int eval;
    double q_analytic;

    /* sqrt(x) */
    a = 0, b = 1;
    acc = 1e-4, eps = 1e-4;
    std::cout << "acc = " << acc << ", eps = " << eps << "\n";
    res = integrate(f_sqrt, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = 2.0/3.0*(std::pow(b,3.0/2.0) - std::pow(a,3.0/2.0));
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "∫_"<<a<<"^"<<b<<" dx sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations\n";

    /* 1/sqrt(x) */
    a = 0, b = 1;
    res = integrate(f_sqrt_inv, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = 2.0*(std::pow(b,0.5) - std::pow(a,0.5));
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx 1/sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations\n";

    /* sqrt(1-x^2) */
    a = 0, b = 1;
    res = integrate(f_3, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = M_PI_4;
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx sqrt(1 - x*x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations\n";

    /* ln(x)/sqrt(x) */
    a = 0.0, b = 1.0;
    res = integrate(f_4, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = -4.0;
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx ln(x)/sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations\n";

    /* Error function */
    double erf_x1 = 0.84270079294971486934122063;
    vector erf_x, erf_y;
    for(double i = -3.0; i < 3.0; i += 1.0/8.0) {
        erf_x.push_back(i);
        erf_y.push_back(erf(i, 0.01, 0.01));
    }
    vector erf_acc_x, erf_acc_y;
    for(int i = 0; i < 52; ++i) {
        erf_acc_x.push_back(std::pow(0.5,i));
        erf_acc_y.push_back(std::abs(erf_x1 - erf(1,erf_acc_x[i],0)));
    }
    

    /* Clenshaw-Curtis integration */
    std::cout << "\nTask b) Clenshaw-Curtis integration:\n";

    /* sqrt(x) */
    a = 0, b = 1;
    acc = 1e-4, eps = 1e-4;
    std::cout << "acc = " << acc << ", eps = " << eps << "\n";
    res = integrate_CC(f_sqrt, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = 2.0/3.0*(std::pow(b,3.0/2.0) - std::pow(a,3.0/2.0));
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations (Scipy: 231)\n";
    
    /* ln(x)/sqrt(x) */
    a = 0.0, b = 1.0;
    res = integrate_CC(f_4, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = -4.0;
    tol = acc + eps * std::abs(q_analytic);
    tol_num = std::abs(q_analytic - inte)*(1 + 1/std::abs(q_analytic));
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx ln(x)/sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations (Scipy: 315)\n";
    
    // std::cout << "\nClenshaw-Curtis method has comparable evaluations to SciPy's routines.\n";
    


    std::cout << "\nInfinite limit integrals:\n";
    acc = 1e-4, eps = 1e-4;
    std::cout << "acc = " << acc << ", eps = " << eps << "\n";
    /* Normal distribution */
    a = -std::numeric_limits<double>::infinity(), b = std::numeric_limits<double>::infinity();
    res = integrate_CC(f_gauss, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = 1;
    tol = acc + eps * std::abs(q_analytic);
    std::cout << "\n1/sqrt(2pi)∫_"<<a<<"^"<<b<<" dx exp(-x*x/2) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations (SciPy: 150)\n";
    
    /* 1/x/x */
    a = 1, b = std::numeric_limits<double>::infinity();
    res = integrate_CC(f_xx, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = 1;
    tol = acc + eps * std::abs(q_analytic);
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx 1/x/x = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations (SciPy: 15)\n";
    
    /* 1/(x + 1)/sqrt(x) */
    a = 0, b = std::numeric_limits<double>::infinity();
    res = integrate_CC(f_xsqrtx, a, b, acc, eps);
    inte = std::get<0>(res);
    err = std::get<1>(res);
    eval = std::get<2>(res);
    q_analytic = M_PI;
    tol = acc + eps * std::abs(q_analytic);
    std::cout << "\n∫_"<<a<<"^"<<b<<" dx 1/(x + 1)/sqrt(x) = " << inte << " +/- " << err << ", expected " << q_analytic << "\n";
    std::cout << "|calculated - analytic| <= est. error ?= " << (std::abs(inte - q_analytic) <= err) << "\n";
    std::cout << "Combined absolute and relative error: " << tol_num << ",  Promised tolerance: " << tol << "  :  error <= tol ?= " << (tol_num <= tol) << "\n";
    std::cout << "In " << eval << " evaluations (SciPy: 285)\n";
    

    std::cout << "\n\n";
    for(int i = 0; i < erf_x.size; ++i) std::cout << erf_x[i] << ", " << erf_y[i] << "\n";
    std::cout << "\n\n";
    for(int i = 0; i < erf_acc_x.size; ++i) std::cout << erf_acc_x[i] << ", " << erf_acc_y[i] << "\n";



    return 0;
};
