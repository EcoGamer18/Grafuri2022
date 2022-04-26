/*
Problema 3 – Ciclu Eulerian

Cerință
Se dă un graf neorientat. Să se găsească un ciclu eulerian în graful dat. Implementarea trebuie să fie eficientă din punctul
de vedere al memoriei folosite și al timpului de execuție.


Formatul sursei
Soluția va fi implementată în limbajul de programare C/C++. Numele sursei va fi „p3.cpp”. Căile fișierelor de intrare și
de ieșire vor fi date ca parametrii în linia de comandă, prima fiind calea fișierului de intrare și a doua fiind calea fișierului
de ieșire.


Formatul fișierului de intrare
Fișierul de intrare conține pe prima linie 2 numere separate prin spațiu V E unde V reprezintă numărul de noduri ale
grafului iar E reprezintă numărul muchiilor grafului.
Următoarele E linii conțin câte 2 numere separate prin spațiu, reprezentând câte o muchie, x y. Indexarea vârfurilor se
face de la 0.
Grafurile din fișierele de intrare sunt euleriene.


Valorile din fișierul de intrare se încadrează în următoarele limite:
• 1 ≤ 𝑉 ≤ 101000;
• 0 ≤ 𝐸 ≤ 501000;
• 0 ≤ 𝑥 < 𝑉;
• 0 ≤ 𝑦 < 𝑉.


Formatul fișierului de ieșire
Fișierul de ieșire va conține o singură linie cu ciclul eulerian. Acesta este reprezentat ca un șir de noduri de forma
𝑛0, 𝑛1, ... , 𝑛𝑚 cu proprietatea că muchia {𝑛0, 𝑛𝑚} și muchiile {ni, ni+1\}, 𝑖 = 0, 𝑚 – 1 există în graful din fișierul de
intrare.
Soluția nu este unică. Se va accepta orice soluție corectă.


https://cp-algorithms.com/graph/euler_path.html

*/

/*
int result_eulerian(int** a, int n, int* result) {
    int* deg = (int*)malloc(sizeof(int)*(n+1));
    for (int i = 0; i < n; i++) {
        deg[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            deg[i] += a[i][j];
    }

    int first = 0;
    while (first < n && !deg[first]) {
       first++;
    }

    if (first == n) {
        cout << -1;
        return 0;
    }

    int v1 = -1, v2 = -1;
    bool bad = false;

    for (int i = 0; i < n; i++) {
        if (deg[i] & 1) {
            if (v1 == -1)
                v1 = i;
            else if (v2 == -1)
                v2 = i;
            else
                bad = true;
        }
    }

    if (v1 != -1){
        a[v1][v2]++;
        a[v2][v1]++;
    }

    int* stack = (int*)malloc(sizeof(int) * (n + 1) * (n + 1));
    stack[0] = first;
    int top = 0;

    int topRes = -1;

    while (top > -1 and top < (n + 1) * (n + 1)) {
        int v = stack[top];
        int i;
        for (i = 0; i < n; i++)
            if (a[v][i] != 0)
                break;

        if (i == n) {
            result[++topRes] = v;
            top--;
        }
        else {
            a[v][i]--;
            a[i][v]--;
            stack[++top] = i;
        }
    }

    if (v1 != -1) {
        for (int i = 0; i < topRes; ++i) {
            if ((result[i] == v1 && result[i + 1] == v2) || (result[i] == v2 && result[i + 1] == v1)) {

                int* result2 = (int*)malloc(sizeof(int) * (n + 1) * (n + 1));
                int topRes2 = -1;

                for (int j = i + 1; j <= topRes; ++j)
                    result2[++topRes2] = result[j];
                for (int j = 1; j <= i; ++j)
                    result2[++topRes2] = result[j];

                result = result2;
                topRes = topRes2;

                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j])
                bad = true;
        }
    }

    if (bad) {
        return 0;
    }


    return topRes;
}


*/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
using namespace std;

vector<int> G[2001], L;
vector<pair<int, int>> M;
vector<bool> elim;

void Euler(int k)
{
    for (auto x : G[k])
    {
        //x = indicele muchiei 
        //M[x].first = k
        //M[x].second = cealalta extremitate
        if (!elim[x])
        {
            elim[x] = 1;
            int p = M[x].second;
            if (p == k)
                p = M[x].first;
            Euler(p);
        }
    }
    L.push_back(k);
}


void test_cases(const char* name_of_file_in, const char* name_of_file_out) {

    ifstream fin(name_of_file_in);
    ifstream fout(name_of_file_out);

    int n, m;

    fin >> n >> m;

    int x, y;
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        M.push_back(pair<int,int>(x,y));
        elim.push_back(false);
        G[x].push_back(M.size() - 1);
        G[y].push_back(M.size() - 1);
    }

    cout << "Testing starting for " << name_of_file_in << "\n";
    
    Euler(0);

    for (int i = 0; i < L.size() and i < (n + 1) * (n + 1) and fout >> x; i++) {
        if (x != L[i]) {
            cout << "Testul pica la comparatie pe pozitia " << i << "\n";
            for(int j = 0; j < L.size(); j++) {
                cout << j << " ";
            }
            cout << "\n";
            break;
        }
    }

    fin.close();
    fout.close();


    cout << "Testing done for " << name_of_file_in << "\n";
}


int main()
{
    // Vârful sursă este 0, iar vârful destinație este (V - 1).

    test_cases("1-in.txt", "1-out.txt");
    test_cases("2-in.txt", "2-out.txt");
    test_cases("3-in.txt", "3-out.txt");
    test_cases("4-in.txt", "4-out.txt");
    test_cases("5-in.txt", "5-out.txt");
    test_cases("6-in.txt", "6-out.txt");
    test_cases("7-in.txt", "7-out.txt");
    test_cases("8-in.txt", "8-out.txt");
    test_cases("9-in.txt", "9-out.txt");

    return 0;
}