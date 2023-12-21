#include "klase.hpp"
#include<iostream>
#include<string>
#include<vector>

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

void Boss::attack()
{
	health -= damage;
	cout << "Boss napada." << endl;
}

void Monster::attack()
{
	health -= damage;
	cout << "Monster napada." << endl;
}

void Boss::DisplayInfo()
{
	cout << "Name: " << name << endl;
	cout << "Health: " << health << endl;
	cout << "Damage: " << damage << endl;
	cout << "Weapon: " << weapon << endl;
}

void Monster::DisplayInfo()
{
	cout << "Name: " << name << endl;
	cout << "Health: " << health << endl;
	cout << "Damage: " << damage << endl;
	cout << "Ability: " << ability << endl;
}

int main()
{
	vector<Boss> v1(3);
	vector<Monster> v2(3);
	int i;
	for (i = 0; i < 3; i++)
	{
		string ime;
		int hp;
		int dmg;
		string oruzje;
		cout << "Ime: ";
		cin >> ime;
		cout << "Health: ";
		cin >> hp;
		cout << "Damage: ";
		cin >> dmg;
		cout << "Oruzje: ";
		cin >> oruzje;
		try {
			Boss b(ime, hp, dmg, oruzje);
			v1.at(i) = b;
			v1.at(i).attack();
			v1.at(i).DisplayInfo();
		}
		catch (std::invalid_argument& e) {
			cerr << e.what() << endl;
		}
	}
	for (i = 0; i < 3; i++)
	{
		string ime;
		int hp;
		int dmg;
		string sposobnost;
		cout << "Ime: ";
		getline(cin, ime);
		cout << "Health: ";
		cin >> hp;
		cout << "Damage: ";
		cin >> dmg;
		cout << "Sposobnost: ";
		getline(cin, sposobnost);
		Monster m(ime, hp, dmg, sposobnost);
		try {
			Monster(ime, hp, dmg, sposobnost);
		}
		catch (std::invalid_argument& e) {
			cerr << e.what() << endl;
			
		}
		v2.at(i) = m;
		v2.at(i).attack();
		v2.at(i).DisplayInfo();
	}
	return 0;
}