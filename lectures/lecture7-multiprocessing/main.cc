#include<iostream>
#include<thread>
#include<string>
#include<vector>

//We give this object to our function, harm, and then it calculates the harmonic sum from start to stop and accumulates it into sum
struct datum {int start,stop; double sum;};
//Different threads must not refer to the same object, they must be seperate

//The return type must be void
void harm(datum& d) {
    d.sum = 0;
    for(long i = d.start+1 ; i <= d.stop; i++) d.sum += 1.0/i;
}

int main(int argc, char* argv[]) {
    int nthreads = 1;
    long nterms = (long)1e8;

    for(int i = 0; i < argc ; i++) {
        std::string arg = argv[i];
        if(arg == "-threads" && i + 1 < argc) nthreads = std::stoi(argv[i + 1]);
        if(arg == "-terms" && i + 1 < argc) nterms = (long)std::stod(argv[i + 1]);
    }
    std::cerr << "nthreads = " << nthreads << " nterms = " << nterms << "\n";

    //We keep our threads in a vector:
    std::vector<std::thread> threads(nthreads);
    std::vector<datum> data(nthreads);

    for(int i=0; i<nthreads; i++) {
        data[i].start = i*nterms/nthreads;
        data[i].stop = (i + 1)*nterms/nthreads;
    }
    for(int i = 0; i < nthreads; i++) {
        threads[i] = std::thread(harm, data[i]); //Start the threads
    }
    // for(std::thread t : threads) t.join();
    for(int i=0 ; i < nthreads < i++) threads[i].join();
    double sum=0;
    for(datum d : data) sum += d.sum;

    std::cout << "harmonic sum = " << sum << std::endl;
}