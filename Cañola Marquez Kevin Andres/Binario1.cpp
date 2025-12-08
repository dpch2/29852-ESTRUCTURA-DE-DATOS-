#include <iostream>
#include <cstring>
using namespace std;

// Función para ordenar palabras usando burbuja
void ordenarPalabras(char** arr, int n) {
    char temp[100];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

// Búsqueda binaria de cadenas
int busquedaBinaria(char** arr, int n, const char* objetivo) {
    int izquierda = 0, derecha = n - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;
        int cmp = strcmp(arr[medio], objetivo);

        if (cmp == 0)
            return medio;  // encontrado
        else if (cmp < 0)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }
    return -1; // no encontrado
}

int main() {
    int n;
    cout << "Cuantas palabras desea ingresar?: ";
    cin >> n;

    cin.ignore(); // limpiar buffer

    // Crear arreglo dinámico de punteros
    char** palabras = new char*[n];

    cout << "\nIngrese " << n << " palabras (no importa el orden):\n";

    for (int i = 0; i < n; i++) {
        palabras[i] = new char[100];
        cin.getline(palabras[i], 100);
    }

    // Ordenar palabras
    ordenarPalabras(palabras, n);

    int opcion;
    char buscar[100];

    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Buscar palabra\n";
        cout << "2. Mostrar lista ordenada\n";
        cout << "3. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            cout << "Ingrese palabra a buscar: ";
            cin.getline(buscar, 100);

            int pos = busquedaBinaria(palabras, n, buscar);

            if (pos != -1)
                cout << "La palabra SI se encuentra (posicion " << pos << ").\n";
            else
                cout << "La palabra NO se encuentra.\n";

        } else if (opcion == 2) {
            cout << "\nLista ordenada:\n";
            for (int i = 0; i < n; i++)
                cout << palabras[i] << endl;

        } else if (opcion == 3) {
            cout << "Saliendo del programa...\n";
            break;

        } else {
            cout << "Opcion invalida.\n";
        }
    }

    // Liberar memoria
    for (int i = 0; i < n; i++)
        delete[] palabras[i];

    delete[] palabras;

    return 0;
}
