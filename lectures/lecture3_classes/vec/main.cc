#include<iostream>
#include"vec.h"
#include<vector>

int main() {
    vec v;
    v.x = v.y = 6;
    v.z = 3;
    std::cout << "v = " << v.x << v.y << v.z << std::endl;
}