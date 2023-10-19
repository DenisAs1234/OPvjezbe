#include <iostream>
using namespace std;

typedef struct
{
	int red;
	int stupac;
	float** mat;
}matrica;

void unos(float** A, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "%d,%d" << i, j;
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
			cout << "%lf " << A[a][b];
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
			cout << "%lf " << A[i][j] + B[i][j];
		}
	}
}

void oduzimanje(float** A, float** B, int r, int s)
{
	int i, j;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < s; j++)
		{
			cout << "%lf " << A[i][j] - B[i][j];
		}
	}
}

int main()
{
	matrica M,N;
	int i, j;
	cin >> i;
	cin >> j;
	M.mat = new float*[i];
	N.mat = new float*[i];
	for (int x = 0; x < i; x++)
	{
		M.mat[i] = new float[j];
		N.mat[i] = new float[j];
	}

	unos(M.mat, i, j);
	unos(N.mat, i, j);
	int a, b;
	cin >> a;
	cin >> b;
	raspon(M.mat, a, b);
	zbrajanje(M.mat, N.mat, i, j);
	oduzimanje(M.mat, N.mat, i, j);
}