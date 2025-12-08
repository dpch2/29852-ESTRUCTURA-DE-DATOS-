#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Alumno {
    int legajo;
    char nombre[30];
    char carrera[30];
};

struct IndexEntry {
    int legajo;
    int posicion;
};

// Búsqueda binaria en índice usando punteros
int busquedaBinaria(IndexEntry *indice, int n, int x) {
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if ((indice + medio)->legajo == x)
            return (indice + medio)->posicion;  // devuelve posición en archivo

        if (x < (indice + medio)->legajo)
            fin = medio - 1;
        else
            inicio = medio + 1;
    }
    return -1;
}

// Ordenar índice por legajo (burbuja simple)
void ordenarIndice(IndexEntry *indice, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if ((indice + j)->legajo > (indice + j + 1)->legajo) {
                IndexEntry temp = *(indice + j);
                *(indice + j) = *(indice + j + 1);
                *(indice + j + 1) = temp;
            }
        }
    }
}

int main() {
    ifstream archivo("ALUMNOS.DAT", ios::binary);

    if (!archivo) {
        cout << "No se puede abrir ALUMNOS.DAT\n";
        return 1;
    }

    // Contar registros
    archivo.seekg(0, ios::end);
    streampos tam = archivo.tellg();
    if (tam <= 0) {
        cout << "Archivo vacío o error al leer tamaño.\n";
        return 1;
    }
    int n = tam / sizeof(Alumno);
    archivo.seekg(0, ios::beg);

    // Crear índice en memoria
    IndexEntry *indice = new IndexEntry[n];
    Alumno aux;

    for (int i = 0; i < n; i++) {
        archivo.read(reinterpret_cast<char*>(&aux), sizeof(Alumno));
        (indice + i)->legajo = aux.legajo;
        (indice + i)->posicion = i; // posición física en archivo
    }

    // Ordenar índice por legajo
    ordenarIndice(indice, n);

    int buscado;
    cout << "Ingrese el legajo a buscar: ";
    cin >> buscado;

    int pos = busquedaBinaria(indice, n, buscado);

    if (pos == -1) {
        cout << "No existe un alumno con ese legajo.\n";
    } else {
        archivo.seekg(pos * sizeof(Alumno), ios::beg);
        archivo.read(reinterpret_cast<char*>(&aux), sizeof(Alumno));

        cout << "Alumno encontrado:\n";
        cout << "Legajo: " << aux.legajo << endl;
        cout << "Nombre: " << aux.nombre << endl;
        cout << "Carrera: " << aux.carrera << endl;
    }

    delete[] indice;
    archivo.close();
    return 0;
}
