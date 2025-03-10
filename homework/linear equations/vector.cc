#include"vector.h"
#include<string>
#include<iostream>
#include<cmath>
#include<stdexcept>


vector& vector::operator*=(double n) {
    for(auto& d : data) d *= n;
    return *this;
}
vector& vector::operator/=(double n) {
    for(auto& d : data) d /= n;
    return *this;
}
vector& vector::operator+=(double n) {
    for(auto& d : data) d += n;
    return *this;
}
vector& vector::operator-=(double n) {
    for(auto& d : data) d -= n;
    return *this;
}


vector& vector::operator+=(const vector& a) {
    compatible_exception(*this, a);
    for(int i = 0 ; i < size ; ++i) data[i] += a.data[i];
    return *this;
}
vector& vector::operator-=(const vector& a) {
    compatible_exception(*this, a);
    for(int i = 0 ; i < size ; ++i) data[i] -= a.data[i];
    return *this;
}


double vector::norm() {
    double res;
    for(auto& d : data) res += d*d;
    return std::sqrt(res);
}



void vector::print(std::string s) const {
    std::cout << s;
    for(auto d : data) std::cout << d << " ";
    std::cout << "\n";
}

vector operator+(const vector& a, const vector& b) {
    compatible_exception(a, b);
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] + b.data[i];
    return res;
}
vector operator-(const vector& a, const vector& b) {
    compatible_exception(a, b);
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
vector operator/(const vector& a, double n) {
    vector res(a.size);
    for(int i = 0 ; i < a.size ; ++i) res[i] = a.data[i] / n;
    return res;
}


double dot(const vector& a, const vector& b) {
    compatible_exception(a, b);
    double res = 0;
    for(int i = 0 ; i < a.size ; ++i) res += a.data[i] * b.data[i];
    return res;
}

bool compatible_exception(const vector& a, const vector& b) {
    if(a.size != b.size) throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.size) + "," + std::to_string(b.size) + ")");
    return true;
}