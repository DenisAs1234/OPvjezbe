#include<iostream>
#include<string>
using namespace std;

template<typename TYPE>
TYPE min(TYPE a, TYPE b)
{
	if (a < b)
		return a;
	else
		return b;
}

int main()
{
	int a, b;
	cin >> a;
	cin >> b;
	int m=min(a, b);
	cout << m << endl;
	string s1, s2;
	cin >> s1;
	cin >> s2;
	string s = min(s1, s2);
	cout << s << endl;
	return 0;
}