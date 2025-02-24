#include"vector.h"
#include<string>
#include<iostream>

// template<typename T>
// vector<T> operator+(const vector<T>& a, const vector<T>& b) {
//     vector<T> res(a.size());
//     for(int i = 0 ; i < a.size() ; ++i) res[i] = a[i] + b[i];
//     return res;
// }

template<typename T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
    vector<T> res(a.size);
    for(int i = 0; i < a.size ; ++i) res[i] = a[i] + b[i];
    return res;
}

template<typename T>
vector<T>& vector<T>::operator*=(double n) {
    for(T& d : data) d *= n;
    return *this;
}

template<typename T>
void vector<T>::print(std::string s) const {
    // std::cout << s;
    std::cout << "mojn gutter";
    // for(T d : data) std::cout << d << ", ";
    // for(int i = 0 ; i < size ; ++i) std::cout << data[i] << ", ";
    std::cout << std::endl;
}

// void TemporaryFunction ()
// {
//     vector<int> TempObj;
// }