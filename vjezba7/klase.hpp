#ifndef KLASE
#define KLASE
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
using namespace std;

class VirtualPet {
	string ime;
	string vrsta;
	int glad;
	int sreca;
	int budnost;
	int broj_porcija;
public:
	void setImeVrsta(string i, string v)
	{
		ime = i;
		vrsta = v;
	}
	void setGladSreca(int g, int s, int b, int p)
	{
		glad = g;
		sreca = s;
		budnost = b;
		broj_porcija = p;
	}
	string getIme()
	{
		return ime;
	}
	string getVrsta()
	{
		return vrsta;
	}
	int getGlad()
	{
		return glad;
	}
	int getSreca()
	{
		return sreca;
	}
	int getBudnost()
	{
		return budnost;
	}
	int getPorcije()
	{
		return broj_porcija;
	}
	void hranjenje(int& glad, int& sreca)
	{
		glad -= 40;
		sreca += 15;
		broj_porcija++;
		setGladSreca(glad, sreca, 1, broj_porcija);
	}
	void igranje(int& glad, int& sreca)
	{
		glad += 25;
		sreca += 20;
		setGladSreca(glad, sreca, 1, broj_porcija);
	}
	void spavanje(int& glad, int& sreca)
	{
		glad = 60;
		sreca += 20;
		setGladSreca(glad, sreca, 0, broj_porcija);
	}
	void ispis_bodova(int glad, int sreca)
	{
		cout << "Glad: " << glad << endl;
		cout << "Sreca: " << sreca << endl;
	}
	VirtualPet& operator= (VirtualPet& other)
	{
		ime = other.ime;
		vrsta = other.vrsta;
		glad = other.glad;
		sreca = other.sreca;
		budnost = other.budnost;
		broj_porcija = other.broj_porcija;
		return *this;
	}
	friend int operator==(VirtualPet& p1, VirtualPet& p2);
	friend int operator!=(VirtualPet& p1, VirtualPet& p2);
	friend int operator++(VirtualPet& p);
	friend int operator++(VirtualPet& p, int);
	friend int operator<(VirtualPet& p1, VirtualPet& p2);
	friend int operator>(VirtualPet& p1, VirtualPet& p2);
	friend int operator<=(VirtualPet& p1, VirtualPet& p2);
	friend int operator>=(VirtualPet& p1, VirtualPet& p2);
	friend ostream& operator<<(ostream& out, VirtualPet& p);
};

int operator==(VirtualPet& p1, VirtualPet& p2)
{
	if ((p1.ime != p2.ime) || (p1.vrsta != p2.vrsta) || (p1.glad != p2.glad) || (p1.sreca != p2.sreca) || (p1.budnost != p2.budnost))
		return 0;
	return 1;
}

int operator!=(VirtualPet& p1, VirtualPet& p2)
{
	if(p1==p2)
		return 0;
	return 1;
}

int operator++(VirtualPet& p)
{
	return ++p.broj_porcija;
}

int operator++(VirtualPet& p, int)
{
	return p.broj_porcija++;
}

int operator<(VirtualPet& p1, VirtualPet& p2)
{
	if (p1.sreca < p2.sreca)
		return 1;
	return 0;
}

int operator>(VirtualPet& p1, VirtualPet& p2)
{
	if (p1.sreca > p2.sreca)
		return 1;
	return 0;
}

int operator<=(VirtualPet& p1, VirtualPet& p2)
{
	if ((p1 < p2) || (p1 == p2))
		return 1;
	return 0;
}

int operator>=(VirtualPet& p1, VirtualPet& p2)
{
	if ((p1 > p2) || (p1 == p2))
		return 1;
	return 0;
}

ostream& operator<<(ostream& out, VirtualPet& p)
{
	out << "Ime: " << p.ime << endl;
	out << "Vrsta: " << p.vrsta << endl;
	out << "Glad: " << p.glad << endl;
	out << "Sreca: " << p.sreca << endl;
	out << "Budnost: " << p.budnost << endl;
	out << "Broj porcija: " << p.broj_porcija << endl;
	return out;
}

class Food {
	static int counter;
public:
	Food(int c) { counter = c; }
	static void mijenjanje_cnt()
	{
		counter--;
	}
	static void ispis_cnt()
	{
		cout << counter << endl;
	}
	friend static int get_counter(Food);
};

static int get_counter(Food f)
{
	return f.counter;
}

class Owner {
	string ime_vlasnika;
	vector<VirtualPet> ljubimci;
	int broj_akcija;
	vector<string> niz_akcija;
	vector<int> pomocni_niz;
public:
	void set(string i, int br)
	{
		ime_vlasnika = i;
		broj_akcija = br;
	}
	string getImeVl()
	{
		return ime_vlasnika;
	}
	vector<VirtualPet> getLjubimci()
	{
		return ljubimci;
	}
	int getBrAkcija()
	{
		return broj_akcija;
	}
	vector<string> getNizAkcija()
	{
		return niz_akcija;
	}
	vector<int> getPomNiz()
	{
		return pomocni_niz;
	}
	void unos_ljubimaca(vector<VirtualPet> &niz)
	{
		int i;
		for (i = 0; i < niz.size(); i++)
		{
			string ime, vrsta;
			int glad, sreca, budnost;
			cout << "Ljubimac " << i + 1 << endl;
			cout << "Ime: ";
			cin >> ime;
			cout << "Vrsta: ";
			cin >> vrsta;
			niz.at(i).setImeVrsta(ime, vrsta);
			niz.at(i).setGladSreca(50, 0, 1, 0);
		}
	}
	void niz_indeksa(vector<int> &pom)
	{
		int i;
		for (i = 0; i < 2 * broj_akcija; i++)
		{
			pom.at(i) = i;
		}
	}
	void redoslijed_akcija(vector<int> pom, vector<string> &niz)
	{
		unsigned int i;
		int r;
		for (i = 0; i < broj_akcija; i++)
		{
			r = rand() % (pom.size());
			niz.at(pom.at(r)) = "hranjenje";
			pom.erase(pom.begin() + r);
		}
		for (i = 0; i < broj_akcija; i++)
		{
			r = rand() % (pom.size());
			niz.at(pom.at(r)) = "igranje";
			pom.erase(pom.begin() + r);
		}
	}
	void ispis_niza_akcija(vector<string> niz)
	{
		int i;
		for (i = 0; i < niz.size(); i++)
		{
			cout << "" << niz.at(i) << ", ";
		}
		cout << endl;
	}
	void obavljanje_akcija(VirtualPet &pet, vector<string> niz, Food &f)
	{
		int i, g, s, p;
		for (i = 0; i < 2 * broj_akcija; i++)
		{
			g = pet.getGlad();
			s = pet.getSreca();
			p = pet.getPorcije();
			if (niz.at(i) == "hranjenje")
			{
				if (get_counter(f) == 0)
				{
					break;
				}
				else
				{
					pet.hranjenje(g, s);
					f.mijenjanje_cnt();
					f.ispis_cnt();
				}
			}
			else if (niz.at(i) == "igranje")
			{
				pet.igranje(g, s);
			}
			g = pet.getGlad();
			s = pet.getSreca();
			p = pet.getPorcije();
			if (g <= 40)
			{
				pet.spavanje(g, s);
				pet.setGladSreca(g, s, 1, p);
			}
			cout << pet;
		}
	}
	Owner() = default;
	Owner(Owner &stari)
	{
		ime_vlasnika = stari.ime_vlasnika;
		ljubimci = stari.ljubimci;
		broj_akcija = stari.broj_akcija;
		niz_akcija = stari.niz_akcija;
		pomocni_niz = stari.pomocni_niz;
	}
	VirtualPet& max_sreca(vector<VirtualPet> niz, VirtualPet& p)
	{
		int i;
		for (i = 0; i < niz.size(); i++)
		{
			if (niz.at(i) > p)
			{
				p = niz.at(i);
			}
		}
		return p;
	}
};

#endif
