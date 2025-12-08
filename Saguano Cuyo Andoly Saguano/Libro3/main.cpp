#include <iostream>
using namespace std;

/*
Algoritmo de búsqueda binaria:
Encontrar el algoritmo de búsqueda binaria para localizar un elemento K en una lista
de elementos X1, X2, X3, ..., Xn previamente clasificados en orden ascendente.
El arreglo se supone ordenado en orden creciente si los datos son numéricos,
o alfabéticamente si son caracteres.
Las variables Bajo, Central y Alto indican los límites inferior, central y superior
del intervalo de búsqueda.
*/

int busquedaBinaria(int *X, int n, int K) {
    int Bajo = 1;        // posición lógica (1 a n)
    int Alto = n;
    int Central;

    while (Bajo <= Alto) {
        Central = (Bajo + Alto) / 2;
        // Como usamos Bajo-Alto desde 1, el índice real es Central-1
        if (*(X + (Central - 1)) == K) {
            return Central;    // devuelve la posición exacta (1 a n)
        }
        if (K < *(X + (Central - 1))) {
            Alto = Central - 1;   // buscar en la mitad izquierda
        } else {
            Bajo = Central + 1;   // buscar en la mitad derecha
        }
    }
    return -1;   // K no está
}
int main() {
    int n, K;
    cout << "Ingrese n: ";
    cin >> n;
    // Reservar memoria dinámica
    int *X = new int[n];
    cout << "Ingrese los elementos ORDENADOS:\n";
    for (int i = 0; i < n; i++) {
        cin >> *(X + i);   // ingreso con punteros
    }
    cout << "Ingrese K a buscar: ";
    cin >> K;
    int pos = busquedaBinaria(X, n, K);
    if (pos != -1)
        cout << "El elemento " << K << " se encuentra en la posición lógica: " << pos << endl;
    else
        cout << "El elemento NO se encuentra en la lista.\n";
    delete[] X;   // liberar memoria
    return 0;
}
