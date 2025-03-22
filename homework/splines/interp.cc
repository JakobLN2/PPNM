#include"interp.h"

int binsearch(vector x, double z) {

    int mid = x.size/2; //integer division
    while(true) {
        if(z < x[mid]) {mid = mid/2;}
        else {mid = 3*mid/2;}

    }
    return 1;
}

double linterp(vector x, vector y, double z) {
    int i = binsearch(x,z);
    y += i;
    return 1.0;
}