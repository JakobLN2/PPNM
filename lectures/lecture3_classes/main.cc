#include<iostream>
#include<vector>

//main must be in the global scope
int main() {
    double x = 5;
    double y = x; //in c++ this passes a value
    double& z = x; //This passes a reference, double& means "reference to double" which works exactly like a double
    x = 9; //y is still 5, z is also 9

    int n = 3;
    std::vector<double> a(3);
    for(int i = 0; i < a.size(); i++) a[i] = i+1;
    auto b = a; //This = calls the "copy constructor" of the type. Depending on what the programmer did, this could pass either a value or reference
    //auto& b = a; definently passes a reference

    //Auto means that the compiler must figure out the type of a and give it to b
    //std::vector<double> b = a is the equivalent statement

    return 0;
}