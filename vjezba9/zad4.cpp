#include<iostream>
#include "zad4.hpp"
using namespace std;

int main()
{
	point<int> p1(2, 3), p2(3, 4);
	cout << " udaljenost tocaka " << p1 << " i " << p2 << " je " << p1 - p2 << endl;
	return 0;
}