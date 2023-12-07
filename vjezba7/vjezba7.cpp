#include<iostream>
#include<vector>
#include<string>
#include "klase.hpp"
using namespace std;
int Food::counter = 0;

int main()
{
	Owner vl1;
	Owner vl2;
	int br_ljub;
	cout << "Broj ljubimaca: ";
	cin >> br_ljub;
	vector<VirtualPet> ljubimci1 = vl1.getLjubimci();
	vector<VirtualPet> ljubimci2 = vl2.getLjubimci();
	ljubimci1.resize(br_ljub);
	ljubimci2.resize(br_ljub);
	string ime_vl1;
	string ime_vl2;
	cout << "Vlasnik 1: " << endl;
	cin >> ime_vl1;
	vl1.unos_ljubimaca(ljubimci1);
	cout << "Vlasnik 2:" << endl;
	cin >> ime_vl2;
	vl2.unos_ljubimaca(ljubimci2);
	int br_akc;
	cout << "Broj akcija: ";
	cin >> br_akc;
	int br_por;
	cout << "Broj porcija: ";
	cin >> br_por;
	Food f(br_por);
	vl1.set(ime_vl1, br_akc);
	vl2.set(ime_vl2, br_akc);
	vector<string> niz_akc1 = vl1.getNizAkcija();
	vector<string> niz_akc2 = vl2.getNizAkcija();
	niz_akc1.resize(2 * vl1.getBrAkcija());
	niz_akc2.resize(2 * vl2.getBrAkcija());
	vector<int> pom_niz1 = vl1.getPomNiz();
	vector<int> pom_niz2 = vl2.getPomNiz();
	pom_niz1.resize(2 * vl1.getBrAkcija());
	vl1.niz_indeksa(pom_niz1);
	pom_niz2.resize(2 * vl2.getBrAkcija());
	vl2.niz_indeksa(pom_niz2);
	int i;
	srand(time(NULL));
	for (i = 0; i < br_ljub; i++)
	{
		vl1.redoslijed_akcija(pom_niz1, niz_akc1);
		cout << ljubimci1.at(i).getIme() << endl;
		vl1.ispis_niza_akcija(niz_akc1);
		vl2.redoslijed_akcija(pom_niz2, niz_akc2);
		cout << ljubimci2.at(i).getIme() << endl;
		vl2.ispis_niza_akcija(niz_akc2);
		vl1.obavljanje_akcija(ljubimci1.at(i), niz_akc1, f);
		cout << ime_vl1 << " - " << ljubimci1.at(i).getIme() << endl;
		ljubimci1.at(i).ispis_bodova(ljubimci1.at(i).getGlad(), ljubimci1.at(i).getSreca());
		vl2.obavljanje_akcija(ljubimci2.at(i), niz_akc2, f);
		cout << ime_vl2 << " - " << ljubimci2.at(i).getIme() << endl;
		ljubimci2.at(i).ispis_bodova(ljubimci2.at(i).getGlad(), ljubimci2.at(i).getSreca());
	}
	VirtualPet p1 = ljubimci1.at(0);
	VirtualPet p2 = ljubimci2.at(0);
	if (vl1.max_sreca(ljubimci1, p1) > vl2.max_sreca(ljubimci2, p2))
	{
		cout << "Najsretniji ljubimac pripada vlasniku " << vl1.getImeVl() << endl;
		cout << vl1.max_sreca(ljubimci1, p1);
	}
	else if (vl1.max_sreca(ljubimci1, p1) < vl2.max_sreca(ljubimci2, p2))
	{
		cout << "Najsretniji ljubimac pripada vlasniku " << vl2.getImeVl() << endl;
		cout << vl2.max_sreca(ljubimci2, p2);
	}
	else
	{
		cout << "Oba vlasnika imaju jednako sretnog ljubimca." << endl;
		cout << vl1.max_sreca(ljubimci1, p1);
		cout << vl2.max_sreca(ljubimci2, p2);
	}
	return 0;
}