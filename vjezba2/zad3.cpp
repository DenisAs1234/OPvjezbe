#include<iostream>
using namespace std;

struct vect
{
	int logv;
	int fiz;
	int* niz;
};

vect v, nv;

void vector_new(int vel)
{
	v.niz = new int[vel];
}

void vector_delete()
{
	delete v.niz;
	delete nv.niz;
}

int* vector_push_back(const int& novi)
{
	int i;
	if (v.logv == v.fiz)
	{
		nv.niz = new int[2 * v.fiz];
	}
	v.fiz = 2 * v.fiz;
	for (i = 0; i < v.fiz; i++)
	{
		nv.niz[i] = v.niz[i];
	}
	nv.niz[v.logv] = novi;
	v.logv++;
	return nv.niz;
}

void vector_pop_back()
{
	v.logv--;
}

int& vector_front()
{
	return nv.niz[0];
}

int& vector_back()
{
	return nv.niz[v.logv - 1];
}

unsigned int vector_size()
{
	return v.fiz;
}

int main()
{
	cout << "Fizicka velicina: " << endl;
	cin >> v.fiz;
	v.logv = 0;
	v.niz = new int[v.fiz];
	int i;
	for (i = 0; i < v.fiz; i++)
	{
		cin >> v.niz[i];
		v.logv++;
	}
	const int x = 10;
	int* noviniz = vector_push_back(x);
	cout << "Povecani niz:" << endl;
	for (i = 0; i < v.logv; i++)
	{
		cout << "" << noviniz[i] << " ";
	}
	cout << endl;
	vector_pop_back();
	cout << "Izbrisan zadnji element:" << endl;
	for (i = 0; i < v.logv; i++)
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
	vector_new(v.fiz);
	vector_delete();
	return 0;
}
