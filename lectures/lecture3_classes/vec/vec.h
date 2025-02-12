// #ifndef HAVE_VEC_H
// #define HAVE_VEC_H
// #include<iostream>
// #include<string>
// struct vec{
// 	double x,y,z;
// 	vec(double x,double y,double z): x(x),y(y),z(z){} //We create a constructor which assigns xyz to xyz
// 	vec():vec(0,0,0){} //Since we have defined one constructor, we have to define the others as well:
// 	vec(const vec&)=default; //Move constructor?
// 	vec(vec&&)=default; //Delete constructor?
// 	~vec()=default;
// 	vec& operator=(const vec&)=default;
// 	vec& operator=(vec&&)=default;
// 	vec& operator+=(const vec&);
// 	vec& operator-=(const vec&);
// 	vec& operator*=(double);
// 	vec& operator/=(double);
// 	void set(double a,double b,double c){x=a;y=b;z=c;}
// 	void print(std::string s="") const;
// 	friend std::ostream& operator<<(std::ostream& os, const vec& v);
//     //operator << is used for std::out, if we want to print the object we have to overload (override) this operator
//     //friend means that we grant it access to even private methods and members
// };
// vec operator-(const vec&); //const means that the compiler can find very deep bugs??
// vec operator-(const vec&, const vec&);
// vec operator+(const vec&, const vec&);
// vec operator*(const vec&, double);
// vec operator*(double, const vec&);
// vec operator/(const vec&, double);
// bool approx(const vec&, const vec&, double acc=1e-6,double eps=1e-6);
// #endif

#ifndef HAVE_VEC_H
#define HAVE_VEC_H
struct vec {
	double x,y,z;
};
#endif