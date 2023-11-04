#include<iostream>
using namespace std;

struct vect
{
	int logv;
	int fiz;
	int* niz;

	void vector_new(int vel)
	{
		niz = new int[vel];
	}

	void vector_delete()
	{
		delete niz;
	}

	int* vector_push_back(const int& novi)
	{
		niz[logv] = novi;
		logv++;
		return niz;
	}

	void vector_pop_back()
	{
		logv--;
	}

	int& vector_front()
	{
		return niz[0];
	}

	int& vector_back()
	{
		return niz[logv - 1];
	}

	unsigned int vector_size()
	{
		return logv;
	}
};

int main()
{
	vect v, nv;
	cout << "Fizicka velicina: " << endl;
	cin >> v.fiz;
	v.logv = 0;
	v.vector_new(v.fiz);
	int i;
	for (i = 0; i < v.fiz; i++)
	{
		cin >> v.niz[i];
		v.logv++;
	}
	if (v.logv == v.fiz)
	{
		nv.vector_new(2 * v.fiz);
	}
	for (i = 0; i < v.fiz; i++)
	{
		nv.niz[i] = v.niz[i];
	}
	const int x = 10;
	int* noviniz = v.vector_push_back(x);
	cout << "Povecani niz:" << endl;
	for (i = 0; i < v.logv; i++)
	{
		cout << "" << noviniz[i] << " ";
	}
	cout << endl;
	nv.logv = v.logv;
	nv.vector_pop_back();
	cout << "Izbrisan zadnji element:" << endl;
	for (i = 0; i < nv.logv; i++)
	{
		cout << "" << nv.niz[i] << " ";
	}
	cout << endl;
	int y = nv.vector_front();
	cout << "Prvi element: " << y << "" << endl;
	int z = nv.vector_back();
	cout << "Zadnji element: " << z << "" << endl;
	int n = nv.vector_size();
	cout << "Velicina niza: " << n << "" << endl;
	v.vector_delete();
	nv.vector_delete();
	return 0;
}

