#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<time.h>
using namespace std;

void pig_latin(string& str, string voc)
{
	unsigned int poz = 0;
	while (poz < str.length())
	{
		unsigned int razmak = str.find(' ', poz);
		if (razmak == string::npos)
		{
			razmak = str.length() - 1;
		}
		if (voc.find(str.at(poz)) == string::npos)
		{
			do
			{
				str.insert(str.begin()+razmak, str.at(poz));
				str.erase(str.begin()+poz);
			} while (voc.find(str.at(poz)) == string::npos);
			str.insert(razmak, "ay");
			razmak += 2;
		}
		else
		{
			str.insert(razmak, "hay");
			razmak += 3;
		}
		poz = razmak + 1;
	}
}

int main()
{
	vector<string> v{ "What time is it?","How are you?" };
	string samoglasnici("aeiouAEIOU");
	srand(time(0));
	int indeks = rand() % 2;
	cout << "Izabrana recenica: " << endl;
	cout << v.at(indeks) << endl;
	string str = v.at(indeks);
	pig_latin(str, samoglasnici);
	cout << "Prevedena recenica: " << endl;
	cout << str << endl;
	return 0;
}