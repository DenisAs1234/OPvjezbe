#include <iostream>
#include <vector>
#include "vj3header.hpp"
#include "vj3implementacija.hpp"

int main()
{
	vector<int> v(5);
	cout << "Unos vektora:" << endl;
	unos1(v, 5);
	int i, j, p, suma = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (v.at(j) < v.at(i))
			{
				p = v.at(j);
				v.at(j) = v.at(i);
				v.at(i) = p;
			}
		}
	}
	for (i = 0; i < 5; i++)
	{
		suma += v.at(i);
	}
	cout << "Sortirani vektor:" << endl;
	ispis(v, 5);
	v.insert(v.begin(), 0);
	v.emplace_back(suma);
	cout << endl;
	cout << "Novi vektor:" << endl;
	ispis(v, 7);
	return 0;
}