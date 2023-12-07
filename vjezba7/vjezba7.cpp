#include<iostream>
#include<vector>
#include<string>
#include "klase.hpp"
using namespace std;
int Food::counter = 0;

void VirtualPet::setImeVrsta(string i, string v)
{
	ime = i;
	vrsta = v;
}

void VirtualPet::setGladSreca(int g, int s, int b, int p)
{
	glad = g;
	sreca = s;
	budnost = b;
	broj_porcija = p;
}

string VirtualPet::getIme()
{
	return ime;
}

string VirtualPet::getVrsta()
{
	return vrsta;
}

int VirtualPet::getGlad()
{
	return glad;
}

int VirtualPet::getSreca()
{
	return sreca;
}

int VirtualPet::getBudnost()
{
	return budnost;
}

int VirtualPet::getPorcije()
{
	return broj_porcija;
}

void VirtualPet::hranjenje(int& glad, int& sreca)
{
	glad -= 40;
	sreca += 15;
	broj_porcija++;
	setGladSreca(glad, sreca, 1, broj_porcija);
}

void VirtualPet::igranje(int& glad, int& sreca)
{
	glad += 25;
	sreca += 20;
	setGladSreca(glad, sreca, 1, broj_porcija);
}

void VirtualPet::spavanje(int& glad, int& sreca)
{
	glad = 60;
	sreca += 20;
	setGladSreca(glad, sreca, 0, broj_porcija);
}

void VirtualPet::ispis_bodova(int glad, int sreca)
{
	cout << "Glad: " << glad << endl;
	cout << "Sreca: " << sreca << endl;
}

VirtualPet& VirtualPet::operator= (VirtualPet& other)
{
	ime = other.ime;
	vrsta = other.vrsta;
	glad = other.glad;
	sreca = other.sreca;
	budnost = other.budnost;
	broj_porcija = other.broj_porcija;
	return *this;
}

int operator==(VirtualPet& p1, VirtualPet& p2)
{
	if ((p1.ime != p2.ime) || (p1.vrsta != p2.vrsta) || (p1.glad != p2.glad) || (p1.sreca != p2.sreca) || (p1.budnost != p2.budnost))
		return 0;
	return 1;
}

int operator!=(VirtualPet& p1, VirtualPet& p2)
{
	if (p1 == p2)
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

static int get_counter(Food f)
{
	return f.counter;
}

void Owner::set(string i, int br)
{
	ime_vlasnika = i;
	broj_akcija = br;
}

string Owner::getImeVl()
{
	return ime_vlasnika;
}

vector<VirtualPet> Owner::getLjubimci()
{
	return ljubimci;
}

int Owner::getBrAkcija()
{
	return broj_akcija;
}

vector<string> Owner::getNizAkcija()
{
	return niz_akcija;
}

vector<int> Owner::getPomNiz()
{
	return pomocni_niz;
}

void Owner::unos_ljubimaca(vector<VirtualPet> &niz)
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

void Owner::niz_indeksa(vector<int> &pom)
{
	int i;
	for (i = 0; i < 2 * broj_akcija; i++)
	{
		pom.at(i) = i;
	}
}

void Owner::redoslijed_akcija(vector<int> pom, vector<string> &niz)
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

void Owner::ispis_niza_akcija(vector<string> niz)
{
	int i;
	for (i = 0; i < niz.size(); i++)
	{
		cout << "" << niz.at(i) << ", ";
	}
	cout << endl;
}

void Owner::obavljanje_akcija(VirtualPet &pet, vector<string> niz, Food &f)
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

VirtualPet& Owner::max_sreca(vector<VirtualPet> niz, VirtualPet& p)
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
	cout << "Vlasnik 1:" << endl;
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