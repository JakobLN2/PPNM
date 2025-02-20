#include"sfuns.h"

namespace sfuns{

bool approx(double a, double b, double acc, double eps) {
    if(std::abs(a - b) <= acc || std::abs(a - b)/std::max(std::abs(a),std::abs(b)) <= eps) {return true;}
    return false;
}
bool complex_approx(std::complex<double> a, std::complex<double> b, double acc,double eps){
    if(approx(a.real(), b.real(), acc, eps) && approx(a.imag(), b.imag(), acc, eps)) {return true;} //Both real and imaginary part must individually be approximatively equal
    // if((std::abs(a.real() - b.real()) <= acc || std::abs(a.real() - b.real())/std::max(std::abs(a.real()),(std::abs(b.real()))) <= eps) && 
    //    (std::abs(a.imag() - b.imag()) <= acc || std::abs(a.imag() - b.imag())/std::max(std::abs(a.imag()),(std::abs(b.imag()))) <= eps)) {return true;}
    return false;
}
}//namespace sfuns