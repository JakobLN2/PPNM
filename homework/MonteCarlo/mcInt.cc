#include"mcInt.h"

std::tuple<double,double> plainMC(const std::function<double(vector)>& F, vector a, vector b, int N) {
    double V = 1;
    for(int i = 0; i < a.size ; ++i) V *= b[i] - a[i];
    
    std::default_random_engine re;
    std::vector<std::uniform_real_distribution<double>> unifs(a.size);
    for(int i = 0; i < a.size ; ++i) unifs[i] = std::uniform_real_distribution<double>(a[i],b[i]); 
    
    vector x(a.size);
    double fx,sum1 = 0,sum2 = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < a.size ; ++j) x[j] = unifs[j](re);
        fx = F(x);
        sum1 += fx;
        sum2 += fx*fx;
    }
    double mean = sum1/N;
    double variance = sum2/N-mean*mean;
    return std::make_tuple(V*mean, V * std::sqrt(variance/N));
}

double halton(int n, int b) {
    double f = 1,
           r = 0;
    while(n > 0) {
        f /= b;
        r += (n % b) * f;
        n = std::floor(n/b);
    }
    return r;
}

vector bases({2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61});
std::tuple<double,double> quasiMC(const std::function<double(vector)>& F, vector a, vector b, int N) {
    double V = 1;
    for(int i = 0; i < a.size ; ++i) V *= b[i] - a[i];
     
    vector x(a.size);
    double sum1 = 0,sum2 = 0;
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < a.size ; ++j) x[j] = a[j] + halton(i, bases[j]) * (b[j] - a[j]);
        sum1 += F(x);
        
        for(int j = 0; j < a.size ; ++j) x[j] = a[j] + halton(i + N, bases[j]) * (b[j] - a[j]);
        sum2 += F(x);
    }
    return std::make_tuple(V/N * sum1, V/N * std::abs(sum1 - sum2));
}

std::tuple<double,double> stratMC(const std::function<double(vector)>& F, vector a, vector b, int N, int nmin) {
    if(N <= nmin) return plainMC(F,a,b,N); //Maximally subdivided, use plain Monte Carlo 

    int dim = a.size;
    
    double V = 1;
    for(int i = 0; i < dim ; ++i) V *= b[i] - a[i];

    std::default_random_engine re;
    std::vector<std::uniform_real_distribution<double>> unifs(dim);
    for(int i = 0; i < dim ; ++i) unifs[i] = std::uniform_real_distribution<double>(a[i],b[i]); 
    
    std::vector<int> n_left(dim), n_right(dim);
    vector x(dim), mean_left(dim), mean_right(dim);
    double sum, fx;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < dim ; ++j) x[j] = unifs[j](re);
        fx = F(x);
        sum += fx;
        for(int j  = 0; j < dim; ++j) {
            if(x[j] > (a[j] + b[j]) / 2) {
                n_right[j]++;
                mean_right[j] += fx;
            } else {
                n_left[j]++;
                mean_left[j] += fx;
            }
        }
    }
    sum /= N;
    for(int j = 0; j < dim; ++j) {
        mean_right[j] /= n_right[j];
        mean_left[j] /= n_left[j];
    }
    int jmax = 0; //Dimension with largest variance between left and right side integral
    double maxVar = 0;
    for(int j = 0; j < dim ; ++j) {
        double var = std::abs(mean_right[j] - mean_left[j]);
        if(var > maxVar) {maxVar = var; jmax = j;}
    }

    vector b_left = b.copy(), a_right = a.copy();
    b_left[jmax] = (a[jmax] + b[jmax])/2;
    a_right[jmax] = (a[jmax] + b[jmax])/2;


    int N_left = n_left[jmax]; //This way of splitting up points doesn't really make sense (is approximatively equal, always).
    int N_right = n_right[jmax]; //It should be weighed by internal variance in each of the two subdivisions, which i do not have.
    std::tuple<double, double> res_left, res_right;

    // std::cerr << "Splitting integral in dimension " << jmax << ", n_left = " << N_left << ", nright = " << N_right << "\n";
    // std::cerr << "Splitting integral in dimension " << jmax << ", maxVar = " << maxVar << ", "; (mean_left - mean_right).print("variances = ");
    // std::cerr << "Splitting integral in dimension " << jmax << ", "; (mean_left - mean_right).print("variances = ");
    res_left = stratMC(F, a, b_left, N_left, nmin);
    res_right = stratMC(F, a_right, b, N_right, nmin);

    double q = std::get<0>(res_left) + std::get<0>(res_right); //The integrals will always be the same size (V/2) so we can just add them together?
    double err = std::sqrt(std::pow(std::get<1>(res_left),2) + std::pow(std::get<1>(res_right),2)); //They are probably independent, right, should be weighed against no. of points?
    return std::make_tuple(q,err);

}


// #define FOR( k ) for ( int k=0;k<dim ; k++)
// #define RND (double) rand ( ) /RAND_MAX

// int n_reuse , double mean_reuse )
// {

// int n_le ft [ dim ] , n_right [ dim ] ;
// double x [ dim ] , mean_left [ dim ] , mean_right [ dim ] , mean=0;
// FOR( k ){ mean_left [ k ]=0; mean_right [ k ]=0; n_left [ k ]=0; n_right [ k ]=0; }
// for ( int i =0; i<N; i ++){
// FOR( k ) x [ k]=a [ k]+RND∗(b [ k]−a [ k ] ) ;
// double f x=f (dim , x ) ;
// mean+=f x ;
// FOR( k ){
// i f ( x [ k] >(a [ k]+b [ k ] ) / 2 ) { n_right [ k]++; mean_right [ k]+=f x ; }
// else { n _lef t [ k]++; mean_left [ k]+=f x ; }
// }
// }
// mean/=N;
// FOR( k ){ mean_left [ k]/= n _lef t [ k ] ; mean_right [ k]/= n_right [ k ] ; }
// int kdiv =0; double maxvar=0;
// FOR( k ){
// double var=f a b s ( mean_right [ k]−mean_left [ k ] ) ;
// i f ( var>maxvar ){ maxvar=var ; kdiv=k ; }
// }
// double i n t e g =(mean∗N+mean_reuse∗n_reuse ) / (N+n_reuse )∗V;
// double e r r o r=f a b s ( mean_reuse−mean)∗V;
// double t o l e r=acc+f a b s ( i n t e g )∗ eps ;
// i f ( e r r o r <t o l e r ) return i n t e g ;
// double a2 [ dim ] , b2 [ dim ] ; FOR( k ) a2 [ k]=a [ k ] ; FOR( k ) b2 [ k]=b [ k ] ;
// a2 [ kdiv ]=(a [ kdiv ]+b [ kdiv ] ) / 2 ; b2 [ kdiv ]=(a [ kdiv ]+b [ kdiv ] ) / 2 ;
// double i n t e g _ l e f t=
// s t r a t a (dim , f , a , b2 , acc / s q r t ( 2 ) , eps , n_le ft [ kdiv ] , mean_left [ kdiv ] ) ;
// double i n t e g _ r i g h t=
// s t r a t a (dim , f , a2 , b , acc / s q r t ( 2 ) , eps , n_right [ kdiv ] , mean_right [ kdiv ] ) ;
// return i n t e g _ l e f t+i n t e g _ r i g h t ;
// }