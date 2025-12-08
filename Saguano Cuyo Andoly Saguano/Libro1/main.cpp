/*
Ejercicio:
4.- Localice un entero en un arreglo usando una versión recursiva del algoritmo de búsqueda binaria.
El número que se debe buscar (clave) se debe ingresar como argumento por línea de comandos.
El arreglo de datos debe estar previamente ordenado (requisito de la búsqueda binaria).
Comparar esta versión recursiva de la búsqueda binaria con la versión iterativa dada en el capítulo 5.
*/
// Función de búsqueda binaria recursiva usando punteros
#include <iostream>
#include <cstdlib>
using namespace std;
// Búsqueda binaria recursiva
int busquedaRec(int *arr, int inicio, int fin, int clave) {
    if (inicio > fin)
        return -1; // no encontrado

    int medio = (inicio + fin) / 2;

    if (arr[medio] == clave)
        return medio;
    if (clave < arr[medio])
        return busquedaRec(arr, inicio, medio - 1, clave);
    else
        return busquedaRec(arr, medio + 1, fin, clave);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Uso: ./programa <numero_a_buscar>\n";
        return 1;
    }
    int clave = atoi(argv[1]);   // clave desde la linea de comando
    int n;
    cout << "Ingrese el tamano del arreglo: ";
    cin >> n;
    int *arr = new int[n];
    cout << "Ingrese " << n << " numeros ORDENADOS:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int pos = busquedaRec(arr, 0, n - 1, clave);
    if (pos == -1)
        cout << "El numero " << clave << " no se encuentra.\n";
    else
        cout << "El numero " << clave << " esta en la posicion: " << pos << endl;
    delete[] arr;
    return 0;
}
