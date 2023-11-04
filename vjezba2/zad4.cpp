#include <iostream>
#include <iomanip>
using namespace std;

struct matrica
{
	int red;
	int stupac;
	float** mat;
};

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

void generiranje(float** A, int a, int b)
{
	int i, j;
	float** G;
	G = new float*[a];
	for (i = 0; i < b; i++)
	{
		G[i] = new float[b];
	}
	for (i = 0; i < a; i++)
	{
		for (j = 0; j < b; j++)
		{
			G[i][j] = A[i][j];
		}
	}
	ispisivanje(G, a, b);
	for (i = 0; i < a; i++)
	{
		delete[] G[i];
	}
	delete[] G;
}

void zbrajanje(float** A, float** B, int r, int s)
{
	int i, j;
	float** Z;
	Z = new float*[r];
	for (i = 0; i < s; i++)
	{
		Z[i] = new float[s];
	}
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			Z[i][j] = A[i][j] + B[i][j];
		}
	}
	ispisivanje(Z, r, s);
	for (i = 0; i < r; i++)
	{
		delete[] Z[i];
	}
	delete[] Z;
}

void oduzimanje(float** A, float** B, int r, int s)
{
	int i, j;
	float** O;
	O = new float*[r];
	for (i = 0; i < s; i++)
	{
		O[i] = new float[s];
	}
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			O[i][j] = A[i][j] - B[i][j];
		}
	}
	ispisivanje(O, r, s);
	for (i = 0; i < r; i++)
	{
		delete[] O[i];
	}
	delete[] O;
}

void mnozenje(float** A, float** B, int r1, int s1, int r2, int s2)
{
	int i, j, k;
	float** C;
	C = new float*[r1];
	for (i = 0; i < s2; i++)
	{
		C[i] = new float[s2];
	}
	for (i = 0; i < r1; i++)
	{
		for (j = 0; j < s2; j++)
		{
			C[i][j] = 0;
			for (k = 0; k < s1; k++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	ispisivanje(C, r1, s2);
	for (i = 0; i < r1; i++)
	{
		delete[] C[i];
	}
	delete[] C;
}

void transponiranje(float** A, int r, int s)
{
	int i, j;
	float** T;
	T = new float*[s];
	for (i = 0; i < s; i++)
	{
		T[i] = new float[r];
	}
	for (i = 0; i < s; i++)
	{
		for (j = 0; j < r; j++)
		{
			T[i][j] = A[j][i];
		}
	}
	ispisivanje(T, s, r);
	for (i = 0; i < s; i++)
	{
		delete[] T[i];
	}
	delete[] T;
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
	generiranje(M.mat, a, b);
	cout << "Zbrajanje:" << endl;
	zbrajanje(M.mat, N.mat, M.red, M.stupac);
	cout << "Oduzimanje:" << endl;
	oduzimanje(M.mat, N.mat, M.red, M.stupac);
	cout << "Mnozenje:" << endl;
	mnozenje(M.mat, N.mat, M.red, M.stupac, N.red, N.stupac);
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
