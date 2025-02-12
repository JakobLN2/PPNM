#include<iostream> //Look at the system header file called iostream and use the definitions there - <> means that it only looks in the system files (PATH)
#include<cmath> //Put all mathematical functions into std namespace - Many compilers also bring it into the global scope, but we usually prefix with std:: just to be sure
#include"sfuns.h" //"" means that the compiler also looks in the current directory for this file

//The main function should be in the global scope, not in a name space or class
// int main(int argc, char* argv[]) {
int main() {
    //argc is argument count
    //char* argv is the only time we use pointers - it is just a pure pointer, it has no idea what it points to
    std::cout << "hello" << std::endl; 

    double x = std::sin(1.0); //std namespace
    double y = cos(1.0); //Global namespace (kikset)
    double z = sfuns::fgamma(1.0);
    std::cout << "x = " << x << " y = " << y << " z = " << z << std::endl;
    return 0;
}