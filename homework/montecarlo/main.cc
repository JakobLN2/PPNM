#include"../include/vector.h"
#include"mcInt.h"
#include<iostream>
#include<cmath>
#include<string>
#include<functional>

auto f_const = [](vector x){return 1;};
auto f_ucirc = [](vector x){
    if(x.norm() <= 1.0) return 1;
    else return 0;
};

auto f_coses = [](vector x) {
    if((0 <= x[0] && x[0] <= M_PI) ||
        (0 <= x[1] && x[1] <= M_PI) ||
        (0 <= x[2] && x[2] <= M_PI)) return std::pow(M_PI,-3) * 1/(1 - std::cos(x[0])*std::cos(x[1])*std::cos(x[2]));
    return 0.0;
};

auto f_gauss2d = [](vector x) {
    return std::exp(-std::pow(x[0] - 1.0, 2)/2 - std::pow((x[1] - 0.5)/0.5, 2)/2);
};

std::string reportResult(const std::tuple<double, double>& res, double q_analytic, int N) {
    double q = std::get<0>(res),
           err = std::get<1>(res);
    std::string out = 
        std::to_string(q) + " +/- " + std::to_string(err) + ", expected: " + std::to_string(q_analytic) + "\n"\
        "\twith " + std::to_string(N) + " samples\n" + \
        "\t|MC - analytic|/err = " + std::to_string(std::abs(q - q_analytic) / err) + "\n";
    return out;
}

int task_a() {
    std::cout << "Task a, plain Monte Carlo integration.\n";
    
    vector a,b;
    int N;
    double q,err;
    double q_analytic;
    std::tuple<double,double> res;

    /* Constant function */
    a = vector({-1,-1,-1});
    b = vector({1,1,1});
    N = 1000;
    res = plainMC(f_const, a,b,N);
    q = std::get<0>(res);
    err = std::get<1>(res);
    std::cout << "∫_-1^1∫_-1^1∫_-1^1 1 = " << q << " +/- " << err << "\n"; 
    std::cout << "\twith " << N << " samples\n";
    std::cout << "\tIs calculated exactly, which was our one requirement\n";

    
    /* Unit circle */
    a = vector({-1,-1});
    b = vector({1,1});
    N = 1e5;
    res = plainMC(f_ucirc, a,b,N);
    std::cout << "\n∫unit circle = " << reportResult(res, M_PI, N);
    std::cout << "Since the error is a statistical deviation, it is expected that the result is within one standard deviation of the actual value ~67\% of the time, and within 2 deviations ~95\% of the time\n";
    std::cout << "Error as a function of sample points is plotted in Plot.err.svg\n" <<
                "Though it seems underestimated for N <~ 1e5, where there may not be enough samples for proper convergence.\n" <<
                "The first two points also have a extremely low estimated error, which is likely due to random chance from having few samples\n" <<
                "The actual error convincingly follows a 1/sqrt(N) dependency. Note that the first 3 points are not included in the fit due to low number of samples\n";
    
    /* unit sphere */
    a = vector({-1.05,-1.05,-1.05});
    b = vector({1.05,1.05,1.05});
    N = 1e6;
    res = plainMC(f_ucirc, a,b,N);
    q_analytic = 4.0/3.0*M_PI;
    std::cout << "\n∫unit sphere = " << reportResult(res, q_analytic, N);
    
    /* unit sphere 4D*/
    a = vector({-1.05,-1.05,-1.05,-1.05});
    b = vector({1.05,1.05,1.05,1.05});
    N = 5e6;
    res = plainMC(f_ucirc, a,b,N);
    q_analytic = 0.5*M_PI*M_PI;
    std::cout << "\n∫4D unit sphere = " << reportResult(res, q_analytic, N);

    /*Task A integral*/
    a = vector({0,0,0});
    b = vector({M_PI, M_PI, M_PI});
    N = 1e8;
    res = plainMC(f_coses, a,b,N);
    // q = std::get<0>(res) * std::pow(M_PI,-3);
    // err = std::get<1>(res) * std::pow(M_PI,-3);
    q_analytic = 1.3932039296856768591842462603255;
    std::cout << "\n1/pi^3∫_0^pi dx∫_0^pi dy∫_0^pi dz [1-cos(x)cos(y)cos(z)]^-1 = " << reportResult(res, q_analytic, N);


    return 0;
}


int graph_a() {
    std::tuple<double,double> res;
    double q,err;
    
    vector a({-1,-1}),
    b({1,1});
    for(int i = 10; i < 25 ; ++i) {
        double N = std::pow(2,i);
        res = plainMC(f_ucirc, a,b,N);
        q = std::get<0>(res);
        err = std::get<1>(res);
        std::cout << N << ", " << err << ", " << std::abs(q - M_PI) << "\n";
    }
    return 0;
}

int task_b() {
    std::cout << "Task b, Quasi-random Monte Carlo integration.\n";
    
    vector a,b;
    int N;
    double q_analytic;
    std::tuple<double,double> res;

    /* Unit circle */
    a = vector({-1,-1});
    b = vector({1,1});
    N = 1e5;
    res = quasiMC(f_ucirc, a,b,N);
    q_analytic = M_PI;
    std::cout << "∫unit circle = " << reportResult(res, q_analytic, N);
    std::cout << "Due to random variance arising from an error estimate of two random samplers, the error can be misjudged severely. Though this seems rare from the error plot.\n";
    std::cout << "\tError as a function of sample points is plotted in Plot.errquasi.svg.\n" << 
                "\tThe convergence of quasi-random sampling is quite a lot faster than plain Monte Carlo (plainMC), still roughly following the 1/sqrt(N) dependency.\n" <<
                "\tThe actual error is about an order of magnitude lower than for plainMC for pretty much all no. of samples, the fitting coefficient is ~17 times lower\n";
    return 0;
}

int graph_b() {
    std::tuple<double,double> res;
    double q,err;
    
    vector a({-1,-1}),
    b({1,1});
    for(int i = 10; i < 25 ; ++i) {
        double N = std::pow(2,i);
        res = quasiMC(f_ucirc, a,b,N);
        q = std::get<0>(res);
        err = std::get<1>(res);
        std::cout << N << ", " << err << ", " << std::abs(q - M_PI) << "\n";
    }
    return 0;
}

int task_c() {
    std::cout << "Task c, Stratified Monte Carlo integration.\n";
    std::cout << "This one didn't really work out. Likely a misunderstanding with splitting the volume.\n";
    std::cout << "It technically has a lower error than plainMC (for actually asymmetric integrals), about a factor 10\n" << 
                "Though it calculates the whole thing for every subdivision, leading to a very slow algorithm where one might as well crank up the no. of samples for plainMC and still get a better and faster result. \n" <<
                "I may have misunderstood the assignment, since it to me reads like 'dont use the acc,eps condition from the book' and instead let it run only with N and nmin, but this doesn't seem to make much sense.\n";

    vector a,b;
    int N;
    double q_analytic;
    std::tuple<double,double> res;
    std::cout << "\n2D gauss centered on (1, 0.5) with standard deviations (1, 0.5):";

    /* 2D Gauss plainMC */
    a = vector({-15.0, -15.0});
    b = vector({15.0, 15.0});
    N = 1e7;
    res = plainMC(f_gauss2d, a,b,N);
    q_analytic = M_PI;
    std::cout << "\nplainMC: ∫2D gauss = " << reportResult(res, q_analytic, N);
    
    /* 2D Gauss */
    a = vector({-15.0, -15.0});
    b = vector({15.0, 15.0});
    N = 1e7;
    res = stratMC(f_gauss2d, a,b,N, 4096);
    q_analytic = M_PI;
    std::cout << "\nStratified: ∫2D gauss = " << reportResult(res, q_analytic, N);
    return 0;
}

int main(int argc, char** argv) {
    std::string task = "all";

    for(int i = 0; i<argc; ++i){
        std::string arg = argv[i];
        if(arg == "-t" && i+1<argc) task = argv[i + 1];
    }


    if(task == "all") {
        task_a();
        std::cout << "\n\n";
        task_b();
        std::cout << "\n\n";
        task_c();
        return 0;
    }
    if(task == "a")
    {
        return task_a();
    }
    else if (task == "b")
    {
        return task_b();
    }
    else if (task == "c")
    {
        return task_c();
    }
    
    if(task == "errData") {
        return graph_a();
    }
    if(task == "errQuasiData") {
        return graph_b();
    }

    std::cout << "unknown task: " << task <<  "\n";
    return 1;
};
