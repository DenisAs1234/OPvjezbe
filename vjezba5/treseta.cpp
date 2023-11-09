#include<iostream>
#include<vector>
#include<string>
#include<time.h>
using namespace std;

class Karta {
public:
	int broj;
	string zog;
};

class Spil {
	vector<int> niz_broj { 1,2,3,4,5,6,7,11,12,13 };
	vector<string> niz_zog { "spadi","bastoni","kupe","dinari" };
public:
	Karta k;
	vector<Karta> spil;
	void generiranje_spila(vector<Karta> &spil)
	{
		int i, j, l = 0;
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 4; j++)
			{
				k.broj = niz_broj.at(i);
				k.zog = niz_zog.at(j);
				spil.resize(spil.size() + 1);
				spil.at(l++) = k;
			}
		}
	}
	vector<Karta> mijesanje_spila(vector<Karta> spil)
	{
		vector<Karta> promijesani_spil;
		int i;
		for (i = 0; i < 40; i++)
		{
			promijesani_spil.resize(i + 1);
			int r = rand() % (40 - i);
			promijesani_spil.at(i) = spil.at(r);
			spil.erase(spil.begin() + r);
		}
		return promijesani_spil;
	}
	vector<Karta> dijeljenje_karata(vector<Karta> &spil)
	{
		vector<Karta> kombinacija;
		int i;
		for (i = 0; i < 10; i++)
		{
			kombinacija.resize(i + 1);
			kombinacija.at(i) = spil.at(0);
			spil.erase(spil.begin());
		}
		return kombinacija;
	}
	void ispisivanje(vector<Karta> spil)
	{
		unsigned int i;
		for (i = 0; i < spil.size(); i++)
		{
			cout << "{" << spil.at(i).broj << "," << spil.at(i).zog << "} ";
		}
		cout << endl;
	}
};

class Igrac {
public:
	string ime;
	vector<Karta> ruka;
	int broj_bodova;
	int akuze(vector<Karta> ruka)
	{
		int bodovi = 0;
		int spadi[3] = { 0,0,0 };
		int bastoni[3] = { 0,0,0 };
		int kupe[3] = { 0,0,0 };
		int dinari[3] = { 0,0,0 };
		int ukupno[3] = { 0,0,0 };
		unsigned int i;
		for (i = 0; i < ruka.size(); i++)
		{
			if (ruka.at(i).broj == 1)
			{
				if (ruka.at(i).zog == "spadi")
				{
					spadi[2]++;
				}
				else if (ruka.at(i).zog == "bastoni")
				{
					bastoni[2]++;
				}
				else if (ruka.at(i).zog == "kupe")
				{
					kupe[2]++;
				}
				else
				{
					dinari[2]++;
				}
				ukupno[2]++;
			}
			else if (ruka.at(i).broj == 2)
			{
				if (ruka.at(i).zog == "spadi")
				{
					spadi[1]++;
				}
				else if (ruka.at(i).zog == "bastoni")
				{
					bastoni[1]++;
				}
				else if (ruka.at(i).zog == "kupe")
				{
					kupe[1]++;
				}
				else
				{
					dinari[1]++;
				}
				ukupno[1]++;
			}
			else if (ruka.at(i).broj == 3)
			{
				if (ruka.at(i).zog == "spadi")
				{
					spadi[0]++;
				}
				else if (ruka.at(i).zog == "bastoni")
				{
					bastoni[0]++;
				}
				else if (ruka.at(i).zog == "kupe")
				{
					kupe[0]++;
				}
				else if (ruka.at(i).zog == "dinari")
				{
					dinari[0]++;
				}
				ukupno[0]++;
			}
		}
		if (ukupno[2] >= 3)
			bodovi += ukupno[2];
		if (ukupno[1] >= 3)
			bodovi += ukupno[1];
		if (ukupno[0] >= 3)
			bodovi += ukupno[0];
		if (spadi[0] && spadi[1] && spadi[2])
		{
			bodovi += 3;
		}
		if (bastoni[0] && bastoni[1] && bastoni[2])
		{
			bodovi += 3;
		}
		if (kupe[0] && kupe[1] && kupe[2])
		{
			bodovi += 3;
		}
		if (dinari[0] && dinari[1] && dinari[2])
		{
			bodovi += 3;
		}
		return bodovi;
	}
};

int main()
{
	srand(time(NULL));
	Spil s, m;
	s.generiranje_spila(s.spil);
	m.spil = s.mijesanje_spila(s.spil);
	cout << "Promijesani spil: " << endl;
	s.ispisivanje(m.spil);
	int n;
	cout << "Broj igraca: ";
	cin >> n;
	Igrac i1, i2, i3, i4;
	cout << "1.igrac: ";
	cin >> i1.ime;
	cout << "2.igrac: ";
	cin >> i2.ime;
	if (n == 4)
	{
		cout << "3.igrac: ";
		cin >> i3.ime;
		cout << "4.igrac: ";
		cin >> i4.ime;
	}
	i1.ruka = m.dijeljenje_karata(m.spil);
	cout << "" << i1.ime << ":" << endl;
	s.ispisivanje(i1.ruka);
	i2.ruka = m.dijeljenje_karata(m.spil);
	cout << "" << i2.ime << ":" << endl;
	s.ispisivanje(i2.ruka);
	if (n == 4)
	{
		i3.ruka = m.dijeljenje_karata(m.spil);
		cout << "" << i3.ime << ":" << endl;
		s.ispisivanje(i3.ruka);
		i4.ruka = m.dijeljenje_karata(m.spil);
		cout << "" << i4.ime << ":" << endl;
		s.ispisivanje(i4.ruka);
	}
	cout << i1.ime << " bodovi: " << i1.akuze(i1.ruka) << endl;
	cout << i2.ime << " bodovi: " << i2.akuze(i2.ruka) << endl;
	if (n == 4)
	{
		cout << i3.ime << " bodovi: " << i3.akuze(i3.ruka) << endl;
		cout << i4.ime << " bodovi: " << i4.akuze(i4.ruka) << endl;
	}
	return 0;
}
