#include <iostream>
using namespace std;

int niz[] = { 6,4,5,8,10,1,25 };
int& veciza1(int i)
{
	return niz[i];
}

int main()
{
	int i;
	cout << "Koji element?" << endl;
	cin >> i;
	veciza1(i)+=1;
	for (i = 0; i < 7; i++)
	{
		cout << niz[i] << " ";
	}

}