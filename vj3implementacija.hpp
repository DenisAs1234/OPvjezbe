#include "vj3header.hpp"
#include <iostream>
#include <vector>

void unos1(vector<int> &v, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		cin >> v.at(i);
	}
}

void unos2(vector<int> &v, int a, int b)
{
	int i = 0;
	do
	{
		cin >> v.at(i);
		v.resize(i+2);
		i++;
	} while ((v.at(i-1) >= a) && (v.at(i-1) <= b));
}

void ispis(vector<int> &v, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		cout << ""<<v.at(i)<<" ";
	}
}