#include"vec.h"
#include<iostream>
#include<random>
#include<string>

int main() {
    std::uniform_real_distribution<double> unif(-10, 10); //random double generator, uniformly spits out numbers between -1000 and 1000
    std::default_random_engine re;
    std::cout << unif(re) << std::endl;

    double ax = unif(re),
           ay = unif(re),
           az = unif(re),
           bx = unif(re),
           by = unif(re),
           bz = unif(re);
    vec a(ax,ay,az),
        b(bx,by,bz),
        test;
    double val_test;
    a.print("a = ");
    b.print("b = ");

    std::cout << "\'<<\' overload: a = " << a << "\n";

    test = a;
    std::cout << "test = a:\n";
    a.print("a    = ");
    test.print("test = ");
    if(approx(a,test)) std::cout << "\'=\' assignment operator : passed\n\n";

    test.set(ax + bx, ay + by, az + bz);
    (a+b).print("a + b = ");
    test.print("test  = ");
    if(approx(a + b, test)) std::cout << "\'+\' Operator : passed\n\n";

    test.set(ax - bx, ay - by, az - bz);
    (a - b).print("a - b = ");
    test.print("test  = ");
    if(approx(a - b, test)) std::cout << "\'-\' Operator : passed\n\n";

    test.set(-ax, -ay, -az);
    (-a).print("-a =   ");
    test.print("test = ");
    if(approx(-a,test)) std::cout << "\'-\' Unary operator : passed\n\n";

    test.set(ax * 3.5, ay * 3.5, az * 3.5);
    (a*3.5).print("a * 3.5 = ");
    (3.5*a).print("3.5 * a = ");
    test.print("test    = ");
    if(approx(3.5*a,test)) std::cout << "\'*\' operator : passed\n\n";
    
    test.set(ax / 4, ay / 4, az / 4);
    (a/4).print("a / 4 = ");
    test.print("test  = ");
    if(approx(a/4,test)) std::cout << "\'/\' operator : passed\n\n";

    val_test = ax * bx + ay * by + az * bz;
    std::cout << "a.dot(b) = " << a.dot(b) << "\n";
    std::cout << "dot(a,b) = " << dot(a,b) << "\n";
    std::cout << "test     = " << val_test << "\n\n";
    
    val_test = std::sqrt(std::pow(ax,2) + std::pow(ay,2) +std::pow(az,2));
    std::cout << "a.norm() = " << a.norm() << "\n";
    std::cout << "test     = " << val_test << "\n\n";

    a += b;
    std::cout << "a += b  :  a = " << a;
    
    a -= b;
    std::cout << "a -= b  :  a = " << a;

    a *= 2.5;
    std::cout << "a *= 2.5 : a = " << a;
    
    a /= 5;
    std::cout << "a /= 5  :  a = " << a;





    


    return 0;
}

