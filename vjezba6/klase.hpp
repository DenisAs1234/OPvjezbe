#ifndef KLASE
#define KLASE
#include<iostream>
#include<vector>
#include<string>
#include<time.h>
using namespace std;

class VirtualPet {
public:
	string ime;
	string vrsta;
	int glad;
	int sreca;
	int budnost;
	void hranjenje(int& glad, int& sreca)
	{
		glad -= 40;
		sreca += 15;
	}
	void igranje(int& glad, int& sreca)
	{
		glad += 20;
		sreca += 25;
	}
	void spavanje(int& glad, int& sreca)
	{
		glad = 60;
		sreca += 20;
	}
	void ispis_bodova(int glad, int sreca)
	{
		cout << "Glad: " << glad << endl;
		cout << "Sreca: " << sreca << endl;
	}
};

class Owner {
public:
	string ime_vlasnika;
	vector<VirtualPet> ljubimci;
	int broj_akcija;
	vector<string> niz_akcija;
	vector<int> pomocni_niz;
	void unos_ljubimaca(vector<VirtualPet> &niz)
	{
		int i;
		for (i = 0; i < niz.size(); i++)
		{
			cout << "Ljubimac " << i + 1 << endl;
			cout << "Ime: ";
			cin >> niz.at(i).ime;
			cout << "Vrsta: ";
			cin >> niz.at(i).vrsta;
			niz.at(i).glad = 50;
			niz.at(i).sreca = 0;
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
		int i;
		for (i = 0; i < 2 * broj_akcija; i++)
		{
			if (niz.at(i) == "hranjenje")
			{
				pet.hranjenje(pet.glad, pet.sreca);
			}
			if (niz.at(i) == "igranje")
			{
				pet.igranje(pet.glad, pet.sreca);
			}
			if (pet.glad <= 40)
			{
				pet.spavanje(pet.glad, pet.sreca);
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