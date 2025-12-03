#include <iostream>
using namespace std;

/*
Una empresa necesita transportar N paquetes en M días.
Cada paquete tiene un peso, y se debe enviar en orden (no se puede cambiar el orden).
Cada día el camión carga paquetes hasta que ya no pueda agregar más por su límite de peso.

Objetivo:
Encontrar la capacidad mínima posible del camión para poder enviar todos los paquetes en M días o menos.
*/

// Calcula cuántos días se necesitan usando capacidad C
int diasNecesarios(int *a, int n, int C) {
    int dias = 1;
    int carga = 0;

    for (int i = 0; i < n; i++) {
        if (carga + *(a+i) > C) {   // No entra → nuevo día
            dias++;
            carga = 0;
        }
        carga += *(a+i);
    }
    return dias;
}

int minimaCapacidad(int *a, int n, int M) {
    int low = 0, high = 0;

    // Hallar límites inferiores y superiores
    for (int i = 0; i < n; i++) {
        low = max(low, *(a+i));   // paquete más pesado
        high += *(a+i);           // suma total
    }

    // Búsqueda binaria sobre la respuesta
    while (low < high) {
        int mid = (low + high) / 2;

        if (diasNecesarios(a, n, mid) <= M)
            high = mid;     // mid funciona → buscamos menor
        else
            low = mid + 1;  // mid no funciona → aumentamos capacidad
    }

    return low;
}

int main() {
    int paquetes[] = {10, 20, 30, 40};
    int n = sizeof(paquetes) / sizeof(paquetes[0]);
    int M = 2;

    cout << "Minima capacidad del camion: "
         << minimaCapacidad(paquetes, n, M) << endl;

    return 0;
}
