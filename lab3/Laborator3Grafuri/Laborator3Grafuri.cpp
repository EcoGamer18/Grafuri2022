#include <iostream>
#include <fstream>
using namespace std;

#define INFINIT 1000000000

void algoritm_Dijskstra(int a[101][101], int n, int d[101], int s) {
	int f[101];
	for (int i = 0; i < n; i++)
	{
		f[i] = 0;
		d[i] = a[s][i];
	}

	f[s] = 1, d[s] = 0;
	d[0] = INFINIT;
	for (int k = 0; k < n-1; ++k)
	{
		int pmax = 0;
		for (int i = 0; i < n; ++i)
			if (f[i] == 0 && d[i] < d[pmax])
				pmax = i;

		if (pmax > -1)
		{
			f[pmax] = 1;
			for (int i = 0; i < n; ++i)
				if (f[i] == 0 && d[i] > d[pmax] + a[pmax][i])
					d[i] = d[pmax] + a[pmax][i];
		}
	}
}


int main(int argc, char * argv[])
{
    ifstream fin(argv[1]);

    ofstream fout(argv[2]);

	int n, a[101][101], s, m;

	fin >> n >> m >> s;

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


	int d[101];
	algoritm_Dijskstra(a, n, d, s);

	for (int i = 0; i < n; i++) {
		if (d[i] == INFINIT) {
			fout << "INFINIT ";
		}
		else {
			fout << d[i] << " ";
		}
	}

    fin.close();
    fout.close();
    return 0;

}