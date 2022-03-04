// Laborator1Grafuri.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
ADT graf.

1. Fie un fisier ce contine un graf neorientat reprezentat sub forma: prima linie contine numarul nodurilor iar urmatoarele randuri muchiile grafului. Sa se scrie un program in C/C++ care sa citeasca fisierul si sa reprezinte/stocheze un graf folosind matricea de adiacenta, lista de adiacenta si matricea de incidenta. Sa se converteasca un graf dintr-o forma de reprezentare in alta.

lista de adiacenta -> matr de adiacenta -> matr de incidenta

exemplu fisier
in.txt
4
1 2
3 4
2 3
4 2

2. Fie un graf reprezentat sub o anumita forma (graful este citit dintr-un fisier). Sa se rezolve:
a. sa se determine nodurile izolate dintr-un graf.
b. sa se determine daca graful este regular.
c. pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor.
d. pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.
*/
#include <iostream>
#include <fstream>
#define INF 100000
using namespace std;
ifstream f1("input2.txt");
ifstream f2("input2.txt");


void citire_lista_muchii_to_matrice_adiacenta(int a[101][101],int n) {
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            a[i][j] = 0;
        }
    }

    int aux, bux;
    while(f1 >> aux >> bux)
    {
        a[aux][bux] = a[bux][aux] = 1;
    }
}

void print_consola_matrice(int a[101][101], int n,int m) {
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



void citire_lista_muchii_to_matrice_incidenta(int a[1001][101], int n,int &muchie)
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

int suma_linie(int a[101][101], int n, int i) {
    int sum = 0;
    for (int j = 1; j <= n; j++) {
        sum += a[i][j];
    }
    return sum;
}

void varfuri_izolate(int a[101][101], int n, int vf[101], int &nvf) {
    nvf = 0;
    for (int i = 1; i <= n; i++) {
        if (suma_linie(a, n, i) == 0)
        {
            vf[++nvf] = i;
        }
    }
}

void print_vector(int v[101], int n)
{
    for (int i = 1; i <= n; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

bool graf_regular_matrice_adiacenta(int a[101][101], int n) {
    int gradInit = suma_linie(a, n, 1);
    for (int i = 2; i <= n; i++)
    {
        if (gradInit != suma_linie(a, n, i))
            return false;
    }
    return true;
}

void DFS(int a[101][101], int n, int v[101], int k) {
    v[k] = 1;
    for (int i = 1; i <= n; i++) {
        if (a[k][i] == 1 && v[i] == 0)
        {
            DFS(a, n, v, i);
        }
    }
}

bool verificare_conex(int a[101][101], int n) {
    int v[101] = {};
    DFS(a, n, v, 1);
    for (int i = 1; i <= n; i++) {
        if (v[i] == 0)
            return false;
    }
    return true;
}

void roy_floyd(int a[101][101], int n) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (a[i][k] != INF && a[k][j] != INF) {
                    if (a[i][j] > a[i][k] + a[k][j]) {
                        a[i][j] = a[i][k] + a[k][j];
                    }
                }
            }
        }
    }
}

void matrice_distante(int a[101][101], int n, int roy[101][101]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i != j and a[i][j] == 0)
            {
                roy[i][j] = INF;
            }
            else
            {
                roy[i][j] = a[i][j];
            }
        }
    }
    roy_floyd(roy, n);
}


int main()
{
    int a[101][101];
    int n;
    f1 >> n;
    citire_lista_muchii_to_matrice_adiacenta(a, n);
    cout << "Exercitiul 1\n Lista muchii -> Matrice adiacenta\n";
    print_consola_matrice(a, n, n);
    
    cout << "Exercitiul 1\n Lista muchii -> Matrice incidenta\n";
    int muchii = 1;
    int b[1001][101];
    f2 >> n;
    citire_lista_muchii_to_matrice_incidenta(b, n, muchii);
    print_consola_matrice(b, n, muchii);

    cin.get();

    cout << "Exercitiul 2\n Varfurile izolate\n";
    int vfI[101], nvfI = 0;
    varfuri_izolate(a, n, vfI, nvfI);
    print_vector(vfI, nvfI);

    cout << "Exercitiul 2\n Verificare grad regular\n";
    if (graf_regular_matrice_adiacenta(a, n) == true)
    {
        cout << ">Graful dat este regular\n";
    }   
    else
    {
        cout << ">Graful dat nu este regular\n";
    }

    cout << "Exercitiul 2\n Verificare conexitate\n";
    if (verificare_conex(a, n) == true)
    {
        cout << ">Graful dat este conex\n";
    }
    else
    {
        cout << ">Graful dat nu este conex\n";
    }
    
    cout << "Exercitiul 2\n Matricea distantelor\n";
    int roy[101][101];
    matrice_distante(a, n, roy);
    print_consola_matrice(roy,n,n);

    return 0;
}
