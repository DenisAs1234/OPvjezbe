#include <iostream>
#include <vector>
#include "vj3header.hpp"
#include "vj3implementacija.hpp"

void uklanjanje(vector<int> &v, int ukl)
{
	int i;
	for (i = 0; i < v.size() - 1; i++)
	{
		if (i >= ukl)
		{
			v.at(i) = v.at(i + 1);
		}
	}
	v.resize(v.size() - 1);
}

int main()
{
	int n = 5, ukl;
	vector<int> vec(n);
	cout << "Unos vektora:" << endl;
	unos1(vec, 5);
	cout << "Indeks elementa kojeg treba ukloniti: ";
	cin >> ukl;
	uklanjanje(vec, ukl);
	cout << "Novi vektor:" << endl;
	ispis(vec, 4);
	return 0;
}