using static System.Console; //Static class which is just a collection of functions to work with the console
using static System.Math;

static class main{
    static string class_variable = "class variable"; //This variable is in the "class scope", which then exists in all lower scopes. It can be used in functions e.g.
    // In a class, everythin is by default private, in a structure it is by default public
    static double square(double x) {
        double tmp = 1;
        //{double tmp = 2;} //This is called shadowing the only difference in scoping in c# and c++ is that you cannot "block shadow" in c#
        double result = x*x*tmp; //This variable is in the function "square" scope, i does not exist in other functions in the class
        return result;
    }
    static int Main(string[] args) {
        System.Console.WriteLine("hello");
        System.Console.WriteLine(class_variable);

        double x = System.Math.Sin(1.0);
        double y = Cos(1.0);
        System.Console.WriteLine($"x = {x}, y = {y}"); //Stream interpolation, just like python f strings.

        
        return 0; //Everything went well, f something went wrong and there is no point in continuing the program, return 1

    }
}