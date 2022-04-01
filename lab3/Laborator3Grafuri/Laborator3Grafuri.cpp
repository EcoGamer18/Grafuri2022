#include <iostream>
#include <fstream>
using namespace std;

#define INFINIT 1000000000

void algoritm_Dijskstra(int **a, int n, int *d, int s) {
	int *f;
	f = (int*)malloc((n+1) * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		f[i] = 0;
		d[i] = a[s][i];
	}

	f[s] = 1, d[s] = 0;
	d[n] = INFINIT;
	for (int k = 0; k < n-1; ++k)
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


int main(int argc, char * argv[])
{
    ifstream fin(argv[1]);

    ofstream fout(argv[2]);

	int n, s, m;

	fin >> n >> m >> s;

	int** a;
	a = (int**)malloc((n + 1) * sizeof(int*));
	for (int i = 0; i < n; i++) {
		a[i] = (int*)malloc((n + 1) * sizeof(int));
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			a[i][j] = INFINIT;
		}
	}


	int x, y, w;
	for (int i = 0; i < m;i++) {
		fin >> x >> y >> w;
		a[x][y] = w;
	}


	int *d;
	d = (int*)malloc((n + 1) * sizeof(int));
	algoritm_Dijskstra(a, n, d, s);

	for (int i = 0; i < n; i++) {
		if (d[i] == INFINIT) {
			fout << "INF ";
		}
		else {
			fout << d[i] << " ";
		}
	}
	
	free(d);
	for (int i = 0; i < n; i++) {
		free(a[i]);
	}
	free(a);

    fin.close();
    fout.close();
    return 0;

}