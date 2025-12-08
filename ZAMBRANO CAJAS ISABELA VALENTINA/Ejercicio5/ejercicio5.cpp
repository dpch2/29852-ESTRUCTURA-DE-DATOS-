/* Encontrar el algoritmo de búsqueda binaria para encontrar un elemento K
en una lista de elemen- tos X1, X2, ..., Xn, previamente clasificados en orden ascendente.
El array o vector X se supone ordenado en orden creciente si los datos son numéricos, o
alfabéticamente si son caracteres. Las variables BAJO, CENTRAL, ALTO indican los
límites inferior, central y superior del intervalo de búsqueda.*/
#include <iostream>
using namespace std;

int busquedaBinaria(int* X, int N, int K) {
    int BAJO = 0;
    int ALTO = N - 1;
    int CENTRAL = (BAJO + ALTO) / 2;

    // mientras BAJO <= ALTO y *(X + CENTRAL) != K
    while (BAJO <= ALTO && *(X + CENTRAL) != K) {

        if (K < *(X + CENTRAL)) {
            ALTO = CENTRAL - 1;
        } else {
            BAJO = CENTRAL + 1;
        }

        CENTRAL = (BAJO + ALTO) / 2;
    }

    if (BAJO <= ALTO && *(X + CENTRAL) == K)
        return CENTRAL;
    else
        return -1;
}

int main() {
    int X[] = {3, 8, 12, 17, 25, 30, 45};
    int N = sizeof(X) / sizeof(X[0]);

    int K;
    cout << "Ingrese el valor a buscar: ";
    cin >> K;

    int pos = busquedaBinaria(X, N, K);

    if (pos != -1)
        cout << "Valor encontrado en la posicion " << pos << endl;
    else
        cout << "Valor no encontrado" << endl;

    return 0;
}
