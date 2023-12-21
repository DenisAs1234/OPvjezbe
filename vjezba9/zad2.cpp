#include<iostream>
#include<vector>
#include "zad2.hpp"
using namespace std;

template<typename T>
vector<T> skup<T>::get()
{
	return vec;
}

template<typename T>
void skup<T>::dodavanje(vector<T> &v, int n)
{
	v.insert(v.begin() + n, 1, 10);
}

template<typename T>
void skup<T>::izbacivanje(vector<T> &v, int n)
{
	v.erase(v.begin() + n);
}

template<typename T>
bool skup<T>::provjera(vector<T> v, T n)
{
	int i;
	for (i = 0; i < v.size(); i++)
	{
		if (v.at(i) == n)
			return true;
	}
	return false;
}

template<typename T>
void skup<T>::ispis(vector<T> v)
{
	int i;
	for (i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> v{ 1,7,4,3,8,2 };
	skup<int> niz(v);
	niz.dodavanje(v, 3);
	niz.ispis(v);
	niz.izbacivanje(v, 2);
	niz.ispis(v);
	bool x = niz.provjera(v, 5);
	bool y = niz.provjera(v, 4);
	cout << x << endl;
	cout << y << endl;
	return 0;
}