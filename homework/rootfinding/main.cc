#include"../include/vector.h"
#include"../include/matrix.h"
#include"roots.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>


auto F = [](vector x){return x - 1.0;}; //root at x = 1

int main() {
    vector a({0.0});
    vector res = newton(F,a,1.0);

    return 0;
}