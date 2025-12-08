/*diseñe una variacion de busqueda binaria que efectue 
solo una comparacion binaria es decir la comparacion devuelve 
un resultado booleano, de k con un elemento del arreglo cada vez que se invoca
 la funcion puede hacerse compraraciones adiccionales con variables de intervalo. 
 Analice la correcion de su procedimineto.
  Sugerencia ¿cuando debera ser de igualdad (==) la unica comparacion que hace?*/
#include <iostream>
using namespace std;

// Búsqueda binaria con UNA sola comparación directa
int binarySearch1Compare(int *arr, int n, int k) {
    int lo = 0, hi = n - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        // ÚNICA comparación permitida con un elemento del arreglo
        if (*(arr + mid) == k)
            return mid;
        // Si k está en el rango posible de la izquierda:
        if (k >= *(arr + lo) && k <= *(arr + mid - 1)) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    return -1;
}

int main() {
    int n, k;

    cout << "Tamaño del arreglo: ";
    cin >> n;
    // Reservar memoria dinámica
    int *arr = new int[n];

    cout << "Ingrese " << n << " valores ORDENADOS:\n";
    for (int i = 0; i < n; i++)
        cin >> *(arr + i);  
    cout << "Ingrese valor a buscar: ";
    cin >> k;
    // Llamada a la búsqueda
    int pos = binarySearch1Compare(arr, n, k);
    if (pos == -1)
        cout << "No encontrado\n";
    else
        cout << "Encontrado en posición: " << pos << endl;
    delete[] arr; // liberar memoria
    return 0;
}
