// Laborator3GrafuriProblema2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

#define INFINIT 1000000000

void algoritm_Dijskstra(int** a, int n, int* d, int s) {
	int* f;
	f = (int*)malloc((n + 1) * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		f[i] = 0;
		d[i] = a[s][i];
	}

	f[s] = 1, d[s] = 0;
	d[n] = INFINIT;
	for (int k = 0; k < n - 1; ++k)
	{
		int pmax = n;
		for (int i = 0; i < n; ++i)
			if (f[i] == 0 && d[i] < d[pmax])
				pmax = i;

		if (pmax < n)
		{
			f[pmax] = 1;
			for (int i = 0; i < n; ++i)
				if (f[i] == 0 && d[i] > d[pmax] + a[pmax][i])
					d[i] = d[pmax] + a[pmax][i];
		}
	}

	free(f);
}


int algoritm_BellmanFord(int** a, int n, int** e, int m,int *d, int s) {
	int i, u, v, k, d[20], p[20], S, flag = 1;
	for (i = 0; i < n; i++)
		d[i] = 1000, p[i] = -1;
	d[s - 1] = 0;
	for (i = 0; i < n - 1; i++)
	{
		for (k = 0; k < m; k++)
		{
			u = e[k][0], v = e[k][1];
			if (d[u] + a[u][v] < d[v])
				d[v] = d[u] + a[u][v], p[v] = u;
		}
	}
	for (k = 0; k < m; k++)
	{
		u = e[k][0], v = e[k][1];
		if (d[u] + a[u][v] < d[v])
			flag = 0;
	}

	return flag;
}


void algoritm_Johnson(int** a, int n, int** e, int m) {
	int* d = (int*)malloc((n + 1) * sizeof(int));
	int result = algoritm_BellmanFord(a, n, e, m, d, 0);


}

int main(int argc, char* argv[])
{
	ifstream fin(argv[1]);

	ofstream fout(argv[2]);

	int n, m;

	fin >> n >> m;

	int** a;
	a = (int**)malloc((n + 1) * sizeof(int*));
	for (int i = 0; i < n; i++) {
		a[i] = (int*)malloc((n + 1) * sizeof(int));
	}

	int** e;
	e = (int**)malloc((n + 1) * sizeof(int*));
	for (int i = 0; i < n; i++) {
		e[i] = (int*)malloc((4) * sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				a[i][j] = INFINIT;
			}
			else {
				a[i][j] = 0;
			}
		}
	}


	int x, y, w;
	for (int i = 0; i < m; i++) {
		fin >> x >> y >> w;
		a[x][y] = w;
		e[i][0] = x;
		e[i][1] = y;
		e[i][2] = w;
	}


	for (int i = 0; i < n; i++) {
		free(a[i]);
	}
	free(a);

	for (int i = 0; i < n; i++) {
		free(e[i]);
	}
	free(e);

	fin.close();
	fout.close();
	return 0;
}
