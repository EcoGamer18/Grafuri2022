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
#define INF 100000
using namespace std;
ifstream f1;
ifstream f2;


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

void citire_lista_muchii_to_matrice_incidenta(int a[1001][101], int n, int& muchie)
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
    while (f2 >> aux >> bux)
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
    f2.open("input2.txt");
    f2 >> n;
    citire_lista_muchii_to_matrice_adiacenta_orientat(a, n, f2);
    cout << "Matricea de adiacenta:\n";
    print_consola_matrice(a, n, n);
    matricea_inchiderii_tranzitive(a, n, t);
    cout << "Matricea inchiderii tranzitiva este:\n";
    print_consola_matrice(t, n, n);
    f2.close();
    f2.clear();

    cout << "\n>>Exercitiul 3\n";



    return 0;
}