#ifndef KLASE
#define KLASE
#include<iostream>
#include<string>
using namespace std;

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
		if ((name == "") || (health < 0) || (damage < 0))
			throw std::invalid_argument("Argument konstruktora Enemy nije ispravan.");
	}
	virtual void attack() = 0;
	virtual void DisplayInfo() = 0;
};

class Boss : public Enemy {
	string weapon;
public:
	Boss() = default;
	Boss(string n, int hp, int dmg, string w): Enemy(n, hp, dmg)
	{
		weapon = w;
		if (w == "")
			throw std::invalid_argument("Argument konstruktora Boss nije ispravan.");
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
		if (a == "")
			throw std::invalid_argument("Argument konstruktora Monster nije ispravan.");
	}
	virtual void attack();
	virtual void DisplayInfo();
};

#endif
