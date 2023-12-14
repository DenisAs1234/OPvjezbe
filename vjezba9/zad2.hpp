#ifndef ZAD2
#define ZAD2
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class skup {
	vector<T> vec;
public:
	skup(vector<T> v) { vec = v; }
	vector<T> get();
	void dodavanje(vector<T> &v, int n);
	void izbacivanje(vector<T> &v, int n);
	int provjera(T n);
	void ispis(vector<T> v);
};

#endif