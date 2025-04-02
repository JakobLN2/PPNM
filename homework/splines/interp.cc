#include"interp.h"

int binsearch(vector x, double z) { //TODO: Rewrite this in my own code

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
    for(int i = 0; i < imax; ++i) {
        
        // double dx = x[i + 1] - x[i];
        // double a = (y[i + 1] - y[i])/dx;
        // double b = y[i] - a * x[i];
        // sum += b * dx + 0.5 * a * (x[i + 1] * x[i + 1] - x[i] * x[i]);
        sum += 0.5 * (y[i + 1] + y[i]) * (x[i + 1] - x[i]); //Trapezoid rule integration
    }
    // double dx = z - x[imax];
    // double a = (linterp(x, y, z) - y[imax])/dx;
    // double b = y[imax] - a * x[imax];

    // sum += b * dx + 0.5 * a * (z*z - x[imax] * x[imax]); //0.5 * (y[i + 1] + y[i]) * (x[i + 1] - x[i]);
    sum += 0.5 * (linterp(x, y, z) + y[imax]) * (z - x[imax]);
    return sum;
}

void qspline::buildSpline() {
    vector dx(c.size), p(c.size);
    for(int i = 0; i < x.size - 1 ; ++i) {
        dx[i] = x[i + 1] - x[i];
        p[i] = (y[i + 1] - y[i])/dx[i];
    }

    for(int i = 0; i < x.size - 2 ; ++i) c[i + 1] = 1/dx[i + 1] * (p[i + 1] - p[i] - c[i]*dx[i]);
    
    for(int i = x.size - 3; i >= 0; --i) c[i] = 0.5 * (c[i] + 1/dx[i]*(p[i + 1] - p[i] - c[i + 1]*dx[i + 1]));

    for(int i = 0; i < c.size; ++i) b[i] = p[i] - c[i]*dx[i];
}

double qspline::eval(double z) const {
    int i = binsearch(x,z);
    return y[i] + b[i] * (z - x[i]) + c[i] * (z - x[i]) * (z - x[i]);
}

double qspline::integ(double z) {
    int imax = binsearch(x,z);
    double sum = 0;
    for(int i = 0; i < imax ; ++i) {
        double dx = x[i + 1] - x[i];
        sum += y[i] * dx + (0.5 * b[i] + c[i]/3 * dx) * dx * dx;
    }
    double dx = z - x[imax];
    sum += y[imax] * dx + (0.5 * b[imax] + c[imax]/3 * dx) * dx * dx;
    return sum;
}

double qspline::deriv(double z) {
    int idx = binsearch(x,z);
    return b[idx] + 2*c[idx] * (z - x[idx]);
}


void cubspline::buildSpline() {
    vector dx(c.size), p(c.size),
            D(c.size), B(c.size),
            Q(c.size - 1);
    for(int i = 0; i < x.size -1 ; ++i) {
        dx[i] = x[i+1] - x[i];
        p[i] = (y[i + 1] - y[i])/dx[i];
    }

    D[0] = 2;
    B[0] = 3*p[0];
    Q[0] = 1;
    for(int i = 1; i < x.size - 2; ++i) {
        Q[i] = dx[i - 1]/dx[i];
        D[i] = 2*Q[i] + 2;
        B[i] = 3 * (p[i - 1] + p[i] * Q[i]);
    }
    D[x.size - 2] = 2;
    B[x.size - 2] = 3 * p[x.size - 3];
    D.print("D = ");
    B.print("B = ");

    for(int i = 1; i < x.size - 1; ++i) {
        D[i] -= Q[i - 1]/D[i - 1];
        B[i] -= B[i - 1]/D[i - 1];
    }
    Q.print("Q = ");
    D.print("Dtilde = ");
    B.print("Btilde = ");

    b[x.size - 2] = B[x.size - 2]/D[x.size - 2];
    for(int i = x.size - 3; i >= 0; --i) b[i] = (B[i] - Q[i]*b[i + 1])/D[i];
    b.print("b = ");
    for(int i = 0; i < x.size - 1; ++i) {
        c[i] = (-2*b[i] - b[i + 1] + 3*p[i])/dx[i];
        d[i] = (b[i] + b[i + 1] - 2*p[i])/dx[i]/dx[i];
    }
    // c[x.size - 2] = -3 * d[x.size - 2] * dx[x.size - 2];
}

double cubspline::eval(double z) const {
    int i = binsearch(x,z);
    double dx = z - x[i];
    return y[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}

double cubspline::integ(double z) const {
    int imax = binsearch(x,z);
    double sum = 0;
    for(int i = 0; i < imax; ++i) {
        double dx = x[i + 1] - x[i];
        sum += dx * (y[i] + dx * (0.5 * b[i] + dx * (1/3 * c[i] + dx * 0.25 *d[i])));
    }
    double dx = z - x[imax];
    sum += dx * (y[imax] + dx * (0.5 * b[imax] + dx * (1/3 * c[imax] + dx * 0.25 * d[imax])));
    return sum;
}

double cubspline::deriv(double z) const {
    int i = binsearch(x,z);
    double dx = z - x[i];
    return b[i] + 2*c[i]*dx + 3*d[i]*dx*dx;
}