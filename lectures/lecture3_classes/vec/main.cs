using static System.Console;
class main{
    static int Main() {
        double[] a = new double[3];
        for(int i = 0; i < a.Length ; i++) a[i] = i+1;
        foreach(double ai in a) WriteLine(ai);
        vec v = new vec(); //Use the default constructor
        WriteLine($"{v.x}, {v.y}, {v.z}");
        v.x = 1; v.y = 2; v.z = 3;
        WriteLine($"{v.x}, {v.y}, {v.z}");
        return 0;
    }
}