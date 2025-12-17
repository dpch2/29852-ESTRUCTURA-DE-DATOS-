#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Nombre del archivo de datos
const char* NOMBRE_ARCHIVO = "ALUMNOS.DAT";

// Estructura del registro de alumno (debe ser de tamaño fijo para el seek)
struct Alumno {
    int legajo;
    char nombre[30]; // Usamos un array de tamaño fijo
    char apellido[30];
    // Añadir más campos si es necesario
};

// Estructura del índice en memoria
struct Indice {
    int legajo;
    long offset; // Posición de bytes en el archivo
};

// ===================================================================
vector<Indice> generar_archivo_y_cargar_indice() {
    vector<Indice> indice_memoria;
    
    // Abrir el archivo en modo binario y de escritura (ios::out | ios::binary)
    ofstream archivo(NOMBRE_ARCHIVO, ios::out | ios::binary);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << NOMBRE_ARCHIVO << endl;
        return indice_memoria;
    }

    // Datos de ejemplo ORDENADOS por legajo (CRUCIAL para la búsqueda binaria)
    vector<Alumno> datos = {
        {1001, "Ana", "Gomez"},
        {1005, "Luis", "Perez"},
        {1010, "Marta", "Lopez"},
        {1015, "Juan", "Diaz"},
        {1022, "Sofia", "Ramirez"}
    };

    long offset_actual = 0; // El offset comienza en 0

    for (const auto& alumno : datos) {
        // 1. Escribir el registro completo en el archivo binario
        archivo.write((char*)&alumno, sizeof(Alumno));

        // 2. Crear y guardar la entrada del índice en memoria
        Indice entrada = {alumno.legajo, offset_actual};
        indice_memoria.push_back(entrada);

        // Actualizar el offset para el siguiente registro
        offset_actual += sizeof(Alumno);
    }

    archivo.close();
    cout << "✅ Archivo " << NOMBRE_ARCHIVO << " generado con éxito." << endl;
    cout << "✅ Índice cargado en memoria (" << indice_memoria.size() << " entradas)." << endl;
    return indice_memoria;
}

// ===================================================================
void buscar_alumno(const vector<Indice>& indice, int legajo_a_buscar) {
    if (indice.empty()) {
        cerr << "Error: El índice está vacío." << endl;
        return;
    }

    // --- Parte 3a: Búsqueda Binaria sobre el Índice (O(log n)) ---
    
    // Usamos std::lower_bound para encontrar la primera entrada cuyo legajo
    // no sea menor que el legajo_a_buscar.
    auto it = lower_bound(indice.begin(), indice.end(), legajo_a_buscar, 
        [](const Indice& a, int val) {
            return a.legajo < val;
        }
    );

    // Verificar si se encontró el legajo
    if (it != indice.end() && it->legajo == legajo_a_buscar) {
        
        // Legajo encontrado. Obtenemos el offset.
        long offset_encontrado = it->offset;
        cout << "\n🌟 Legajo " << legajo_a_buscar << " encontrado en el índice." << endl;
        cout << "   -> Offset en el archivo: " << offset_encontrado << " bytes." << endl;

        // --- Parte 3b: Acceso Directo (seek) al Archivo ---

        // Abrir el archivo en modo binario y de lectura
        ifstream archivo_lectura(NOMBRE_ARCHIVO, ios::in | ios::binary);

        if (!archivo_lectura.is_open()) {
            cerr << "Error: No se pudo abrir el archivo para lectura." << endl;
            return;
        }

        // Posicionar el puntero de lectura (seek) al offset encontrado
        archivo_lectura.seekg(offset_encontrado);

        // Leer el registro completo en la estructura Alumno
        Alumno alumno_recuperado;
        archivo_lectura.read((char*)&alumno_recuperado, sizeof(Alumno));
        
        archivo_lectura.close();

        // Mostrar el resultado
        cout << "\n--- Registro Recuperado (Seek) ---" << endl;
        cout << "Legajo: " << alumno_recuperado.legajo << endl;
        cout << "Nombre: " << alumno_recuperado.nombre << endl;
        cout << "Apellido: " << alumno_recuperado.apellido << endl;
        cout << "---------------------------------" << endl;

    } else {
        // Legajo no encontrado
        cout << "\n❌ Legajo " << legajo_a_buscar << " no encontrado en el índice." << endl;
    }
}
// ===================================================================
int main() {
    // 1. Generar el archivo y cargar el índice
    vector<Indice> indice = generar_archivo_y_cargar_indice();

    if (indice.empty()) {
        return 1;
    }

    // 2. Probar búsquedas
    int legajo1 = 1010; // Legajo que existe
    int legajo2 = 9999; // Legajo que NO existe

    cout << "\n==========================================";
    cout << "\nBUSCANDO LEGAJO EXISTENTE: " << legajo1;
    buscar_alumno(indice, legajo1);
    
    cout << "\n==========================================";
    cout << "\nBUSCANDO LEGAJO INEXISTENTE: " << legajo2;
    buscar_alumno(indice, legajo2);
    cout << "\n==========================================" << endl;

    return 0;
}