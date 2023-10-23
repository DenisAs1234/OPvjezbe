#include<iostream>
using namespace std;

struct vect
{
	int size;
	int cap;
	int* niz;
};

vect v;

void vector_new(int vel)
{
	v.niz = new int[vel];
}

void vector_delete()
{
	delete v.niz;
}

void vector_push_back(const int& novi)
{
	v.size += 1;
	v.niz[v.size - 1] = novi;
}

void vector_pop_back()
{
	v.size -= 1;
}

int& vector_front()
{
	return v.niz[0];
}

int& vector_back()
{
	return v.niz[v.size - 1];
}

unsigned int vector_size()
{
	return v.size;
}

int main()
{
	cout << "size:" << endl;
	cin >> v.size;
	cout << "capacity:" << endl;
	cin >> v.cap;
	v.niz = new int[v.size];
	int i;
	for (i = 0; i < v.size; i++)
		cin >> v.niz[i];
	v.niz = new int[2 * v.size];
	int vel;
	cout << "Nova velicina:" << endl;
	cin >> vel;
	vector_new(vel);
	const int x = 10;
	vector_push_back(x);
	vector_pop_back();
	for (i = 0; i < v.size; i++)
	{
		cout << "" << v.niz[i] << " ";
	}
	cout << endl;
	int y = vector_front();
	cout << "Prvi element: " << y << "" << endl;
	int z = vector_back();
	cout << "Zadnji element: " << z << "" << endl;
	int n = vector_size();
	cout << "Velicina niza: " << n << "" << endl;
	vector_delete();
	return 0;
}