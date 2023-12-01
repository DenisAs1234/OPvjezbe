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
public:
	void setImeVrsta(string i, string v)
	{
		ime = i;
		vrsta = v;
	}
	void setGladSreca(int g, int s, int b)
	{
		glad = g;
		sreca = s;
		budnost = b;
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
	void hranjenje(int& glad, int& sreca)
	{
		glad -= 40;
		sreca += 15;
		setGladSreca(glad, sreca, 1);
	}
	void igranje(int& glad, int& sreca)
	{
		glad += 25;
		sreca += 20;
		setGladSreca(glad, sreca, 1);
	}
	void spavanje(int& glad, int& sreca)
	{
		glad = 60;
		sreca += 20;
		setGladSreca(glad, sreca, 0);
	}
	void ispis_bodova(int glad, int sreca)
	{
		cout << "Glad: " << glad << endl;
		cout << "Sreca: " << sreca << endl;
	}
};

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
			niz.at(i).setGladSreca(50, 0, 1);
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
	void obavljanje_akcija(VirtualPet &pet, vector<string> niz)
	{
		int i, g, s;
		for (i = 0; i < 2 * broj_akcija; i++)
		{
			g = pet.getGlad();
			s = pet.getSreca();
			if (niz.at(i) == "hranjenje")
			{
				pet.hranjenje(g, s);
			}
			if (niz.at(i) == "igranje")
			{
				pet.igranje(g, s);
			}
			g = pet.getGlad();
			s = pet.getSreca();
			if (g <= 40)
			{
				pet.spavanje(g, s);
				pet.setGladSreca(g, s, 1);
			}
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
};

#endif