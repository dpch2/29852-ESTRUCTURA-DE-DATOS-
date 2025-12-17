/*¿Cómo podría modificar Búsqueda Binaria (¿algoritmo 1.4) para eliminar trabajo
innecesario si se tiene la certeza de que K está en el arreglo? Dibuje un árbol de decisión para
el algoritmo modificado con n = 7. Efectúe análisis de comportamiento promedio y de peor
caso. (Para el promedio, puede suponerse que n = 2 - 1 para alguna k.)*/

#include <iostream>
using namespace std;

int busquedaAsumida(int* A, int n, int K) {
    int low = 0;
    int high = n - 1;

    while (true) {
        int mid = (low + high) / 2;
        int valor = *(A + mid);   

        if (valor == K)
            return mid;

        if (valor < K)
            low = mid + 1;
        else
            high = mid - 1;
    }
}

int main() {
    int datos[] = {3, 7, 12, 20, 25, 31, 42};
    int n = sizeof(datos) / sizeof(datos[0]);

    int K;
    cout << "Ingrese un valor que SI esté en el arreglo: ";
    cin >> K;

    int pos = busquedaAsumida(datos, n, K);

    cout << "Encontrado en la posicion: " << pos << endl;
    cout << "Valor verificado: " << *(datos + pos) << endl;

    return 0;
}
