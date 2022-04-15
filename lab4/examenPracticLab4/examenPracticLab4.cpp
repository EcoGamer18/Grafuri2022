#include <iostream>
#include <fstream>
using namespace std;
ifstream f("date.in.txt");

#define INFINIT 100000

void algoritm_Dijskstra(int** a, int n, int* d,int* p, int s) {
	int* f;
	f = (int*)malloc((n + 1) * sizeof(int));
	for (int i = 1; i <= n; i++)
	{
		f[i] = 0;
		d[i] = a[s][i];
		if (d[i] != INFINIT) {
			p[i] = s;
		}
	}

	f[s] = 1;
	d[s] = 0;
	p[s] = 0;
	d[0] = INFINIT;


	for (int k = 0; k < n - 1; ++k)
	{
		int pmax = 0;
		for (int i = 1; i <= n; ++i)
			if (f[i] == 0 && d[i] < d[pmax])
				pmax = i;

		if (pmax != 0)
		{
			f[pmax] = 1;
			for (int i = 1; i <= n; ++i)
				if (f[i] == 0 && 
					d[i] > d[pmax] + a[pmax][i]) {
					d[i] = d[pmax] + a[pmax][i];
					p[i] = pmax;
				}
		}
	}

	free(f);
}


int main()
{
	int m;

	f >> m;

	int** muchii;

	muchii = (int**)malloc((m+1)*sizeof(int*));
	for (int i = 1; i <= m; i++) {
		muchii[i] = (int*)malloc(4 * sizeof(int));
	}
	
	int n = 0;
	for (int aux = 1; aux <= m;aux++) {
		int i, j, k;
		f >> i >> j >> k;
		if (i > n) {
			n = i;
		}
		if (j > n) {
			n = j;
		}
		muchii[aux][0] = i;
		muchii[aux][1] = j;
		muchii[aux][2] = k;
	}

	int** a;

	a = (int**)malloc((n + 1) * sizeof(int*));
	for (int i = 1; i <= n; i++) {
		a[i] = (int*)malloc((n + 1) * sizeof(int*));
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = INFINIT;
		}
	}

	for (int i = 1; i <= m; i++) {
		a[muchii[i][0]][muchii[i][1]] = muchii[i][2];
	}

	int X, Y;

	f >> X >> Y;

	int* d;
	d = (int*)malloc((n + 1) * sizeof(int));
	int* p;
	p = (int*)malloc((n + 1) * sizeof(int));
	algoritm_Dijskstra(a, n, d, p, X);

	int distanta = d[Y];

	if (distanta == INFINIT) {
		cout << "Nu exista drum intre cele 2 puncte";
	}
	else {
		cout << "Distanta minima este " << distanta << "\n";
		int copil = Y;
		while (copil != X) {
			cout << copil << "<-";
			copil = p[copil];
		}
		cout << X;
	}

	free(d);
	free(p);

	for (int i = 1; i <= n; i++) {
		free(a[i]);
	}
	free(a);

	for (int i = 1; i <= m; i++) {
		free(muchii[i]);
	}
	free(muchii);

	return 0;
}