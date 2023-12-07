#ifndef KLASE
#define KLASE
#include<iostream>
#include<string>
using namespace std;

class X {};

class Enemy {
	string name;
	int health;
	int damage;
public:
	string getName();
	int getHealth();
	int getDamage();
	Enemy(string n, int hp, int dmg)
	{
		name = n;
		health = hp;
		damage = dmg;
		try {
			if ((name == "") || (health < 0) || (damage < 0))
				throw X();
		}
		catch (X) {
			cout << "Argument konstruktora je neispravan." << endl;
		}
	}
};

#endif
