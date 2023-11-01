#include<iostream>
using namespace std;

int& veciza1(int* niz, int i)
{
	return niz[i];
}

int main()
{
	int niz[] = { 6,4,5,8,10,1,25 };
	int i;
	cout << "Koji element?" << endl;
	cin >> i;
	veciza1(niz, i) += 1;
	for (i = 0; i < 7; i++)
	{
		cout << niz[i] << " ";
	}
	return 0;
}