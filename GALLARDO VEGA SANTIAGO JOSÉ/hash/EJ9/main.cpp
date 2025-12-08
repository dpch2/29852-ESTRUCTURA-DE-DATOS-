#include <iostream>
#include <cstring>
using namespace std;

// Convertir letra o número a valor entero (A=1, B=2,..., Z=26, '1'=1)
int valorClave(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
    if (c >= '0' && c <= '9') return c - '0';
    return 0;
}

int main() {
    const int TAM = 13;
    char tabla[TAM];
    // Inicializar tabla vacía
    for (int i = 0; i < TAM; i++) tabla[i] = '-';

    // Claves a insertar
    const char claves[] = {'C','U','E','S','T','1','O','N','F','A','C','I','L'};
    int n = sizeof(claves)/sizeof(claves[0]);

    for (int i = 0; i < n; i++) {
        int k = valorClave(claves[i]);
        int pos = k % TAM;
        int inicial = pos;

        // Exploración lineal
        while (tabla[pos] != '-') {
            pos = (pos + 1) % TAM;
            if (pos == inicial) {
                cout << "Tabla llena, no se puede insertar " << claves[i] << endl;
                break;
            }
        }
        tabla[pos] = claves[i];
    }

    // Imprimir tabla
    cout << "Tabla de dispersión (lineal):\n";
    for (int i = 0; i < TAM; i++) {
        cout << i << ": " << tabla[i] << endl;
    }

    return 0;
}