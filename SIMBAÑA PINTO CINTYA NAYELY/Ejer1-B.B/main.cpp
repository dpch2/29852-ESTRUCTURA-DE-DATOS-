#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Alumno {
    int legajo;          // 4 bytes
    char nombre[50];     // 50 bytes
    float promedio;      // 4 bytes
}; 
// Tamaño total aprox: 58 bytes


struct Indice {
    int legajo;          // Clave de búsqueda
    long posicionByte;   // Coordenada exacta en el archivo
};

// Constante para definir el tamaño máximo del arreglo estático
const int MAX_ALUMNOS = 100; 

// --- GENERADOR DE DATOS (Para que el código funcione) ---
void crearArchivoPrueba() {
    ofstream arch("ALUMNOS.DAT", ios::binary);
    // Datos DEBEN estar ordenados por legajo para que la búsqueda binaria funcione
    Alumno datos[] = {
        {100, "Ana", 9.5}, {205, "Beto", 7.2}, {310, "Carla", 8.8},
        {450, "Daniel", 6.5}, {501, "Elena", 9.0}, {680, "Fabio", 5.5},
        {720, "Gaby", 8.1}, {890, "Hector", 7.9}, {905, "Ines", 9.2},
        {999, "Juan", 10.0}
    };
    // Escribimos todo el bloque
    arch.write((char*)&datos, sizeof(datos));
    arch.close();
}

// --- PROGRAMA PRINCIPAL ---

int main() {
    // Paso 0: Crear el archivo ficticio
    crearArchivoPrueba();

    // VARIABLES MATEMÁTICAS Y DE CONTROL
    Indice tablaEnMemoria[MAX_ALUMNOS]; // Arreglo estático (Sin vector)
    int cantidadReal = 0;               // Contador 'n' (cardinalidad del conjunto)
    
    ifstream archivoLectura;
    Alumno temp;

    // ---------------------------------------------------------
    // FASE 1: CARGA E INDEXACIÓN (Extracción de Datos)
    // ---------------------------------------------------------
    archivoLectura.open("ALUMNOS.DAT", ios::binary);
    if (!archivoLectura.is_open()) {
        cout << "Error al abrir archivo";
        return 1;
    }

    // Leemos el archivo registro por registro
    while (archivoLectura.read((char*)&temp, sizeof(Alumno))) {
        // VALIDACIÓN DE SEGURIDAD (Evitar desbordamiento de memoria)
        if (cantidadReal >= MAX_ALUMNOS) {
            cout << "Memoria llena. No se pueden indexar mas registros." << endl;
            break;
        }

        // MATEMÁTICA DEL OFFSET:
        // Necesitamos saber dónde EMPEZABA este registro que acabamos de leer.
        // tellg() nos da la posición ACTUAL (al final del registro).
        // Restamos el tamaño del registro para obtener el inicio.
        long posicionActual = (long)archivoLectura.tellg() - sizeof(Alumno);

        // Guardamos en nuestro arreglo (RAM)
        tablaEnMemoria[cantidadReal].legajo = temp.legajo;
        tablaEnMemoria[cantidadReal].posicionByte = posicionActual;
        
        cantidadReal++; // Incrementamos n
    }
    
    // Aquí el archivo queda abierto, o podemos cerrarlo y reabrirlo. 
    // Lo dejaremos abierto pero limpiaremos los 'flags' para poder usar seekg después.
    archivoLectura.clear(); 

    cout << "Indexacion completada. " << cantidadReal << " alumnos en memoria RAM.\n";

    // ---------------------------------------------------------
    // FASE 2: BÚSQUEDA BINARIA (Lógica Matemática)
    // ---------------------------------------------------------
    int legajoBuscado;
    cout << "Ingrese legajo a buscar: ";
    cin >> legajoBuscado;

    int inicio = 0;
    int fin = cantidadReal - 1;
    int posicionEncontrada = -1; // -1 representa el conjunto vacío (no encontrado)

    // Algoritmo de Bisección
    while (inicio <= fin) {
        int centro = (inicio + fin) / 2; // División entera

        if (tablaEnMemoria[centro].legajo == legajoBuscado) {
            posicionEncontrada = centro; // ¡Encontrado!
            break; // Rompemos el ciclo
        }
        else if (legajoBuscado < tablaEnMemoria[centro].legajo) {
            // El valor está en el subconjunto inferior (Izquierda)
            fin = centro - 1;
        }
        else {
            // El valor está en el subconjunto superior (Derecha)
            inicio = centro + 1;
        }
    }

    // ---------------------------------------------------------
    // FASE 3: RECUPERACIÓN DIRECTA (Acceso a Disco)
    // ---------------------------------------------------------
    if (posicionEncontrada != -1) {
        // Paso A: Extraer la coordenada física (byte) del índice
        long byteOffset = tablaEnMemoria[posicionEncontrada].posicionByte;

        // Paso B: Mover el cabezal del disco (Seek)
        // seekg(desplazamiento, desde_donde) -> Mover a 'byteOffset' desde el inicio (beg)
        archivoLectura.seekg(byteOffset, ios::beg);

        // Paso C: Leer solo ese registro
        Alumno alumnoFinal;
        archivoLectura.read((char*)&alumnoFinal, sizeof(Alumno));

        cout << "\n--- RESULTADO ---" << endl;
        cout << "Legajo:   " << alumnoFinal.legajo << endl;
        cout << "Nombre:   " << alumnoFinal.nombre << endl;
        cout << "Promedio: " << alumnoFinal.promedio << endl;
        cout << "Ubicado matematicamente en el byte: " << byteOffset << endl;
    } else {
        cout << "El legajo no existe en la base de datos." << endl;
    }

    archivoLectura.close();
    return 0;
}