#include <iostream>
#include <vector>
#include "vj3header.hpp"
#include "vj3implementacija.hpp"

int main()
{
	int n = 4, a, b;
	vector<int> vec(n);
	unos1(vec, n);
	ispis(vec, n);
	cout << endl;
	cout << "min=";
	cin >> a;
	cout << "max=";
	cin >> b;
	vector<int> vec2(1);
	unos2(vec2, a, b);
	ispis(vec2, vec2.size() - 2);
	return 0;
}