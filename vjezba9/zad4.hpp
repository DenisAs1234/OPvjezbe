#ifndef ZAD4
#define ZAD4
#include<iostream>
#include<cmath>
using namespace std;

template<typename T>
class point {
	T x, y;
public:
	point(T X, T Y) { x = X; y = Y; }
	template<typename T>
	friend double operator-(point<T>& p1, point<T>& p2);
	template<typename T>
	friend ostream& operator<<(ostream& os, point<T>& p);
};

template<typename T>
double operator-(point<T> &p1, point<T> &p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

template<typename T>
ostream& operator<<(ostream& os, point<T> &p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}

#endif
