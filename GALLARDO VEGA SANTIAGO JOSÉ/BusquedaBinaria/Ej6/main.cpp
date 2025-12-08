#include <iostream>
using namespace std;

int busquedaEspecial(int* E, int primero, int ultimo, int K) {

    if (ultimo < primero)
        return -1;

    int* pPrimero = E + primero;
    int* pUltimo  = E + ultimo;

    // Comparaciones permitidas: con límites del intervalo
    if (K < *pPrimero || K > *pUltimo)
        return -1;

    int medio = (primero + ultimo) / 2;
    int* pMedio = E + medio;

    // ÚNICA comparación contra el arreglo permitida
    if (K == *pMedio)
        return medio;

    // Decidir hacia qué lado ir SIN usar < ni > con pMedio
    // Solo usamos rangos
    if (K <= *pMedio)
        return busquedaEspecial(E, primero, medio - 1, K);
    else
        return busquedaEspecial(E, medio + 1, ultimo, K);
}

int main() {

    int E[] = {2, 5, 9, 14, 20, 27, 31, 40};
    int n = sizeof(E) / sizeof(E[0]);

    int K;
    cout << "Ingrese el valor a buscar: ";
    cin >> K;

    int indice = busquedaEspecial(E, 0, n - 1, K);

    if (indice == -1)
        cout << "No encontrado\n";
    else
        cout << "Encontrado en posicion: " << indice << "\n";

    return 0;
}