#include "vj3header.hpp"
#include "vj3implementacija.hpp"
#include <iostream>
#include <vector>

int main()
{
	vector<int> v1(6);
	vector<int> v2(6);
	cout << "Unos prvog vektora:" << endl;
	unos1(v1, 6);
	cout << "Unos drugog vektora:" << endl;
	unos1(v2, 6);
	vector<int> novi(1);
	int i, j = 0, k = 0, p;
	for (i = 0; i < 6; i++)
	{
		p = 1;
		for (j = 0; j < 6; j++)
		{
			if (v1.at(i) == v2.at(j))
				p = 0;
		}
		if (p)
		{
			novi.at(k++) = v1.at(i);
			novi.resize(k + 1);
		}
	}
	ispis(novi, novi.size() - 1);
	return 0;
}