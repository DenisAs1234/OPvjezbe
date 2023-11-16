#include<iostream>
#include<vector>
#include<string>
#include "klase.hpp"
using namespace std;

int main()
{
	Owner vl1;
	Owner vl2;
	int br_ljub;
	cout << "Broj ljubimaca:";
	cin >> br_ljub;
	vl1.ljubimci.resize(br_ljub);
	vl1.ljubimci.resize(br_ljub);
	vl1.unos_ljubimaca(vl1.ljubimci);
	vl2.unos_ljubimaca(vl2.ljubimci);
	cout << "Broj akcija: ";
	cin >> vl1.broj_akcija;
	vl2.broj_akcija = vl1.broj_akcija;
	vl1.niz_akcija.resize(2 * vl1.broj_akcija);
	vl2.niz_akcija.resize(2 * vl2.broj_akcija);
	vl1.pomocni_niz.resize(2 * vl1.broj_akcija);
	vl2.pomocni_niz.resize(2 * vl2.broj_akcija);
	vl1.niz_indeksa(vl1.pomocni_niz);
	vl2.niz_indeksa(vl2.pomocni_niz);
	int i;
	for (i = 0; i < br_ljub; i++)
	{
		vl1.redoslijed_akcija(vl1.pomocni_niz, vl1.niz_akcija);
		vl2.redoslijed_akcija(vl2.pomocni_niz, vl2.niz_akcija);
		cout << "Vlasnik 1:" << endl;
		vl1.ispis_niza_akcija(vl1.niz_akcija);
		cout << "Vlasnik 2:" << endl;
		vl2.ispis_niza_akcija(vl2.niz_akcija);
		vl1.obavljanje_akcija(vl1.ljubimci.at(i), vl1.niz_akcija);
		vl2.obavljanje_akcija(vl2.ljubimci.at(i), vl2.niz_akcija);
		cout << "Vlasnik 1 - Ljubimac " << i+1 << endl;
		vl1.ljubimci.at(i).ispis_bodova(vl1.ljubimci.at(i).glad, vl1.ljubimci.at(i).sreca);
		cout << "Vlasnik 2 - Ljubimac " << i+1 << endl;
		vl2.ljubimci.at(i).ispis_bodova(vl2.ljubimci.at(i).glad, vl2.ljubimci.at(i).sreca);
	}
	return 0;
}