#ifndef KLASE
#define KLASE
#include<iostream>
#include<string>
using namespace std;

class X {};

class Enemy {
protected:
	string name;
	int health;
	int damage;
public:
	string getName();
	int getHealth();
	int getDamage();
	Enemy() = default;
	Enemy(string n, int hp, int dmg)
	{
		try {
			if ((name == "") || (health < 0) || (damage < 0))
				throw X();
		}
		catch (X) {
			cout << "Argument konstruktora nije ispravan." << endl;
		}
	}
	virtual void attack() = 0;
	virtual void DisplayInfo() = 0;
};

class Boss : public Enemy {
	string weapon;
public:
	Boss() = default;
	Boss(string n, int hp, int dmg, string w)
	{
		name = n;
		health = hp;
		damage = dmg;
		weapon = w;
		try {
			if ((name == "") || (health < 0) || (damage < 0) || (w == ""))
				throw X();
		}
		catch (X) {
			cout << "Argument konstruktora nije ispravan." << endl;
		}
	}
	virtual void attack();
	virtual void DisplayInfo();
};

class Monster : public Enemy {
	string ability;
public:
	Monster() = default;
	Monster(string n, int hp, int dmg, string a)
	{
		name = n;
		health = hp;
		damage = dmg;
		ability = a;
		try {
			if ((name == "") || (health < 0) || (damage < 0) || (a == ""))
				throw X();
		}
		catch (X) {
			cout << "Argument konstruktora nije ispravan." << endl;
		}
	}
	virtual void attack();
	virtual void DisplayInfo();
};

#endif