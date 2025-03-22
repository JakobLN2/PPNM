#include"interp.h"

int binsearch(vector x, double z) {

    // int mid = x.size/2; //integer division
    // while(true) {
    //     if(z < x[mid]) {mid = mid/2;}
    //     else {mid = 3*mid/2;}


    // }
    if( z<x[0] || z>x[x.size-1] ) throw std::invalid_argument("binsearch: bad z");
	int i=0, j=x.size-1;
	while(j-i > 1){
		int mid = (i+j)/2;
		if(z > x[mid]) i = mid; else j = mid;
		}
	return i;
}

double linterp(vector x, vector y, double z) {
    int i = binsearch(x,z);
    return y[i] + (y[i+1] - y[i])/(x[i+1] - x[i]) * (z - x[i]);
}

double linterpInteg(vector x, vector y, double z) {
    double sum = 0;
    int imax = binsearch(x, z);
    std::cout << imax << "   "; 
    for(int i = 0; i < imax; ++i) {
        sum += 0.5 * (y[i + 1] + y[i]) * (x[i + 1] - x[i]);
    }
    sum += 0.5 * (linterp(x, y, z) + y[imax]) * (z - x[imax]);
    return sum;
}