#include <iostream>
using namespace std;

template
    <typename T> //Assume Vector only takes in integer or double for template typename T

class Vector
{
private:
    int sz;
    T * buf;

public:
    Vector(int n)
	 : sz(n), buf(new T[n]) {}

    Vector(initializer_list<T> L) {
	sz = L.size();
	buf = new T[sz];

	int count = 0;
	for (T item : L)
	    buf[count++] = item;
    }

    ~Vector() {
	delete[] buf;
    }

    Vector(const Vector & v)
	:sz(v.sz), buf(new T[v.sz]) {
	for (int i = 0; i < sz; ++i)
	    buf[i] = v.buf[i];
    }

    int size() {
	return sz;
    }

    T & operator [] (const int i) {
	if (i >= sz)
	    throw "Out of Bounds Error";

	return buf[i];
    }

    T operator * (const Vector & v) const {
	T sum = 0;
	for (int i = 0; i < sz; ++i) 
	    sum += buf[i] * v.buf[i];
	return sum;
    }

    Vector operator + (const Vector & v) const {
	if (v.sz >= sz) {
	    Vector<T> result(v);
	    for (int i = 0; i < sz; ++i)
		result.buf[i] += buf[i];
	    return result;
	}
	else {
	    Vector<T> result(*this);
	    for (int i = 0; i < v.sz; ++i)
		result.buf[i] += v.buf[i];
	    return result;
	}
    }

    const Vector & operator = (const Vector & v) {
	delete[] buf;
	sz = v.sz;
	buf = new T[sz];

	for (int i = 0; i < sz; ++i)
	    buf[i] = v.buf[i];

	return *this;
    }

    bool operator == (const Vector & v) {
	if (v.sz != sz)
	    return false;
	for (int i = 0; i < sz; ++i)
	    if (v.buf[i] != buf[i])
		return false;
	return true;
    }

    bool operator != (const Vector & v) {
	return !(*this == v);
    }

    friend Vector operator * (const int n, const Vector & v) {
	Vector<T> result(v);
	for (int i = 0; i < v.sz; ++i)
	    result.buf[i] *= n;
	return result;
    }

    friend Vector operator + (const int n, const Vector & v) {
	Vector<T> result(v);
	for (int i = 0; i < v.sz; ++i)
	    result.buf[i] += n;
	return result;
    }

    friend ostream & operator << (ostream & o, const Vector & v) {
	o << '(';
	for (int i = 0; i < v.sz-1; ++i)
	    o << v.buf[i] << ", ";
	o << v.buf[v.sz-1] << ')';
	return o;
    }
};
