using static System.Console;
class main{
    static int Main() {
        double x = 0;
        double y = x;
        WriteLine($"y = {y}");
        x = 9; //y still has the value 0, since primitive types are passed as values in C#

        int n = 3;
        double[] a = new double[n];
        for(int i=0; i<a.Length; i++) a[i] = i+1;
        double[] b = a; //An array is a class, therefore a is passed as a reference: Changing a also changes b
        b[0] = 666; //a[0] also changes
        WriteLine($"a[0] = {a[0]}");

        return 0;
    }
}