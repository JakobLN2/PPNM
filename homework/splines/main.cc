#include"interp.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<random>
#include<iostream>
#include<cmath>

int main() {
    vector xs(10), ys(10);
    for(int i = 0; i < 10; ++i) {
        xs[i] = i;
        ys[i] = std::cos(i);
        std::cout << xs[i] << " " << ys[i] << "\n";
    }
    

    return 0;
}