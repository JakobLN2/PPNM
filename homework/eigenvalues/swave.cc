#include"EVD.h"
#include"../include/matrix.h"
#include"../include/vector.h"
#include<random>
#include<iostream>

int main(int argc, char** argv) {
    double rmax = 10,
           dr = 0.3;
    int wf = 0; //Save data for the first wf eigenfunctions, if 0 don't.

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];

        if(arg == "-rmax" && i+1<argc) rmax = std::stod(argv[i + 1]);
        if(arg == "-dr" && i+1<argc) dr = std::stod(argv[i + 1]);
        if(arg == "-wf" && i+1<argc) wf = std::stoi(argv[i + 1]);

    }

    int N = (int)(rmax/dr) - 1;
    matrix H(N,N);
    vector r(N);
    for(int i = 0; i < N; ++i) r[i] = dr * (i+1);
    for(int i = 0; i < N - 1; ++i) {
        H(i,i) = 1/dr/dr - 1/r[i];
        H(i, i+1) = -0.5/dr/dr;
        H(i + 1, i) = -0.5/dr/dr;
    }
    H(N - 1, N - 1) = 1/dr/dr - 1/r[N - 1];
    EVD evd(H);
    evd.cyclic();
    // H.print("H = ");
    // evd.V.print("V = ");
    // evd.D.print("D = ");

    std::cout << rmax << "," << dr << "," << evd.D(0,0) << std::endl;

    if(wf > 0) {
        std::cout << "\n\n";
        for(int k = 0; k < wf; ++k) {
            vector f_r = evd.V.getCol(k)/std::sqrt(dr);
            for(int i = 0; i < N; ++i) {
                std::cout << r[i] << "," << f_r[i] << "\n";
            }
            std::cout << "\n\n";
        }
    }

    return 0;
}