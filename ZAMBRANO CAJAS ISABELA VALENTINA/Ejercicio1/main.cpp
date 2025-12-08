#include <iostream>
#include <fstream>
using namespace std;

struct Alumno {
    int legajo;
    char nombre[50];
    char carrera[30];
    float promedio;
};

struct RegistroIndice {
    int legajo;
    streampos posicion;
};

void generarArchivo(const char* nombreArchivo) {
    fstream archivo(nombreArchivo, ios::binary | ios::out);

    if (!archivo) {
        cout << "Error al crear archivo.\n";
        return;
    }

    // Datos de prueba (ordenados por legajo)
    Alumno a1 = {101, "Ana_Garcia", "Ingenieria", 8.5};
    Alumno a2 = {105, "Luis_Perez", "Arquitectura", 7.2};
    Alumno a3 = {204, "Maria_Lopez", "Medicina", 9.1};
    Alumno a4 = {300, "Carlos_Ruiz", "Derecho", 6.8};
    Alumno a5 = {450, "Sofia_Mendieta", "Sistemas", 9.5};

    archivo.write((char*)&a1, sizeof(Alumno));
    archivo.write((char*)&a2, sizeof(Alumno));
    archivo.write((char*)&a3, sizeof(Alumno));
    archivo.write((char*)&a4, sizeof(Alumno));
    archivo.write((char*)&a5, sizeof(Alumno));

    archivo.close();
    cout << "[INFO] Archivo generado correctamente.\n";
}

// -----------------
// BÚSQUEDA BINARIA 
// -----------------
int busquedaBinaria(RegistroIndice* base, int cantidad, int legajoBuscado) {

    int lo = 0;
    int hi = cantidad - 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        int leg = (*(base + mid)).legajo;

        if (leg == legajoBuscado)
            return mid;

        if (leg < legajoBuscado)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}


int main() {

    const char* ARCHIVO = "ALUMNOS.DAT";

    generarArchivo(ARCHIVO);

   
    fstream archivo(ARCHIVO, ios::binary | ios::in);
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo.\n";
        return 1;
    }

    archivo.seekg(0, ios::end);
    long bytes = archivo.tellg();
    int cantidad = bytes / sizeof(Alumno);

    archivo.seekg(0, ios::beg);

    cout << "\nRegistros encontrados: " << cantidad << "\n";

    
    RegistroIndice* indice = new RegistroIndice[cantidad];

    Alumno temp;
    for (int i = 0; i < cantidad; i++) {
        streampos posActual = archivo.tellg();

        archivo.read((char*)&temp, sizeof(Alumno));

        (*(indice + i)).legajo = temp.legajo;
        (*(indice + i)).posicion = posActual;
    }

    archivo.clear();
    cout << "\n--- BUSQUEDA DE ALUMNOS POR LEGAJO ---\n";
    int legajoBuscado;

    cout << "Ingrese legajo a buscar (0 para salir): ";
    while (cin >> legajoBuscado && legajoBuscado != 0) {

        int posIndice = busquedaBinaria(indice, cantidad, legajoBuscado);

        if (posIndice == -1) {
            cout << "[INFO] No existe ese legajo.\n\n";
        } else {
            // Recuperar posición del archivo
            streampos offset = (*(indice + posIndice)).posicion;

            archivo.seekg(offset);

            Alumno encontrado;
            archivo.read((char*)&encontrado, sizeof(Alumno));

            cout << "\n===== REGISTRO ENCONTRADO =====\n";
            cout << "Legajo:   " << encontrado.legajo << "\n";
            cout << "Nombre:   " << encontrado.nombre << "\n";
            cout << "Carrera:  " << encontrado.carrera << "\n";
            cout << "Promedio: " << encontrado.promedio << "\n";
            cout << "================================\n\n";
        }

        cout << "Ingrese otro legajo (0 para salir): ";
    }

    delete[] indice;
    archivo.close();

    return 0;
}
