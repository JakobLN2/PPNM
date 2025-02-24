#ifndef HAVE_VECTOR_H
#define HAVE_VECTOR_H

// #ifdef LONG_DOUBLE
//     #define NUMBER long double
// #else
//     #define NUMBER double
// #endif

template<typename T>
class vector {
    // private:    
    public:
        T data[];
        int size = data.Length();

    vector(int n) {data = new T[n];} // parametrized constructor
    vector() = default; // default constructor
    vector(const vector&)=default; // copy constructor
    vector(vector&&)=default; // move constructor
    ~vector()=default; // destructor
    vector& operator=(const vector&)=default; // copy assignment
    vector& operator=(vector&&)=default; // move assignment

    // int size() return size;
    // T& operator[](int i) return data[i];
    // const T& operator[](int i) const {return data[i];}


    // friend vector<T> operator+(const vector<T>&, const vector<T>&);
    // vector operator-(const vector&);
    // vector operator-(const vector&, const vector&);
    // vector operator*(const vector&, double);
    // vector operator*(double, const vector&);
    // vector operator/(const vector&, double);
    // bool approx(const vector&, const vector&, double acc=1e-6,double eps=1e-6);
    // double dot(const vector&, const vector&);
};
#endif