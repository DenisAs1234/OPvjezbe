#ifndef KLASE
#define KLASE
#include<iostream>
#include<vector>
#include<string>
using namespace std;

class VirtualPet {
	string ime;
	string vrsta;
	int glad;
	int sreca;
	int budnost;
public:
	void Igranje(int &glad, int &sreca)
	{
		glad += 3;
		sreca += 3;
	}
	void Spavanje(int &glad, int &sreca)
	{
		glad += 1;
		sreca += 2;
	}
	void Hranjenje(int &glad, int &sreca)
	{
		glad -= 3;
		sreca += 5;
	}
};

class Owner {
	vector<string> akcije {"jede","igra se"};
	vector<VirtualPet> ljubimci;
};

#endif