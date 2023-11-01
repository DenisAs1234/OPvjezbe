#include<iostream>
#include<string>
using namespace std;

void ispravak_recenice(string &rec)
{
	unsigned int poz = 0;
	while (poz < rec.length())
	{
		if (rec.at(poz) == ',')
		{
			if (rec.at(poz - 1) == ' ')
			{
				rec.erase(poz - 1, 1);
				poz--;
			}
			if (rec.at(poz + 1) != ' ')
				rec.insert(poz + 1, " ");
			poz += 2;
		}
		poz++;
	}
}

int main()
{
	string rec("Danas sam kupio banane,mlijeko , kruh i cokoladu.");
	ispravak_recenice(rec);
	cout << rec;
	return 0;
}