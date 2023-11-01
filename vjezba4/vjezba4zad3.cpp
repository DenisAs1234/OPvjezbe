#include<iostream>
#include<string>
#include<vector>
using namespace std;

void sort_reverse(vector<string> &v, int n)
{
	int i, j, k;
	for (i = 0; i < n; i++)
	{
		cout << "" << i << ". element: ";
		cin >> v.at(i);
		string kopija = v.at(i);
		k = 0;
		for (j = v.at(i).length() - 1; j >= 0; j--)
		{
			v.at(i).at(j) = kopija.at(k++);
		}
	}
	cout << "Preokrenuti stringovi: " << endl;
	for (i = 0; i < 4; i++)
	{
		cout << v.at(i) << endl;
	}
	string pom;
	for (i = 0; i < n - 1; i++)
	{
		for (j = i; j < n; j++)
		{
			if (v.at(i) > v.at(j))
			{
				pom = v.at(i);
				v.at(i) = v.at(j);
				v.at(j) = pom;
			}
		}
	}
}

int main()
{
	vector<string> v(4);
	sort_reverse(v, 4);
	int i;
	cout << "Sortirani vektor: " << endl;
	for (i = 0; i < 4; i++)
	{
		cout << v.at(i) << endl;
	}
	return 0;
}