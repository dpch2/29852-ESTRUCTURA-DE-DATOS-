#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura para almacenar información del alumno
struct Alumno {
    int legajo;
    char nombre[51];
    char apellido[51];
    char carrera[51];
    int anio;
};

// Estructura para el índice (legajo, posición en archivo)
struct Indice {
    int legajo;
    long posicion;
};

class SistemaAlumnos {
private:
    string nombreArchivo;
    vector<Indice> indice;
    
public:
    SistemaAlumnos(string archivo = "ALUMNOS.DAT") : nombreArchivo(archivo) {}
    
    // Crear archivo de ejemplo con datos de prueba
    void crearArchivoEjemplo() {
        ofstream archivo(nombreArchivo, ios::binary);
        
        if (!archivo) {
            cout << "Error al crear el archivo" << endl;
            return;
        }
        
        Alumno alumnos[] = {
            {1001, "Juan", "Perez", "Sistemas", 2},
            {1005, "Maria", "Gonzalez", "Industrial", 3},
            {1010, "Carlos", "Rodriguez", "Civil", 1},
            {1015, "Ana", "Martinez", "Sistemas", 4},
            {1020, "Luis", "Fernandez", "Mecanica", 2},
            {1025, "Sofia", "Lopez", "Sistemas", 3},
            {1030, "Diego", "Sanchez", "Electronica", 1},
            {1035, "Laura", "Ramirez", "Industrial", 2}
        };
        
        int numAlumnos = sizeof(alumnos) / sizeof(Alumno);
        
        for (int i = 0; i < numAlumnos; i++) {
            archivo.write(reinterpret_cast<char*>(&alumnos[i]), sizeof(Alumno));
        }
        
        archivo.close();
        cout << "\n=== CREACION DEL ARCHIVO ===" << endl;
        cout << "Archivo " << nombreArchivo << " creado exitosamente" << endl;
        cout << numAlumnos << " registros guardados" << endl;
        cout << "Tamanio del registro: " << sizeof(Alumno) << " bytes\n" << endl;
    }
    
    // Cargar índice en memoria desde el archivo
    bool cargarIndice() {
        ifstream archivo(nombreArchivo, ios::binary);
        
        if (!archivo) {
            cout << "Error: El archivo " << nombreArchivo << " no existe" << endl;
            return false;
        }
        
        indice.clear();
        Alumno alumno;
        long posicion = 0;
        
        while (archivo.read(reinterpret_cast<char*>(&alumno), sizeof(Alumno))) {
            Indice idx;
            idx.legajo = alumno.legajo;
            idx.posicion = posicion;
            indice.push_back(idx);
            posicion += sizeof(Alumno);
        }
        
        archivo.close();
        
        // Ordenar el índice por legajo (en caso de que no esté ordenado)
        sort(indice.begin(), indice.end(), [](const Indice& a, const Indice& b) {
            return a.legajo < b.legajo;
        });
        
        cout << "\n=== CARGA DEL INDICE ===" << endl;
        cout << "Indice cargado en memoria: " << indice.size() << " registros" << endl;
        if (!indice.empty()) {
            cout << "Rango de legajos: " << indice[0].legajo << " - " 
                 << indice[indice.size()-1].legajo << endl;
        }
        cout << endl;
        
        return true;
    }
    
    // Búsqueda binaria sobre el índice
    long busquedaBinaria(int legajoBuscado) {
        int izq = 0;
        int der = indice.size() - 1;
        int comparaciones = 0;
        
        cout << "\n=== BUSQUEDA BINARIA ===" << endl;
        cout << "Buscando legajo: " << legajoBuscado << endl;
        cout << "----------------------------------------" << endl;
        
        while (izq <= der) {
            comparaciones++;
            int medio = (izq + der) / 2;
            int legajoMedio = indice[medio].legajo;
            
            cout << "Comparacion " << comparaciones << ": ";
            cout << "indice[" << medio << "] = legajo " << legajoMedio;
            
            if (legajoMedio == legajoBuscado) {
                cout << " -> ENCONTRADO!" << endl;
                cout << "----------------------------------------" << endl;
                cout << "Total de comparaciones: " << comparaciones << endl;
                cout << "Posicion en archivo: " << indice[medio].posicion << " bytes" << endl;
                return indice[medio].posicion;
            } else if (legajoMedio < legajoBuscado) {
                cout << " (menor, buscar derecha)" << endl;
                izq = medio + 1;
            } else {
                cout << " (mayor, buscar izquierda)" << endl;
                der = medio - 1;
            }
        }
        
        cout << "----------------------------------------" << endl;
        cout << "NO ENCONTRADO despues de " << comparaciones << " comparaciones" << endl;
        return -1;
    }
    
    // Leer registro desde posición específica usando seek
    bool leerRegistro(long posicion, Alumno& alumno) {
        ifstream archivo(nombreArchivo, ios::binary);
        
        if (!archivo) {
            cout << "Error al abrir el archivo" << endl;
            return false;
        }
        
        // Usar seek para ir directamente a la posición
        archivo.seekg(posicion);
        archivo.read(reinterpret_cast<char*>(&alumno), sizeof(Alumno));
        
        archivo.close();
        return true;
    }
    
    // Buscar y mostrar información de un alumno
    void buscarAlumno(int legajo) {
        long posicion = busquedaBinaria(legajo);
        
        if (posicion == -1) {
            cout << "\nEl alumno con legajo " << legajo << " NO existe en el sistema\n" << endl;
            return;
        }
        
        Alumno alumno;
        if (leerRegistro(posicion, alumno)) {
            cout << "\n=== INFORMACION DEL ALUMNO ===" << endl;
            cout << "Legajo:   " << alumno.legajo << endl;
            cout << "Nombre:   " << alumno.nombre << endl;
            cout << "Apellido: " << alumno.apellido << endl;
            cout << "Carrera:  " << alumno.carrera << endl;
            cout << "Año:      " << alumno.anio << endl;
            cout << "==============================\n" << endl;
        }
    }
    
    // Mostrar todos los legajos del índice
    void mostrarIndice() {
        cout << "\n=== INDICE DE LEGAJOS ===" << endl;
        cout << "Posicion | Legajo | Offset en archivo" << endl;
        cout << "---------|--------|------------------" << endl;
        for (size_t i = 0; i < indice.size(); i++) {
            cout << setw(8) << i << " | " 
                 << setw(6) << indice[i].legajo << " | " 
                 << setw(10) << indice[i].posicion << " bytes" << endl;
        }
        cout << endl;
    }
};

int main() {
    SistemaAlumnos sistema;
    
    // 1. Crear archivo de ejemplo
    sistema.crearArchivoEjemplo();
    
    // 2. Cargar índice en memoria
    if (!sistema.cargarIndice()) {
        return 1;
    }
    
    // 3. Mostrar el índice cargado
    sistema.mostrarIndice();
    
    // 4. Realizar búsquedas de ejemplo
    cout << "\n********************************************" << endl;
    cout << "*      PRUEBAS DE BUSQUEDA BINARIA        *" << endl;
    cout << "********************************************\n" << endl;
    
    // Búsqueda exitosa
    sistema.buscarAlumno(1015);
    
    // Otra búsqueda exitosa
    sistema.buscarAlumno(1030);
    
    // Búsqueda fallida
    sistema.buscarAlumno(1999);
    
    // Búsqueda del primer elemento
    sistema.buscarAlumno(1001);
    
    // Búsqueda del último elemento
    sistema.buscarAlumno(1035);
    
    cout << "\n********************************************" << endl;
    cout << "*           VENTAJAS DEL SISTEMA          *" << endl;
    cout << "********************************************" << endl;
    cout << "1. Busqueda O(log n) - muy eficiente" << endl;
    cout << "2. Acceso directo con seek() - sin recorrer todo" << endl;
    cout << "3. Indice en memoria - rapido acceso" << endl;
    cout << "4. Archivo ordenado por clave primaria" << endl;
    cout << "********************************************\n" << endl;
    
    return 0;
}