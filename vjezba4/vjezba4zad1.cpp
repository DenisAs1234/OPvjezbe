#include<iostream>
#include<string>
using namespace std;

int broj_pojavljivanja(string s1, string s2)
{
	int br_poj = 0;
	int duljina_podstringa = s2.length();
	unsigned int poz = 0;
	while (s1.find(s2, poz) != string::npos)
	{
		br_poj++;
		poz = s1.find(s2, poz) + duljina_podstringa;
	}
	return br_poj;
}

int main()
{
	string s1;
	string s2;
	cin >> s1;
	cin >> s2;
	cout << "Broj pojavljivanja: " << broj_pojavljivanja(s1, s2) << endl;
	return 0;
}