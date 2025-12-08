#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* sig;
};

// Crear tabla hash dinámicamente usando solo punteros
Nodo** crearTabla(int size) {
    Nodo** tabla = new Nodo*[size]; // puntero a punteros
    for (int i = 0; i < size; i++)
        tabla[i] = nullptr;
    return tabla;
}

int hashFunction(int clave, int size) {
    return clave % size;
}

void insertar(Nodo** tabla, int size, int clave) {
    int indice = hashFunction(clave, size);

    Nodo* nuevo = new Nodo();
    nuevo->dato = clave;
    nuevo->sig = nullptr;

    // Inserción al inicio de la lista
    if (tabla[indice] == nullptr) {
        tabla[indice] = nuevo;
    } else {
        nuevo->sig = tabla[indice];
        tabla[indice] = nuevo;
    }
}

void mostrar(Nodo** tabla, int size) {
    cout << "\n----- TABLA HASH -----\n";
    for (int i = 0; i < size; i++) {
        cout << "[" << i << "] -> ";
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            cout << actual->dato << " -> ";
            actual = actual->sig;
        }
        cout << "NULL\n";
    }
}

int main() {
    int size = 10;
    Nodo** tabla = crearTabla(size);

    int n, valor;
    cout << "¿Cuántos valores deseas insertar? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Ingresa un valor entero: ";
        cin >> valor;
        insertar(tabla, size, valor);
    }

    mostrar(tabla, size);
    return 0;
}
