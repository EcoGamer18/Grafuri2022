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
https://cp-algorithms.com/graph/push-relabel-faster.html

https://www.geeksforgeeks.org/relabel-to-front-algorithm/
http://www.euroinformatica.ro/documentation/programming/!!!Algorithms_CORMEN!!!/DDU0165.html

*/

/*
INITIALIZARE_PREFLUX(G,s,t)
1: \\ iniţializare f (u, v) și h(u, v), ∀u, v ∈ V
2: for fiecare v ∈ V do
3:      v.h = 0
4:      v.e = 0
5: for fiecare (u, v) ∈ E do
6:      (u,v).f=0
7:      s.h = |V|
8: for fiecare v ∈ s.Adj do
9:      (s, v).f = c(s, v)
10:     v.e = c(s, v)
11:     s.e = s.e − c(s, v)


POMPARE_PREFLUX(G,s,t)
1: INITIALIZARE_PREFLUX(G,s,t)
2: while TRUE do
3:      if ∃u /∈ {s, t} ∧ u.e > 0 ∧ cf (u, v) > 0 ∧ u.h = v.h + 1 then
4:          POMPARE(u,v)
5:          continue
6:      if ∃u /∈ {s, t} ∧ u.e > 0 ∧ [u.h ≤ v.h|∀v ∈ V, (u, v) ∈ Ef ] then
7:          INALTARE(u)
8:          continue
9:      break


POMPARE_TOPOLOGICA(G,s,t)
1:      INITIALIZARE_PREFLUX(G,s,t)
2:      L = V \ {s, t}
3:      for fiecare u ∈ V \ {s, t} do
4:          u.curent = u.N.head
5:          u = L.head
6:      while u 6 = N IL do
7:          înalţime_veche = u.h
8:          DESCARCARE(u)
9:          if u.h > înalţime_veche then
10:             muta u în capul listei L
11:         u.next


DESCARCARE(u)
1: while u.e > 0 do
2:      v = u.curent
3:      if v == N IL then
4:          INALTARE(u)
5:          u.curent = u.N.head
6:      else if cf (u, v) > 0 ∧ u.h == v.h + 1 then
7:          POMPARE(u,v)
8:      else
9:          u.curent = u.urmatorul_vecin
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

/*
INITIALIZE-PREFLOW(G, s)
 1  for each vertex u ∈ V[G]
 2       do h[u] ← 0
 3          e[u] ← 0
 4  for each edge (u, v) ∈ E[G]
 5       do f[u, v] ← 0
 6          f[v, u] ← 0
 7  h[s] ← |V[G]|
 8  for each vertex u ∈ Adj[s]
 9       do f[s, u] ← c(s, u)
10          f[u, s] ← -c(s,  u)
11          e[u] ← c(s, u)
12          e[s] ← e[s] - c(s, u)

DISCHARGE(u)
1  while e[u] > 0
2      do v ← current[u]
3          if v = NIL
4             then RELABEL(u)
5                  current[u] ← head[N[u]]
6          elseif cf(u, v) > 0 and h[u] = h[v] + 1
7            then PUSH(u, v)
8          else current[u] ← next-neighbor[v]


RELABEL-TO-FRONT(G, s, t)
 1  INITIALIZE-PREFLOW(G, s)
 2  L ← V[G] - {s, t}, in any order
 3  for each vertex u ∈ V[G] - {s, t}
 4      do current[u] ← head[N[u]]
 5  u ← head[L]
 6  while u ≠ NIL
 7     do old-height ← h[u]
 8        DISCHARGE(u)
 9        if h[u] > old-height
10           then move u to the front of list L
11        u ← next[u]
*/



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
    int result_relabel_to_front = 0;
    int expected_result;

    fout >> expected_result;

    fin.close();
    fout.close();

    if (result_push_relabel != expected_result) {
        cout << name_of_file_in << " pica la push-relabel\n\tresult_push_relabel: " << result_push_relabel << "\n\tresult_expected: " << expected_result << "\n";
    }
    else {
        cout << name_of_file_in << " trece push-relabel\n";
    }

    if (result_relabel_to_front != expected_result) {
        cout << name_of_file_in << " pica la relabel-to-front\n\tresult_edmond: " << result_relabel_to_front << "\n\tresult_expected: " << expected_result << "\n";;
    }
    else {
        cout << name_of_file_in << " trece relabel-to-front\n";
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
