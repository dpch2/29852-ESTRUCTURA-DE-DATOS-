#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

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


void generarArchivoDePrueba(const char* nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::binary);
    if (!archivo) {
        cerr << "Error al crear el archivo de prueba." << endl;
        return;
    }

    Alumno alumnos[] = {
        {101, "Ana Garcia", "Ingenieria", 8.5},
        {105, "Luis Perez", "Arquitectura", 7.2},
        {204, "Maria Lopez", "Medicina", 9.1},
        {300, "Carlos Ruiz", "Derecho", 6.8},
        {450, "Sofia Mendieta", "Sistemas", 9.5}
    };

    for (const auto& alu : alumnos) {
        archivo.write(reinterpret_cast<const char*>(&alu), sizeof(Alumno));
    }
    archivo.close();
    cout << "[INFO] Archivo " << nombreArchivo << " generado correctamente con datos ordenados." << endl;
}


int busquedaBinaria(const vector<RegistroIndice>& indice, int legajoBuscado) {
    int izquierda = 0;
    int derecha = indice.size() - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (indice[medio].legajo == legajoBuscado) {
            return medio; 
        }
        if (indice[medio].legajo < legajoBuscado) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1; 
}



int main() {
    const char* NOMBRE_ARCHIVO = "ALUMNOS.DAT";
    generarArchivoDePrueba(NOMBRE_ARCHIVO);

    // 2. Abrir el archivo para lectura
    ifstream archivo(NOMBRE_ARCHIVO, ios::binary);
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << NOMBRE_ARCHIVO << endl;
        return 1;
    }

    // 3. Cargar el índice en Memoria Principal (RAM)
    vector<RegistroIndice> indiceMemoria;
    Alumno temp;
    
    while (true) {
        streampos posActual = archivo.tellg(); 
        
        if (!archivo.read(reinterpret_cast<char*>(&temp), sizeof(Alumno))) {
            break; 
        }

        RegistroIndice reg;
        reg.legajo = temp.legajo;
        reg.posicion = posActual;
        indiceMemoria.push_back(reg);
    }
    
    // Limpiamos flags del archivo para usarlo luego
    archivo.clear(); 

    cout << "\n--- SISTEMA DE CONSULTA DE ALUMNOS ---" << endl;
    cout << "Indice cargado en memoria. Total registros: " << indiceMemoria.size() << endl;

    // 5. Interacción con el usuario
    int legajoBusqueda;
    cout << "Ingrese el legajo a buscar (0 para salir): ";
    while (cin >> legajoBusqueda && legajoBusqueda != 0) {
        
        // A. Búsqueda Binaria sobre el índice (RÁPIDO - En RAM)
        int indexPos = busquedaBinaria(indiceMemoria, legajoBusqueda);

        if (indexPos != -1) {
            
            streampos byteOffset = indiceMemoria[indexPos].posicion;
            
            archivo.seekg(byteOffset); 
            
            Alumno alumnoEncontrado;
            archivo.read(reinterpret_cast<char*>(&alumnoEncontrado), sizeof(Alumno));

            cout << "\n[RESULTADO] Registro Encontrado:" << endl;
            cout << "-----------------------------" << endl;
            cout << "Legajo:   " << alumnoEncontrado.legajo << endl;
            cout << "Nombre:   " << alumnoEncontrado.nombre << endl;
            cout << "Carrera:  " << alumnoEncontrado.carrera << endl;
            cout << "Promedio: " << alumnoEncontrado.promedio << endl;
            cout << "-----------------------------" << endl;
        } else {
            cout << "\n[INFO] El legajo " << legajoBusqueda << " no existe en la base de datos." << endl;
        }

        cout << "\nIngrese otro legajo a buscar (0 para salir): ";
    }

    archivo.close();
    return 0;
}