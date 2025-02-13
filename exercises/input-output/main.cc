#include<iostream>
#include<cmath>
#include<vector>
#include<fstream>

int main(int argc, char* argv[]) {
    std::vector<double> inputs;
    std::ifstream instream; std::ofstream outstream;

    //Read arguments:
    for(int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        //task 1:
        if(arg == "-n" && i + 1 < argc) {
            inputs.push_back(std::stod(argv[i + 1]));   
        }

        // task 3:
        if(arg == "--input" && i + 1 < argc) {instream.open(argv[i + 1]);} //Opens a standard input stream
        if(arg == "--output" && i + 1 < argc) {outstream.open(argv[i + 1]);} //standard output stream
    }

    // task 1:
    // for(double n : inputs) {
    //     std::cout << n << ": " << std::cos(n) << ", " << std::sin(n) << std::endl;
    // }

    // task 2:
    // double x;
    // while(std::cin >> x) {
    //     std::cout << x << ": " << std::cos(x) << ", " << std::sin(x) << std::endl;
    // }

    //task 3:
    if(instream.is_open() && outstream.is_open()) {
        double num;
        while(instream >> num) {
            outstream << num << ": " << std::cos(num) << ", " << std::sin(num) << std::endl;
        }
    } else {
        std::cerr << "Error: could not open files" << std::endl;
        return 1;
    }
    instream.close(); outstream.close();

    return 0;
}