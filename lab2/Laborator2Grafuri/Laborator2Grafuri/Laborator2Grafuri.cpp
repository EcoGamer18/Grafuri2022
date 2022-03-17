// Laborator2Grafuri.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Laboratorul 2

1. Implementați algoritmul lui Moore pentru un graf orientat neponderat (algoritm bazat pe Breath-first search, vezi cursul 2). 
Datele sunt citete din fisierul graf.txt. Primul rând din graf.txt conține numărul vârfurilor, iar următoarele rânduri conțin muchiile grafului. 
Programul trebuie să afiseze lanțul cel mai scurt dintr-un vârf (vârful sursa poate fi citit de la tastatura).

2. Sa se determine închiderea transitivă a unui graf orientat. 
(Închiderea tranzitivă poate fi reprezentată ca matricea care descrie, pentru fiecare vârf în parte, care sunt vârfurile accesibile din acest vârf. 
Matricea inchiderii tranzitive arată unde se poate ajunge din fiecare vârf.) ex. figura inchidere_tranzitiva.png 
- pentru graful de sus se construieste matricea de jos care arata inchiderea tranzitiva.

3. Să se scrie un program care găsește o soluție pentru unul din următoarele labirinturi: 
labirint_1.txt, 
labirint_2.txt, 
labirint_cuvinte.txt. 
Pentru labirintul 1 si 2 punctul de pornire este indicat de litera S și punctul de oprire este indicat de litera F, 
spre deosebire de labirintul 1 și 2, labirintul 3 nu are o soluție unică.

4. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de algoritmul BFS și distanța față de vârful sursă (arborele descoperit).

5. Pentru un graf dat să se afișeze pe ecran vârfurile descoperite de apelul recursiv al procedurii DFS_VISIT(G, u) (apadurea descoperită de DFS).

*/

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#define INF 100000
using namespace std;
ifstream f1;


void citire_lista_muchii_to_matrice_adiacenta_neorientat(int a[101][101], int n, std::ifstream& f) {
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = 0;
        }
    }

    int aux, bux;
    while (f >> aux >> bux)
    {
        a[aux][bux] = a[bux][aux] = 1;
    }
}

void citire_lista_muchii_to_matrice_adiacenta_orientat(int a[101][101], int n, std::ifstream& f) {
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = 0;
        }
    }

    int aux, bux;
    while (f >> aux >> bux)
    {
        a[aux][bux] = 1;
    }
}

void print_consola_matrice(int a[101][101], int n, int m) {
    cout << "Matricea:\n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i][j] != INF)
            {
                cout << a[i][j] << " ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}

void citire_lista_muchii_to_matrice_incidenta(int a[1001][101], int n, int& muchie,std::ifstream& f)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = 0;
        }
    }

    int aux, bux;
    muchie = 1;
    while (f >> aux >> bux)
    {
        a[bux][muchie] = a[aux][muchie] = 1;
        muchie++;
    }
    muchie -= 1;
}

void print_vector(int v[101], int n)
{
    for (int i = 1; i <= n; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

void algoritmul_moore_matrice_adiacenta(int a[101][101], int n, int l[101],int p[101], int u) {
    for (int i = 1; i <= n; i++)
    {
        l[i] = (i != u) ? INF : 0;
    }
    int q[101] = {};
    q[0] = u;
    int top = 1, current = 0;
    while (current < top) {
        int x = q[current++];
        for (int i = 1; i <= n; i++)
            if (a[x][i] == 1){
                if (l[i] == INF) {
                    p[i] = x;
                    l[i] = l[x] + 1;
                    q[top++] = i;
                }
            }
    }
}

void algoritmul_moore_matrice_adiacenta_print_drum(int a[101][101], int n, int sursa, int destinatia) {
    int l[101] = {}, p[101] = {};
    algoritmul_moore_matrice_adiacenta(a, n, l, p, sursa);
    int k = l[destinatia], pu = destinatia;
    cout << "Vectorul de distante este:\n";
    print_vector(l, n);
    if (k != INF)
    {
        cout << "Drumul este:\n";
        cout << destinatia << "-";
        while (k > 1) {
            pu = p[pu];
            k--;
            cout << pu << "-";
        }
        cout << sursa;
    }
    else
    {
        cout << "Nu exista drum intre " << sursa << " si " << destinatia;
    }
}

void matricea_inchiderii_tranzitive(int a[101][101], int n, int t[101][101]) {
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            t[i][j] = a[i][j];

    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (t[i][j] == 0)
                    t[i][j] = t[i][k] * t[k][j];
}

void BFS_arbore(int a[101][101], int n, int vf[101], int dist[101],int sursa) {
    for (int i = 1; i <= n; i++) {
        dist[i] = (i == sursa) ? 0 : INF;
    }
    *vf = {};
    vf[1] = sursa;
    int top = 2, curent = 1;
    while (curent < top) {
        int k = vf[curent++];
        for (int i = 1; i <= n; ++i)
            if (a[k][i] == 1 && dist[i] == INF) {
                dist[i] = dist[k] + 1;
                vf[top++] = i;
            }
    }
}

void print_arbore_BFS(int vf[101], int dist[101], int n) {
    int distCurent = 0;
    cout << "Distanta " << distCurent << " fata de radacina :";
    for (int i = 1; i <= n; i++){
        if (distCurent != dist[vf[i]]) {
            distCurent++;
            cout << "\nDistanta " << distCurent << " fata de radacina : ";
        }
        cout << vf[i] << " ";
    }
}

void DFS_arbore(int a[101][101], int n, int vf[101], int sursa, int distCurrent = 0) {
    vf[sursa] = distCurrent;
    for (int i = 1; i <= n; i++) {
        if (a[sursa][i] == 1 && vf[i] == INF)
        {
            DFS_arbore(a, n, vf, i,distCurrent+1);
        }
    }
}

void print_arbore_DFS(int vf[101], int n) {
    int distCurent = 0, ok = 0;
    print_vector(vf, n);
    do {
        ok = 0;
        cout << "\nDistanta " << distCurent << " fata de radacina : ";
        for (int i = 1; i <= n; i++) {
            if (distCurent == vf[i]) {
                ok = 1;
                cout << i << " ";
            }
        }
        distCurent++;
    } while (ok != 0);
}

int main()
{
    int a[101][101];
    int n;
    
    cout << ">>Exercitiul 1\n";
    f1.open("input1.txt");
    f1 >> n;
    citire_lista_muchii_to_matrice_adiacenta_neorientat(a, n, f1);
    algoritmul_moore_matrice_adiacenta_print_drum(a, n, 2, 5);
    f1.close();
    f1.clear();

    
    cout << "\n>>Exercitiul 2\n";
    int t[101][101];
    f1.open("input2.txt");
    f1 >> n;
    citire_lista_muchii_to_matrice_adiacenta_orientat(a, n, f1);
    cout << "Matricea de adiacenta:\n";
    print_consola_matrice(a, n, n);
    matricea_inchiderii_tranzitive(a, n, t);
    cout << "Matricea inchiderii tranzitiva este:\n";
    print_consola_matrice(t, n, n);
    f1.close();
    f1.clear();

    cout << "\n>>Exercitiul 3\n";
    cout << "Formatarea acelor fisiere txt ma face sa vreau sa ma sinucid de un arbore.\n";

    cout << "\n>>Exercitiul 4\n";
    f1.open("input1.txt");
    f1 >> n;
    citire_lista_muchii_to_matrice_adiacenta_neorientat(a, n, f1);
    cout << "Varful sursa: ";
    int v,dist[101],vf[101];
    cin >> v;
    BFS_arbore(a, n, vf, dist, v);
    cout << "Arbore:\n";
    print_arbore_BFS(vf, dist, n);
    f1.close();
    f1.clear();

    cout << "\n>>Exercitiul 5\n";
    f1.open("input1.txt");
    f1 >> n;
    citire_lista_muchii_to_matrice_adiacenta_neorientat(a, n, f1);
    cout << "Varful sursa: ";
    cin >> v;
    for (int i = 1; i <= n; i++)
        vf[i] = INF;
    DFS_arbore(a, n, vf, v);
    cout << "Arbore:\n";
    print_arbore_DFS(vf, n);
    f1.close();
    f1.clear();

    return 0;
}