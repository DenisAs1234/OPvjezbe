#include "klase.hpp"
#include<iostream>
#include<string>

string Enemy::getName()
{
	return name;
}

int Enemy::getHealth()
{
	return health;
}

int Enemy::getDamage()
{
	return damage;
}

int main()
{
	string ime;
	int hp;
	int dmg;
	cout << "Name: ";
	getline(cin, ime);
	cout << "Health: ";
	cin >> hp;
	cout << "Damage: ";
	cin >> dmg;
	Enemy e(ime, hp, dmg);
	return 0;
}