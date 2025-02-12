using static System.Console;
using complex = System.Numerics.Complex;
// using np = System.Math;
class main{

    //Generic functions, T is the type parameter
    static void echo<T>(T arg) {
        WriteLine($"echo: {arg}"); //Call the "toString" method in arg
    }
    // the + operator is not defined for all types, so the compiler is angry about this one.
    // static void addition<T>(T x, T y) {
    //     WriteLine($"echo: {x + y}");
    // }

    static double integral(System.Func<double,double> f, double a, double b) {
        return f(b) - f(a);
    }

    static void fun_of_one(System.Func<double,double> f) {WriteLine($"f(1) = {f(1)}");}

    static int Main() {
        //Delegate functions
        //A function which takes a double argument (all parameters up to the last) and returns a double (last parameter)
        System.Func<double,double> f = delegate(double x) {return x*x;};
        f = x => x*x; //Lambda function (annonymous function): Syntactic sugar instead of delegate
        f = System.Math.Sin;
        fun_of_one(f);
        WriteLine(integral(f, 0, 3.14/2));
        fun_of_one(x => x*x); //Passing an annonymous function
        
        //Generic function calls
        echo("string");
        echo(1);
        echo(1.23);
        echo(complex.Sqrt(-1)); //the integer -1 can be casted to a complex number: Safe casting

        complex I = complex.Sqrt(-1);
        echo(complex.Pow(I,I));
        echo(complex.Sin(I));

        string s = "original sring"
        System.Action prints = delegate() {
            WriteLine($"prints: s={s}"); //This is a function which takes a variable which is out of scope.
        };
        prints(); 
        s = "new string"
        prints(); //Depends on the language, when the delegate is defined it depends on how the variable is captured 
        //It might hardcode s into it (capture by value), or it might capture it by reference
        //In this case, defining the function with an out-of-scope variable captures it by reference
        
        return 0;
    }
}