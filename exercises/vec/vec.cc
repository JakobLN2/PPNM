#include<cmath>
#include<string>
#include<iostream>
#include"vec.h"

//No need to define the class again?
//We don't implement constructors and methods which are marked default in the header file
    //Already have implementation therein

vec& vec::operator+=(const vec& a) { //Add assignment
    x += a.x; //modify the vector
    y += a.y;
    z += a.z;
    return *this;
}

vec& vec::operator-=(const vec& a) { //Subtract assignment
    x -= a.x;
    y -= a.y;
    z -= a.z;
    return *this;
}

vec& vec::operator*=(double k) { //Multiplication assignment
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

vec& vec::operator/=(double k) { //Division assignment
    x /= k;
    y /= k;
    z /= k;
    return *this;
}

double vec::dot(const vec& a) {
    return x * a.x + y * a.y + z * a.z;
}

double vec::norm() {
    return std::sqrt(std::pow(x,2) + std::pow(y,2) + std::pow(z,2));
}

void vec::print(std::string s) const { //Default parameters are apparantly only given in the .h file?
    std::cout << s << "(" << x << ", " << y << ", " << z << ")" << std::endl; //To end line or not to end line
}

std::ostream& operator<<(std::ostream& os, const vec& a) { //toString method?
    os << "(" << a.x << ", " << a.y << ", " << a.z << ")" << std::endl;
    return os;
}

//should not be a member function in order to take more than one argument
//None of these should change the input vectors (const)
vec operator+(const vec& a, const vec& b) { //Plus operator
    return vec(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec operator-(const vec& a, const vec& b) { //Minus operator
    return vec(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec operator-(const vec& a) { //Unary minus operator
    return vec(-a.x, -a.y, -a.z);
}

vec operator*(const vec& a, double k) { //Multiplication operator (from the right)
    return vec(a.x * k, a.y * k, a.z * k);
}

vec operator*(double k, const vec& a) { //Multiplication operator (from the left)
    return vec(a.x * k, a.y * k, a.z * k);
}

vec operator/(const vec& a, double k) { //Division operator
    return vec(a.x/k, a.y/k, a.z/k);
}

bool approx(const vec& a, const vec&b, double acc, double eps){
    if((std::abs(a.x - b.x) <= acc || std::abs(a.x - b.x)/std::max(std::abs(a.x),(std::abs(b.x))) <= eps) && //All components must individually be approximatively equal
       (std::abs(a.y - b.y) <= acc || std::abs(a.y - b.y)/std::max(std::abs(a.y),(std::abs(b.y))) <= eps) && //This is kind of ugly in my honest opinion, but i don't want to think too much about it
       (std::abs(a.z - b.z) <= acc || std::abs(a.z - b.z)/std::max(std::abs(a.z),(std::abs(b.z))) <= eps)) {return true;}
       return false;
}

double dot(const vec& a, const vec& b) { //Dot product between two vectors
    return a.x * b.x + a.y * b.y + a.z * b.z;
}