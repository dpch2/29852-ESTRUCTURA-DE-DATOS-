#include <iostream>

using namespace std;

int busquedaBinariaModificada(int arr[], int n, int K) {
    int low = 0;
    int high = n - 1;

    // Mientras el intervalo tenga más de un elemento
    while (low < high) {

        int mid = low + (high - low) / 2;

        if (arr[mid] < K) {
            
            low = mid + 1;
        } else {

            high = mid;
        }
    }

    return low; 
}

int main() {

    int arreglo[] = {10, 20, 30, 40, 50, 60, 70};
    int n = 7; 
    
    int objetivo = 30; 

    cout << "Arreglo: ";
    for(int i = 0; i < n; i++) cout << arreglo[i] << " ";
    cout << endl;

    int indice = busquedaBinariaModificada(arreglo, n, objetivo);

    cout << "El valor " << objetivo << " se encuentra en el indice: " << indice << endl;

    if (arreglo[indice] == objetivo) {
        cout << "Verificacion Exitosa." << endl;
    }

    return 0;
}