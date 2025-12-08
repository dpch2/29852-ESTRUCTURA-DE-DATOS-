#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct Producto {
    char nombre[50];
    char categoria[50];
};

// Validar que solo tenga letras o espacios
bool soloLetras(const char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isalpha(texto[i]) && texto[i] != ' ')
            return false;
    }
    return true;
}

// Comparar alfabeticamente nombres
int comparar(const Producto &a, const Producto &b) {
    return strcmp(a.nombre, b.nombre);
}

// Ordenamiento burbuja con punteros
void ordenar(Producto *arr, int n) {
    Producto temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparar(*(arr + j), *(arr + j + 1)) > 0) {
                temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

// Función para verificar coincidencias
bool coincide(const Producto &p, const char *buscado) {
    return strstr(p.nombre, buscado) != NULL || 
           strstr(p.categoria, buscado) != NULL;
}

// Buscar productos por coincidencia parcial
void buscar(Producto *arr, int n) {
    char buscado[50];

    cout << "\nIngrese nombre o categoria a buscar: ";
    cin.ignore();
    cin.getline(buscado, 50);

    if (!soloLetras(buscado)) {
        cout << "Error: Solo se permiten letras.\n";
        return;
    }

    cout << "\n=== RESULTADOS ===\n";
    bool found = false;

    for (int i = 0; i < n; i++) {
        if (coincide(*(arr + i), buscado)) {
            found = true;
            cout << "- " << arr[i].nombre 
                 << " (" << arr[i].categoria << ")\n";
        }
    }

    if (!found)
        cout << "No se encontraron coincidencias.\n";
}

int main() {
    int n;

    cout << "Cuantos productos desea ingresar?: ";
    cin >> n;

    Producto *prod = new Producto[n];

    cout << "\nIngrese los productos (desordenados):\n";
    cout << "Formato: Nombre   Categoria\n\n";

    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << "Producto " << i + 1 << ":\n";

        cout << " Nombre: ";
        cin.getline(prod[i].nombre, 50);
        while (!soloLetras(prod[i].nombre)) {
            cout << " ERROR: Solo letras. Ingrese nuevamente: ";
            cin.getline(prod[i].nombre, 50);
        }

        cout << " Categoria: ";
        cin.getline(prod[i].categoria, 50);
        while (!soloLetras(prod[i].categoria)) {
            cout << " ERROR: Solo letras. Ingrese nuevamente: ";
            cin.getline(prod[i].categoria, 50);
        }

        cout << endl;
    }

    // Ordenar productos
    ordenar(prod, n);

    int opcion;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Buscar producto\n";
        cout << "2. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                buscar(prod, n);
                break;
            case 2:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 2);

    delete[] prod;
    return 0;
}
