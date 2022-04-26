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


*/

#include <iostream>
#include <fstream>
using namespace std;


#define INF 1000000

int main()
{
    std::cout << "Hello World!\n";
}
