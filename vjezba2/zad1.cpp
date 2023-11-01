#include<iostream>
using namespace std;

int* min_max(int niz[], int& a, int& b)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (niz[i] < a)
			a = niz[i];
		if (niz[i] > b)
			b = niz[i];
	}
	return &a, &b;
}

int main()
{
	int niz[] = { 4,6,1,8,0,2 };
	int min = niz[0];
	int max = niz[0];
	min_max(niz, min, max);
	cout << "Najmanji je " << min << endl;
	cout << "Najveci je " << max << endl;
	return 0;
}