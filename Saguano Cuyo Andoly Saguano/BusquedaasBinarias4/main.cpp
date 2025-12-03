/*
 EJERCICIO: Capacidad mínima de discos
 Tienes n archivos con tamaños en MB.
 Debes grabarlos en k discos, manteniendo el orden de los archivos.
 NO puedes dividir un archivo; cada archivo va completo a un solo disco.
 Cada disco tiene una capacidad máxima X.
 Debes encontrar la capacidad mínima X tal que los n archivos
 puedan ser guardados en orden usando k discos o menos.
 ENTRADA:
   n k
   a1 a2 a3 ... an   (tamaños de archivos)
 SALIDA:
   Capacidad mínima X necesaria para los discos.
 EJEMPLO:
   Entrada:
   5 3
   4 8 5 7 3
   Salida:
   12
*/

#include <iostream>
#include <algorithm>
using namespace std;
bool isPossible(long long X, long long* a, int n, int k) {
    int discos = 1;       // empezamos usando 1 disco
    long long suma = 0;   

    for (int i = 0; i < n; i++) {

        // Si un archivo es más grande que X, imposible
        if (a[i] > X) return false;
        // Si cabe en el disco actual, lo agregamos
        if (suma + a[i] <= X) {
            suma += a[i];
        }
        else {
            // Si no cabe, abrimos un nuevo disco
            discos++;
            suma = a[i];  // este archivo va al nuevo disco
            // Si ya usamos más discos que k, NO es posible
            if (discos > k) return false;
        }
    }
    return true; // Se pudo usando k discos o menos
}

int main() {

    int n, k;
    cin >> n >> k;
    long long* a = new long long[n];
    // Leer los tamaños de los archivos
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long low = 1;
    long long high = 0;

    // high será la suma de TODOS los archivos
    for (int i = 0; i < n; i++) {
        high += a[i];
    }

    long long ans = high;
    while (low <= high) {
        long long mid = (low + high) / 2;

        if (isPossible(mid, a, n, k)) {
            ans = mid;        // esta capacidad funciona
            high = mid - 1;   // intentamos una menor
        }
        else {
            low = mid + 1;    // debemos aumentar la capacidad
        }
    }

    // Imprimir la capacidad mínima encontrada
    cout << ans << endl;
    return 0;
}
