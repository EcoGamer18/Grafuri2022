/*
Problema 1 – flux maxim

Cerință
Se dă un graf orientat fără circuite. Fiecare arc are asociată o capacitate. Să se determine fluxum maxim care poate fi
trimis dintr-un vârf sursă s către un vârf destinație t. Implementați algoritmul Ford-Fulkerson sau Edmonds-Karp pentru
rezolvarea problemei. Implementarea trebuie să fie eficientă din punctul de vedere al memoriei folosite și al timpului de
execuție.


Formatul sursei
Soluția va fi implementată în limbajul de programare C/C++. Numele sursei va fi „p1.cpp”. Căile fișierelor de intrare și
de ieșire vor fi date ca parametrii în linia de comandă, prima fiind calea fișierului de intrare iar a doua fiind calea
fișierului de ieșire.


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


Cormen pg 674 / 684
https://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
https://cp-algorithms.com/graph/edmonds_karp.html
https://brilliant.org/wiki/edmonds-karp-algorithm/

*/
#include <iostream>
#include <fstream>
using namespace std;

#define INF 1000000

// nodurile pot fi si cu 0
// s for source
// d for destination of sinking


void delete_first(int* v, int& n) {
    n++;
    for (int i = 0; i < n - 1; i++) {
        v[i] = v[i + 1];
    }
    n-=2;
}

void print_matrice(int** a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

//custom bfs for ford-fulkerson
bool bfs_ford(int** a, int n, int s, int d, int* p) {

    // Create a visited array and mark all vertices as not
    // visited
    bool* v = (bool*)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        v[i] = false;
    }

    // Create a queue, enqueue source vertex and mark source
    // vertex as visited
    int* q = (int*)malloc(sizeof(int) * n);
    q[0] = s;
    int top = 0;
    v[s] = true;
    p[s] = -1;


    // Standard BFS Loop
    while (top > -1) {
        int u = q[0];
        delete_first(q, top);

        for (int i = 0; i < n; i++) 
            if (v[i] == false && a[u][i] > 0) {
            // If we find a connection to the sink node,
            // then there is no point in BFS anymore We
            // just have to set its parent and can return
            // true
            if (i == d) {
                p[i] = u;
                return true;
            }
            q[++top] = i;   
            p[i] = u;
            v[i] = true;
        }
    }
    
    // We didn't reach sink in BFS starting from source, so return false
    return false;
}


// Returns the maximum flow from s to d in the given graph
int fordFulkerson(int** a, int n, int s, int d)
{

    // Create a residual graph and fill the residual graph
    // with given capacities in the original graph as
    // residual capacities in residual graph
    int** aR = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        aR[i] = (int*)malloc(sizeof(int) * n);
    }


    // Residual graph where aR[i][j]
    // indicates residual capacity of edge
    // from i to j (if there is an edge. If
    // aR[i][j] is 0, then there is not)
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            aR[u][v] = a[u][v];

    int* parent = (int*)malloc(sizeof(int) * n); 
    // This array is filled by BFS and to store path
   

    int max_flow = 0; // There is no flow initially
    int aux;

    // Augment the flow while there is path from source to sink
    while (bfs_ford(aR, n, s, d, parent)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        int path_flow = INT_MAX;
        
        for (int v = d; v != s; v = parent[v]) {
            aux = parent[v];
            path_flow = min(path_flow, aR[aux][v]);
        }

        // update residual capacities of the edges and
        // reverse edges along the path
        for (int v = d; v != s; v = parent[v]) {
            aux = parent[v];
            aR[aux][v] -= path_flow;
            aR[v][aux] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}


//custom bfs for edmond-karp
int bfs_edmond(int** c, int n, int s, int d, int* p) {
    for (int i = 0; i < n; i++) {
        p[i] = -1;
    }
    p[s] = -2;

    int* qNode = (int*)malloc(sizeof(int) * n);
    int* qFlow = (int*)malloc(sizeof(int) * n);
    int top = 0;
    qNode[0] = s;
    qFlow[0] = INF;


    while (top > -1) {
        int current_node = qNode[0];
        int current_flow = qFlow[0];
        delete_first(qNode, top);
        top++;
        delete_first(qFlow, top);

        for (int i = 0; i < n; i++)
            if(p[i] == -1 && c[current_node][i]) {
                p[i] = current_node;
                int new_flow = min(current_flow, c[current_node][i]);
                
                if (i == d) {
                    return new_flow;
                }
                qNode[++top] = i;
                qFlow[top] = new_flow;
        }
    }

    return 0;
}


int edmondKarp(int** c, int n, int s, int d) {
    int flow = 0;
    int* p = (int*)malloc(sizeof(int) * n);
    int new_flow;

    while (new_flow = bfs_edmond(c, n, s, d, p)) {
        flow += new_flow;
        int current_node = d;
        while (current_node != s) {
            int previous = p[current_node];
            c[previous][current_node] -= new_flow;
            c[current_node][previous] += new_flow;
            current_node = previous;
        }
    }

    return flow;
}


void test_cases(const char* name_of_file_in,const char* name_of_file_out) {

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

    int result_ford = fordFulkerson(a, n, 0, n - 1);
    int result_edmond = edmondKarp(a, n, 0, n - 1);
    int expected_result;

    fout >> expected_result;

    fin.close();
    fout.close();

    if (result_ford != expected_result) {
        cout << name_of_file_in << " pica la ford\n\tresult_ford: " << result_ford << "\n\tresult_expected: " << expected_result << "\n";
    }
    else {
        cout << name_of_file_in << " trece ford\n";
    }

    if (result_edmond != expected_result) {
        cout << name_of_file_in << " pica la edmond\n\tresult_edmond: " << result_edmond << "\n\tresult_expected: "<< expected_result << "\n";;
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

