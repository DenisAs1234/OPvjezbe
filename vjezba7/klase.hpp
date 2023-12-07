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
	void setImeVrsta(string i, string v);
	void setGladSreca(int g, int s, int b, int p);
	string getIme();
	string getVrsta();
	int getGlad();
	int getSreca();
	int getBudnost();
	int getPorcije();
	void hranjenje(int& glad, int& sreca);
	void igranje(int& glad, int& sreca);
	void spavanje(int& glad, int& sreca);
	void ispis_bodova(int glad, int sreca);
	VirtualPet& operator= (VirtualPet& other);
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

static int get_counter(Food f);

class Owner {
	string ime_vlasnika;
	vector<VirtualPet> ljubimci;
	int broj_akcija;
	vector<string> niz_akcija;
	vector<int> pomocni_niz;
public:
	void set(string i, int br);
	string getImeVl();
	vector<VirtualPet> getLjubimci();
	int getBrAkcija();
	vector<string> getNizAkcija();
	vector<int> getPomNiz();
	void unos_ljubimaca(vector<VirtualPet> &niz);
	void niz_indeksa(vector<int> &pom);
	void redoslijed_akcija(vector<int> pom, vector<string> &niz);
	void ispis_niza_akcija(vector<string> niz);
	void obavljanje_akcija(VirtualPet &pet, vector<string> niz, Food &f);
	Owner() = default;
	Owner(Owner &stari)
	{
		ime_vlasnika = stari.ime_vlasnika;
		ljubimci = stari.ljubimci;
		broj_akcija = stari.broj_akcija;
		niz_akcija = stari.niz_akcija;
		pomocni_niz = stari.pomocni_niz;
	}
	VirtualPet& max_sreca(vector<VirtualPet> niz, VirtualPet& p);
};

#endif
