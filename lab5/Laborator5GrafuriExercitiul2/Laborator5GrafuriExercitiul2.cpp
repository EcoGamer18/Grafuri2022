/*
Problema 2 – flux maxim

Cerință
Se dă un graf orientat fără circuite. Fiecare arc are asociată o capacitate. Să se determine fluxum maxim care poate fi
trimis dintr-un vârf sursă s către un vârf destinație t. Implementați algoritmul pompare-preflux sau pompare topologică
pentru rezolvarea problemei. Implementarea trebuie să fie eficientă din punctul de vedere al memoriei folosite și al
timpului de execuție.


Formatul sursei
Soluția va fi implementată în limbajul de programare C/C++. Numele sursei va fi „p2.cpp”. Căile fișierelor de intrare și
de ieșire vor fi date ca parametrii în linia de comandă, prima fiind calea fișierului de intrare și a doua fiind calea fișierului
de ieșire.


Formatul fișierului de intrare
Fișierul de intrare conține pe prima linie 2 numere separate prin spațiu V E unde V reprezintă numărul de vârfuri ale
grafului iar E reprezintă numărul de arce ale grafului.
Următoarele E linii conțin câte 3 numere separate prin spațiu, reprezentând câte un arc: x y c. x este nodul sursă al
arcului, y este nodul destinație, iar c este capacitatea arcului. Indexarea vârfurilor se face de la 0.
Vârful sursă este 0, iar vârful destinație este (V - 1).


Valorile din fișierul de intrare se încadrează în următoarele limite:
• 1 ≤ 𝑉 ≤ 1000;
• 0 ≤ 𝐸 ≤ 50000;
• 0 ≤ 𝑥 < 𝑉;
• 0 ≤ 𝑦 < 𝑉;
• 1 ≤ 𝑤 ≤ 1000.


Formatul fișierului de ieșire
Fișierul de ieșire va conține o singură linie cu valoarea fluxului maxim.


Curs 8
https://www.geeksforgeeks.org/push-relabel-algorithm-set-1-introduction-and-illustration/
https://www.geeksforgeeks.org/push-relabel-algorithm-set-2-implementation/
https://cp-algorithms.com/graph/push-relabel.html

https://www.geeksforgeeks.org/relabel-to-front-algorithm/

*/

#include <iostream>
#include <fstream>
using namespace std;

#define INF 1000000

void delete_first(int* v, int& n) {
    n++;
    for (int i = 0; i < n - 1; i++) {
        v[i] = v[i + 1];
    }
    n -= 2;
}

void push(int** capacity, int** flow, int* excess, int n, int* excess_vertices, int& top, int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d != 0 && excess[v] == d) {
        excess_vertices[++top] = v;
    }
}

void relabel(int** capacity, int** flow, int* height, int n, int u) {
    int d = INF;
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 0) {
            d = min(d, height[i]);
        }
    }
    if (d < INF) {
        height[u] = d + 1;
    }
}

void discharge(int** capacity, int** flow, int* height, int* seen, int* excess, int n, int* excess_vertices, int& top, int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 0 && height[u] > height[v])
                push(capacity, flow, excess, n, excess_vertices, top, u, v);
            else
                seen[u]++;
        }
        else {
            relabel(capacity,flow,height,n,u);
            seen[u] = 0;
        }
    }
}

int max_flow_push_relabel(int** capacity, int n, int s, int d) {
    int* height = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        height[i] = 0;
    }
    height[s] = n;


    int** flow = (int**)malloc(sizeof(int*) * n);

    for (int i = 0; i < n; i++) {
        flow[i] = (int*)malloc(sizeof(int) * n);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            flow[i][j] = 0;
        }


    int* excess = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        excess[i] = 0;
    }
    excess[s] = INF;

    int* excess_vertices = (int*)malloc(sizeof(int) * n * n);
    int top = -1;


    for (int i = 0; i < n; i++) {
        if (i != s)
            push(capacity,flow,excess,n,excess_vertices,top,s,i);
    }


    int* seen = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        seen[i] = 0;
    }

    while (top > -1) {
        int u = excess_vertices[0];
        delete_first(excess_vertices, top);
        if (u != s && u != d)
            discharge(capacity,flow,height,seen,excess,n,excess_vertices,top,u);
    }

    int max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][d];
    return max_flow;
}


void test_cases(const char* name_of_file_in, const char* name_of_file_out) {

    ifstream fin(name_of_file_in);
    ifstream fout(name_of_file_out);

    int n, m;

    fin >> n >> m;

    int** a = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(sizeof(int) * n);
    }


    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = 0;
        }


    int x, y, cap;
    for (int i = 0; i < m; i++) {
        fin >> x >> y >> cap;
        a[x][y] = cap;
    }

    int result_push_relabel = max_flow_push_relabel(a, n, 0, n - 1);
    int result_edmond = 0;
    int expected_result;

    fout >> expected_result;

    fin.close();
    fout.close();

    if (result_push_relabel != expected_result) {
        cout << name_of_file_in << " pica la push-relabel\n\tresult_ford: " << result_push_relabel << "\n\tresult_expected: " << expected_result << "\n";
    }
    else {
        cout << name_of_file_in << " trece push-relabel\n";
    }

    if (result_edmond != expected_result) {
        cout << name_of_file_in << " pica la edmond\n\tresult_edmond: " << result_edmond << "\n\tresult_expected: " << expected_result << "\n";;
    }
    else {
        cout << name_of_file_in << " trece edmond\n";
    }

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
    test_cases("10-in.txt", "10-out.txt");

    return 0;
}
