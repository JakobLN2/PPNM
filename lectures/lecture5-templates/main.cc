#include<iostream>
#include<cmath> //Puts cmath functions into std namespace
#include<complex>
#include<functional>
#include<string>

typedef std::complex<double> complex; //complex is now in the std namespace(?)

template< typename T > //Only works for the next decleration
void echo(T arg){ std::cout << "echo: " << arg << "\n"; }

void fun_of_two(std::function<double(double)> f){std::cout << "f(2) = " << f(2) << "\n";}

int main() {
    echo("string");
    echo(1);
    echo(1.3);
    echo(std::sqrt((complex)(-1))); //complex overloads the mathematical functions so it has implementation for complex numbers

    complex I = std::sqrt((complex)(-1));
    echo(std::sqrt(I));

    std::string s = "original string";
    //takes a void and outputs a void (in parentheses)
    //[] is the capture, where we explicitly state how variables are captured: & means by reference, = is by value, [=,&s] means all are captued by value except s which is by reference
    std::function<void(void)> prints = [&]() {
        std::cout << "prints: s = " << s << "\n";
    };
    prints();
    s = "new string";
    prints(); //We have captured it by reference, so it returns the new string. If we defined [=] it would still return the original string.

    std::function<double(double)> f = [](double x) {return x*x;};
    fun_of_two(f);
    fun_of_two([](double x) {return x*x;}); //Call by anonymous function

    return 0;
}
