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

Am 3 variante de functii plang si urlu;

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

/*


void test_cases(const char* name_of_file_in, const char* name_of_file_out) {

    ifstream fin(name_of_file_in);
    ifstream fout(name_of_file_out);

    int n,m;
    fin >> n >> m;

    vector<vector<int>> g(n, vector<int>(n));
    int x, y;
    for (int i = 0; i < m; i++) {
        fin >> x >> y;
        g[x][y] = g[y][x] = 1;
    }
    // reading the graph in the adjacency matrix

    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            deg[i] += g[i][j];
    }

    int first = 0;
    while (first < n && !deg[first])
        ++first;
    if (first == n) {
        cout << "Testul pica la verificare de grade.";
        return;
    }

    int v1 = -1, v2 = -1;
    bool bad = false;
    for (int i = 0; i < n; ++i) {
        if (deg[i] & 1) {
            if (v1 == -1)
                v1 = i;
            else if (v2 == -1)
                v2 = i;
            else
                bad = true;
        }
    }

    if (v1 != -1)
        ++g[v1][v2], ++g[v2][v1];

    stack<int> st;
    st.push(first);
    vector<int> res;
    while (!st.empty()) {
        int v = st.top();
        int i;
        for (i = 0; i < n; ++i)
            if (g[v][i])
                break;
        if (i == n) {
            res.push_back(v);
            st.pop();
        }
        else {
            --g[v][i];
            --g[i][v];
            st.push(i);
        }
    }

    if (v1 != -1) {
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == v1 && res[i + 1] == v2) ||
                (res[i] == v2 && res[i + 1] == v1)) {
                vector<int> res2;
                for (size_t j = i + 1; j < res.size(); ++j)
                    res2.push_back(res[j]);
                for (size_t j = 1; j <= i; ++j)
                    res2.push_back(res[j]);
                res = res2;
                break;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j])
                bad = true;
        }
    }

    if (bad) {
        cout << "Testul pica inainte de comparatie.";
        return;
    }


    cout << "Testing starting for " << name_of_file_in << "\n";


    for (int i=0,x; i < res.size() and fout >> x; i++) {
        if (x != res[i]) {
            cout << "Testul pica la comparatie pe pozitia " << i << "\n";
            for(int j = 0; j < res.size(); j++) {
                cout << res[j] << " ";
            }
            cout << "\n";
            break;
        }
    }

    fin.close();
    fout.close();

    finish:
    cout << "Testing done for " << name_of_file_in << "\n";
}

*/


#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <stack>
using namespace std;

vector<int> G[100001], L;
vector<pair<int, int>> M;
vector<bool> elim;

void Euler(int k)
{
    stack<int> S;
    S.push(0);
    while (!S.empty())
    {
        int k = S.top();
        if (G[k].size())
        {
            int x = G[k].back();
            G[k].pop_back();
            if (!elim[x])
            {
                elim[x] = 1;
                int p = M[x].second;
                if (p == k)
                    p = M[x].first;
                S.push(p);
            }
        }
        else
        {
            L.push_back(k);
            S.pop();
        }
    }
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

    /*for (int i = 0; i < L.size() - 1 and i < (n + 1) * (n + 1) and fout >> x; i++) {
        if (x != L[i]) {
            cout << "Testul pica la comparatie pe pozitia " << i << "\n";
            for(int j = 0; j < L.size() - 1; j++) {
                cout << L[j] << " ";
            }
            cout << "\n";
            break;
        }
    }*/

    for (int j = 0; j < L.size() - 1; j++) {
        cout << L[j] << " ";
    }
    cout << "\n";

    fin.close();
    fout.close();
    L.clear();
    G->clear();
    elim.clear();
    M.clear();


    cout << "Testing done for " << name_of_file_in << "\n";
}


int main()
{
    // Vârful sursă este 0, iar vârful destinație este (V - 1).

    int x = 1;

    while (x) {
        cin >> x;
        switch (x) {
            case 1:
                test_cases("1-in.txt", "1-out.txt");
                break;
            case 2:
                test_cases("2-in.txt", "2-out.txt");
                break;
            case 3:
                test_cases("3-in.txt", "3-out.txt");
                break;
            case 4:
                test_cases("4-in.txt", "4-out.txt");
                break;
            case 5:
                test_cases("5-in.txt", "5-out.txt");
                break;
            case 6:
                test_cases("6-in.txt", "6-out.txt");
                break;
            case 7:
                test_cases("7-in.txt", "7-out.txt");
                break;
            case 8:
                test_cases("8-in.txt", "8-out.txt");
                break;
            case 9:
                test_cases("9-in.txt", "9-out.txt");
                break;
            case 0:
                cout << "exit condition";
                return 0;
                break;
            default:
                cout << "invalid option";
                break;

        }
    }

    return 0;
}