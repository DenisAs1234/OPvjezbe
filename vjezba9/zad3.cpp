#include<iostream>
#include<vector>
using namespace std;

template<typename T>
void ispis(vector<T> v)
{
	int i;
	for (i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;
}

template<typename T>
void sortiranje(vector<T> &v)
{
	T temp;
	int i, j;
	for (i = 0; i < v.size() - 1; i++)
	{
		for (j = i + 1; j < v.size(); j++)
		{
			if (v.at(j) < v.at(i))
			{
				temp = v.at(i);
				v.at(i) = v.at(j);
				v.at(j) = temp;
			}
		}
	}
}

template<>
void sortiranje(vector<char> &v)
{
	char temp;
	int i, j, dif1, dif2;
	for (i = 0; i < v.size() - 1; i++)
	{
		for (j = i + 1; j < v.size(); j++)
		{
			if (v.at(i) <= 'Z')
				dif1 = 'Z' - v.at(i);
			else
				dif1 = 'z' - v.at(i);
			if (v.at(j) <= 'Z')
				dif2 = 'Z' - v.at(j);
			else
				dif2 = 'z' - v.at(j);
			if (dif2 > dif1)
			{
				temp = v.at(i);
				v.at(i) = v.at(j);
				v.at(j) = temp;
			}
		}
	}
}

int main()
{
	vector<int> v1{ 3,7,1,5,2,6 };
	vector<char> v2{ 'K','a','g','P','E','d' };
	sortiranje(v1);
	sortiranje(v2);
	ispis(v1);
	ispis(v2);
	return 0;
}