#include <iostream>
using namespace std;

int busquedaBinariaOptimizada(int* arr, int n, int K) {
    
    if (n <= 0) return -1;

    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda < derecha) {
        
        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio] < K) {

            izquierda = medio + 1;
        } else {
 
            derecha = medio;
        }
    }

    if (arr[izquierda] == K) {
        return izquierda;
    } else {
        return -1;
    }
}

int main() {

    int datos[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(datos) / sizeof(datos[0]);

    int objetivo1 = 23;
    int resultado1 = busquedaBinariaOptimizada(datos, n, objetivo1);
    
    int objetivo2 = 10;
    int resultado2 = busquedaBinariaOptimizada(datos, n, objetivo2);

    cout << "Arreglo: ";
    for(int i=0; i<n; i++) cout << datos[i] << " ";
    cout << "\n\n";

    if (resultado1 != -1)
        cout << "Exito: El numero " << objetivo1 << " esta en el indice " << resultado1 << endl;
    else
        cout << "Fallo: El numero " << objetivo1 << " no se encontro." << endl;

    if (resultado2 != -1)
        cout << "Exito: El numero " << objetivo2 << " esta en el indice " << resultado2 << endl;
    else
        cout << "Fallo: El numero " << objetivo2 << " no se encontro." << endl;

    return 0;
}
