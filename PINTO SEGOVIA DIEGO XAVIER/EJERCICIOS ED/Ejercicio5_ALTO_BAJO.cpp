#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

// Clase que implementa el algoritmo de búsqueda binaria del Ejemplo 10.6
class BusquedaBinaria {
private:
    int BAJO, CENTRAL, ALTO;
    int comparaciones;
    
    // Mostrar estado actual del algoritmo
    void mostrarEstado(int iteracion) {
        cout << "  Iteracion " << setw(2) << iteracion << " | ";
        cout << "BAJO=" << setw(2) << BAJO << " | ";
        cout << "CENTRAL=" << setw(2) << CENTRAL << " | ";
        cout << "ALTO=" << setw(2) << ALTO << endl;
    }
    
public:
    BusquedaBinaria() : BAJO(0), CENTRAL(0), ALTO(0), comparaciones(0) {}
    
    // Búsqueda binaria para arreglos numéricos
    int buscar(vector<int>& X, int N, int K) {
        cout << "\n>>> Buscando K = " << K << " en arreglo numerico <<<\n" << endl;
        
        // Inicializar variables
        BAJO = 0;      // En C++ los índices empiezan en 0
        ALTO = N - 1;
        CENTRAL = (BAJO + ALTO) / 2;
        comparaciones = 0;
        int iteracion = 0;
        
        cout << "Estado inicial:" << endl;
        mostrarEstado(iteracion);
        cout << "\n" << string(50, '-') << endl;
        
        // Bucle principal
        while (BAJO <= ALTO && X[CENTRAL] != K) {
            iteracion++;
            comparaciones++;
            
            cout << "\nIteracion " << iteracion << ":" << endl;
            cout << "  Comparando X[" << CENTRAL << "]=" << X[CENTRAL] 
                 << " con K=" << K << endl;
            
            if (X[CENTRAL] < K) {
                cout << "  X[CENTRAL] < K -> Buscar en mitad DERECHA" << endl;
                BAJO = CENTRAL + 1;
            } else {
                cout << "  X[CENTRAL] > K -> Buscar en mitad IZQUIERDA" << endl;
                ALTO = CENTRAL - 1;
            }
            
            CENTRAL = (BAJO + ALTO) / 2;
            mostrarEstado(iteracion);
        }
        
        cout << "\n" << string(50, '-') << endl;
        
        // Verificar resultado
        if (BAJO <= ALTO && X[CENTRAL] == K) {
            cout << "\n+ Valor encontrado en posicion: " << CENTRAL << endl;
            cout << "  Comparaciones realizadas: " << comparaciones << endl;
            return CENTRAL;
        } else {
            cout << "\n- Valor no encontrado" << endl;
            cout << "  Comparaciones realizadas: " << comparaciones << endl;
            return -1;
        }
    }
    
    // Búsqueda binaria para arreglos de caracteres (strings)
    int buscar(vector<string>& X, int N, string K) {
        cout << "\n>>> Buscando K = \"" << K << "\" en arreglo de caracteres <<<\n" << endl;
        
        // Inicializar variables
        BAJO = 0;
        ALTO = N - 1;
        CENTRAL = (BAJO + ALTO) / 2;
        comparaciones = 0;
        int iteracion = 0;
        
        cout << "Estado inicial:" << endl;
        mostrarEstado(iteracion);
        cout << "\n" << string(50, '-') << endl;
        
        // Bucle principal
        while (BAJO <= ALTO && X[CENTRAL] != K) {
            iteracion++;
            comparaciones++;
            
            cout << "\nIteracion " << iteracion << ":" << endl;
            cout << "  Comparando X[" << CENTRAL << "]=\"" << X[CENTRAL] 
                 << "\" con K=\"" << K << "\"" << endl;
            
            if (X[CENTRAL] < K) {
                cout << "  X[CENTRAL] < K -> Buscar en mitad DERECHA" << endl;
                BAJO = CENTRAL + 1;
            } else {
                cout << "  X[CENTRAL] > K -> Buscar en mitad IZQUIERDA" << endl;
                ALTO = CENTRAL - 1;
            }
            
            CENTRAL = (BAJO + ALTO) / 2;
            mostrarEstado(iteracion);
        }
        
        cout << "\n" << string(50, '-') << endl;
        
        // Verificar resultado
        if (BAJO <= ALTO && X[CENTRAL] == K) {
            cout << "\n+ Valor encontrado en posicion: " << CENTRAL << endl;
            cout << "  Comparaciones realizadas: " << comparaciones << endl;
            return CENTRAL;
        } else {
            cout << "\n- Valor no encontrado" << endl;
            cout << "  Comparaciones realizadas: " << comparaciones << endl;
            return -1;
        }
    }
};

// Función auxiliar para mostrar un arreglo numérico
void mostrarArregloNumerico(const vector<int>& arr) {
    cout << "Arreglo: [";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
    cout << "Indices:  ";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << i;
        if (i < 10) cout << "   ";
        else cout << "  ";
    }
    cout << endl;
}

// Función auxiliar para mostrar un arreglo de strings
void mostrarArregloStrings(const vector<string>& arr) {
    cout << "Arreglo: [";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << "\"" << arr[i] << "\"";
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "\n+==========================================================+" << endl;
    cout << "|        ALGORITMO DE BUSQUEDA BINARIA (Ejemplo 10.6)     |" << endl;
    cout << "|   Busca elemento K en lista ordenada de N elementos     |" << endl;
    cout << "+=========================================================+\n" << endl;
    
    BusquedaBinaria buscador;
    
    // ============================================================
    // PARTE 1: BÚSQUEDA EN ARREGLO NUMÉRICO
    // ============================================================
    cout << "\n" << string(60, '=') << endl;
    cout << "PARTE 1: BUSQUEDA EN ARREGLO NUMERICO (ORDENADO)" << endl;
    cout << string(60, '=') << endl;
    
    vector<int> numerosOrdenados = {3, 7, 12, 18, 23, 29, 35, 41, 48, 56, 63, 71, 85, 92, 100};
    int N_num = numerosOrdenados.size();
    
    mostrarArregloNumerico(numerosOrdenados);
    
    // Prueba 1: Elemento que existe (en el medio)
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 1: Elemento que EXISTE (medio)" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(numerosOrdenados, N_num, 41);
    
    // Prueba 2: Elemento que existe (al inicio)
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 2: Elemento que EXISTE (inicio)" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(numerosOrdenados, N_num, 3);
    
    // Prueba 3: Elemento que existe (al final)
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 3: Elemento que EXISTE (final)" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(numerosOrdenados, N_num, 100);
    
    // Prueba 4: Elemento que NO existe
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 4: Elemento que NO EXISTE" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(numerosOrdenados, N_num, 50);
    
    // ============================================================
    // PARTE 2: BÚSQUEDA EN ARREGLO DE CARACTERES (STRINGS)
    // ============================================================
    cout << "\n\n" << string(60, '=') << endl;
    cout << "PARTE 2: BUSQUEDA EN ARREGLO DE CARACTERES (ORDEN ALFABETICO)" << endl;
    cout << string(60, '=') << endl;
    
    vector<string> palabrasOrdenadas = {
        "algoritmo", "arreglo", "busqueda", "central", "dato",
        "estructura", "funcion", "indice", "ordenar", "programa",
        "vector", "while"
    };
    int N_str = palabrasOrdenadas.size();
    
    mostrarArregloStrings(palabrasOrdenadas);
    
    // Prueba 5: Palabra que existe
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 5: Palabra que EXISTE" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(palabrasOrdenadas, N_str, "funcion");
    
    // Prueba 6: Palabra que NO existe
    cout << "\n" << string(60, '*') << endl;
    cout << "PRUEBA 6: Palabra que NO EXISTE" << endl;
    cout << string(60, '*') << endl;
    buscador.buscar(palabrasOrdenadas, N_str, "tabla");
    
    // ============================================================
    // RESUMEN Y ANÁLISIS
    // ============================================================
    cout << "\n\n+==========================================================+" << endl;
    cout << "|                    ANALISIS DEL ALGORITMO                |" << endl;
    cout << "+=========================================================+\n" << endl;
    
    cout << "CARACTERISTICAS:" << endl;
    cout << "  * Funciona con datos numericos Y caracteres" << endl;
    cout << "  * Requisito: el arreglo DEBE estar ordenado" << endl;
    cout << "  * Variables: BAJO, CENTRAL, ALTO" << endl;
    cout << "  * Complejidad temporal: O(log n)" << endl;
    cout << "  * Complejidad espacial: O(1)" << endl;
    
    cout << "\nVENTAJAS:" << endl;
    cout << "  + Muy eficiente para grandes conjuntos de datos" << endl;
    cout << "  + Para 1,000,000 elementos: max ~20 comparaciones" << endl;
    cout << "  + Para 1,000,000,000 elementos: max ~30 comparaciones" << endl;
    cout << "  + Implementacion simple y elegante" << endl;
    
    cout << "\nDESVENTAJAS:" << endl;
    cout << "  - Requiere que los datos esten ordenados" << endl;
    cout << "  - No es eficiente para arreglos pequenos (< 10 elementos)" << endl;
    
    cout << "\nCOMPARACION CON BUSQUEDA SECUENCIAL:" << endl;
    cout << "  * Secuencial: O(n) - busca elemento por elemento" << endl;
    cout << "  * Binaria: O(log n) - divide el espacio a la mitad" << endl;
    cout << "  * Para N=1000: Secuencial=~500, Binaria=~10" << endl;
    
    return 0;
}