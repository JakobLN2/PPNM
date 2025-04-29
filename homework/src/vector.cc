#include"../include/vector.h"
#include<string>
#include<iostream>
#include<cmath>
#include<stdexcept>


vector& vector::operator*=(double n) {
    for(int i = 0; i < size ; ++i) data[i] *= n;
    return *this;
}
vector& vector::operator/=(double n) {
    for(auto& d : data) d /= n;
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
    double res = 0;
    for(double d : data) res += d*d;
    return std::sqrt(res);
}
void vector::normalize() {
    double len = this->norm();
    for(int i = 0; i < size; ++i) data[i] /= len;
}


void vector::print(std::string s) const {
    std::cout << s << "( ";
    for(auto d : data) std::cout << d << " ";
    std::cout << ")\n";
}

vector vector::copy() const{
    vector res(size);
    for(int i = 0; i < size ; ++i) res[i] = data[i];
    return res;
}

void vector::push_back(double a) {
    data.push_back(a);
    size += 1;
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

vector proj(const vector& a, const vector& b) {
    compatible_exception(a,b);
    vector res = a.copy();
    res *= dot(a,b)/dot(a,a);
    return res;
}

double dot(const vector& a, const vector& b) {
    compatible_exception(a, b);
    double res = 0;
    for(int i = 0 ; i < a.size ; ++i) res += a.data[i] * b.data[i];
    return res;
}

bool approx(const vector& a, const vector& b, double acc,double eps) {
    compatible_exception(a,b);
    for(int i = 0; i < a.size ; ++i) {
        if(std::abs(a[i] - b[i]) <= acc) {
            if(a[i] != 0 && b[i] != 0 && std::abs(a[i] - b[i])/std::max(std::abs(a[i]),(std::abs(b[i]))) > eps) return false;
        } else {return false;}
    }
    return true;
}


bool compatible_exception(const vector& a, const vector& b) {
    if(a.size != b.size) throw std::invalid_argument("operand shapes do not match (" + std::to_string(a.size) + "," + std::to_string(b.size) + ")");
    return true;
}