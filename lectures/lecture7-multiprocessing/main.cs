using static System.Console;
class main {
//We give this object to our function, harm, and then it calculates the harmonic sum from start to stop and accumulates it into sum
public class datum {public long start,stop; public double sum;};
//Different threads must not refer to the same object, they must be seperate

//The return type must be void
public static void harm(object obj) {
    datum d = (datum)obj; //Threading must take a general object class, therefore we have to cast it
    d.sum = 0;
    for(long i = d.start+1 ; i <= d.stop; i++) d.sum += 1.0/i;
}

public static int Main(string[] argv) {
    int argc = argv.Length;
    
    int nthreads = 1;
    long nterms = (long)1e9;

    for(int i = 0; i < argc ; i++) {
        string arg = argv[i];
        if(arg == "-threads" && i + 1 < argc) nthreads = int.Parse(argv[i + 1]);
        if(arg == "-terms" && i + 1 < argc) nterms = (long)double.Parse(argv[i + 1]);
    }
    Error.WriteLine($"nthreads = {nthreads} nterms = {nterms}");

    //We keep our threads in a vector:
    var threads = new System.Threading.Thread[nthreads];
    var data = new datum[nthreads];

    for(int i=0; i<nthreads; i++) {
        data[i].start = i*nterms/nthreads;
        data[i].stop = (i + 1)*nterms/nthreads;
    }
    for(int i = 0; i < nthreads; i++) {
        threads[i] = new System.Threading.Thread(harm); //Start the threads
        threads[i].Start(data[i]);
        //We pass the datum object by reference std::ref is safe for this
    }
    foreach(var t in threads) t.Join(); //wait till all threads are done, and sum them
    // for(int i = 0 ; i < nthreads ; i++) threads[i].join();

    double sum=0;
    foreach(datum d in data) sum += d.sum;

    WriteLine($"harmonic sum = {sum}");
    return 0;
} //Main
}