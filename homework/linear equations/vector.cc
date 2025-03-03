#include"vector.h"
#include<string>
#include<iostream>
#include<cmath>


vector& vector::operator*=(double n) {
    // for(int i = 0 ; i < size ; ++i) data[i] *= n;
    for(auto& d : data) d *= n;
    return *this;
}
vector& vector::operator/=(double n) {
    // for(int i = 0 ; i < size ; ++i) data[i] /= n;
    for(auto& d : data) d /= n;
    return *this;
}
double vector::norm() {
    double res;
    for(auto& d : data) res += d*d;
    return std::sqrt(res);
}



void vector::print(std::string s) const {
    std::cout << s;
    for(auto d : data) std::cout << d << ", ";
    std::cout << "\n";
}

vector operator+(const vector& a, const vector& b) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] + b.data[i];
    return res;
}
vector operator-(const vector& a, const vector& b) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] - b.data[i];
    return res;
}
vector operator-(const vector& a) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = -a.data[i];
    return res;
}

vector operator*(const vector& a, double n) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] * n;
    return res;
}
vector operator*(double n, const vector& a) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] * n;
    return res;
}
vector operator/(double n, const vector& a) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] / n;
    return res;
}


double dot(const vector& a, const vector& b) {
    // assert(a.size == b.size); //Check that they are compatible
    double res = 0;
    for(int i = 0 ; i < a.size ; ++i) res += a.data[i] * b.data[i];
    return res;
}