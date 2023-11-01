#include <iostream>
#include <iomanip>
using namespace std;

struct matrica
{
	int red;
	int stupac;
	float** mat;
};

void unos(float** A, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "[" << i << "][" << j << "] ";
			cin >> A[i][j];
		}
	}
}

void raspon(float** A, int a, int b)
{
	int i, j;
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			cout << "" << A[i][j] << " ";
		}
		cout << endl;
	}
}

void zbrajanje(float** A, float** B, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "" << A[i][j] + B[i][j] << " ";
		}
		cout << endl;
	}
}

void oduzimanje(float** A, float** B, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "" << A[i][j] - B[i][j] << " ";
		}
		cout << endl;
	}
}

void mnozenje(float** A, float** B, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "" << A[i][j] * B[j][i] << " ";
		}
		cout << endl;
	}
}

void transponiranje(float** A, int r, int s)
{
	int i, j;
	for (j = 0; j < r; j++)
	{
		for (i = 0; i < s; i++)
		{
			cout << "" << A[i][j] << " ";
		}
		cout << endl;
	}
}

void ispisivanje(float** A, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << fixed;
			cout << setprecision(4);
			cout << "" << A[i][j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	matrica M;
	matrica N;
	cout << "Broj redaka i stupaca M matrice:" << endl;
	cin >> M.red;
	cin >> M.stupac;
	cout << "Broj redaka i stupaca N matrice:" << endl;
	cin >> N.red;
	cin >> N.stupac;
	M.mat = new float*[M.red];
	N.mat = new float*[N.red];
	int i;
	for (i = 0; i < M.red; i++)
	{
		M.mat[i] = new float[M.stupac];
	}
	for (i = 0; i < N.red; i++)
	{
		N.mat[i] = new float[N.stupac];
	}
	cout << "Unos M:" << endl;
	unos(M.mat, M.red, M.stupac);
	cout << "Unos N:" << endl;
	unos(N.mat, N.red, N.stupac);
	int a, b;
	cout << "Unos intervala:" << endl;
	cin >> a;
	cin >> b;
	cout << "Generiranje u rasponu:" << endl;
	raspon(M.mat, a, b);
	cout << "Zbrajanje:" << endl;
	zbrajanje(M.mat, N.mat, M.red, M.stupac);
	cout << "Oduzimanje:" << endl;
	oduzimanje(M.mat, N.mat, M.red, M.stupac);
	cout << "Mnozenje:" << endl;
	mnozenje(M.mat, N.mat, M.red, M.stupac);
	cout << "Transponiranje:" << endl;
	transponiranje(M.mat, M.red, M.stupac);
	cout << "Ispis:" << endl;
	ispisivanje(M.mat, M.red, M.stupac);
	for (i = 0; i < M.red; i++)
	{
		delete[] M.mat[i];
	}
	delete[] M.mat;
	for (i = 0; i < N.red; i++)
	{
		delete[] N.mat[i];
	}
	delete[] N.mat;
	return 0;
}