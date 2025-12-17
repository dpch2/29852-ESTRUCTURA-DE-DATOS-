#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class BusquedaBinariaVariacion {
private:
    vector<int> arreglo;
    int izq, der;  // Variables de intervalo
    int comparacionesBinarias;
    int comparacionesIntervalo;
    
public:
    BusquedaBinariaVariacion(vector<int> arr) : arreglo(arr) {
        izq = 0;
        der = arreglo.size() - 1;
        comparacionesBinarias = 0;
        comparacionesIntervalo = 0;
    }
    
    // Función recursiva que hace UNA comparación binaria por invocación
    bool buscar(int K) {
        cout << "\n--- Invocacion ---" << endl;
        cout << "Intervalo: [" << izq << ", " << der << "]";
        
        // Comparación de variables de intervalo (NO es comparación binaria)
        comparacionesIntervalo++;
        if (izq > der) {
            cout << " -> Intervalo invalido (izq > der)" << endl;
            cout << "Resultado: NO ENCONTRADO" << endl;
            return false;
        }
        
        // Otra comparación de intervalo
        comparacionesIntervalo++;
        if (izq == der) {
            // Cuando el intervalo tiene un solo elemento,
            // hacemos la comparación de IGUALDAD (==)
            cout << " -> Un solo elemento" << endl;
            int medio = izq;
            cout << "Comparacion BINARIA " << ++comparacionesBinarias 
                 << ": arr[" << medio << "]=" << arreglo[medio] 
                 << " == " << K << "? ";
            
            // ÚNICA comparación binaria de esta invocación
            if (arreglo[medio] == K) {
                cout << "SI" << endl;
                cout << "Resultado: ENCONTRADO en posicion " << medio << endl;
                return true;
            } else {
                cout << "NO" << endl;
                cout << "Resultado: NO ENCONTRADO" << endl;
                return false;
            }
        }
        
        // Calcular punto medio
        int medio = (izq + der) / 2;
        cout << " -> Punto medio: " << medio << endl;
        cout << "Comparacion BINARIA " << ++comparacionesBinarias 
             << ": arr[" << medio << "]=" << arreglo[medio] 
             << " < " << K << "? ";
        
        // ÚNICA comparación binaria de esta invocación (usando <)
        if (arreglo[medio] < K) {
            cout << "SI (buscar derecha)" << endl;
            // Ajustar variable de intervalo
            izq = medio + 1;
            return buscar(K);  // Llamada recursiva
        } else {
            cout << "NO (buscar izquierda o igual)" << endl;
            // Ajustar variable de intervalo
            der = medio;
            return buscar(K);  // Llamada recursiva
        }
    }
    
    void mostrarEstadisticas() {
        cout << "\n========== ESTADISTICAS ==========" << endl;
        cout << "Comparaciones BINARIAS (arr[i] con K): " << comparacionesBinarias << endl;
        cout << "Comparaciones de INTERVALO (izq, der): " << comparacionesIntervalo << endl;
        cout << "==================================\n" << endl;
    }
    
    void reiniciar() {
        izq = 0;
        der = arreglo.size() - 1;
        comparacionesBinarias = 0;
        comparacionesIntervalo = 0;
    }
};

void mostrarArreglo(const vector<int>& arr) {
    cout << "Arreglo: [";
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i < arr.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "\n+========================================================+" << endl;
    cout << "|   BUSQUEDA BINARIA - VARIACION (Algoritmo 1.4)       |" << endl;
    cout << "|   Una comparacion binaria por invocacion              |" << endl;
    cout << "+========================================================+\n" << endl;
    
    // Arreglo de prueba ordenado
    vector<int> arreglo = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    
    mostrarArreglo(arreglo);
    cout << "\nCARACTERISTICAS DEL ALGORITMO:" << endl;
    cout << "1. Solo UNA comparacion binaria (arr[i] con K) por llamada" << endl;
    cout << "2. Se pueden hacer comparaciones de variables de intervalo (izq, der)" << endl;
    cout << "3. La comparacion de igualdad (==) se usa cuando izq == der\n" << endl;
    
    BusquedaBinariaVariacion buscador(arreglo);
    
    // Prueba 1: Buscar elemento que existe (en el medio)
    cout << "\n" << string(60, '=') << endl;
    cout << "PRUEBA 1: Buscar K = 23 (elemento que EXISTE)" << endl;
    cout << string(60, '=') << endl;
    buscador.reiniciar();
    bool resultado1 = buscador.buscar(23);
    buscador.mostrarEstadisticas();
    
    // Prueba 2: Buscar elemento que existe (al inicio)
    cout << "\n" << string(60, '=') << endl;
    cout << "PRUEBA 2: Buscar K = 2 (primer elemento)" << endl;
    cout << string(60, '=') << endl;
    buscador.reiniciar();
    bool resultado2 = buscador.buscar(2);
    buscador.mostrarEstadisticas();
    
    // Prueba 3: Buscar elemento que existe (al final)
    cout << "\n" << string(60, '=') << endl;
    cout << "PRUEBA 3: Buscar K = 78 (ultimo elemento)" << endl;
    cout << string(60, '=') << endl;
    buscador.reiniciar();
    bool resultado3 = buscador.buscar(78);
    buscador.mostrarEstadisticas();
    
    // Prueba 4: Buscar elemento que NO existe
    cout << "\n" << string(60, '=') << endl;
    cout << "PRUEBA 4: Buscar K = 50 (elemento que NO EXISTE)" << endl;
    cout << string(60, '=') << endl;
    buscador.reiniciar();
    bool resultado4 = buscador.buscar(50);
    buscador.mostrarEstadisticas();
    
    // Prueba 5: Buscar elemento menor que todos
    cout << "\n" << string(60, '=') << endl;
    cout << "PRUEBA 5: Buscar K = 1 (menor que todos)" << endl;
    cout << string(60, '=') << endl;
    buscador.reiniciar();
    bool resultado5 = buscador.buscar(1);
    buscador.mostrarEstadisticas();
    
    // Análisis de corrección
    cout << "\n+========================================================+" << endl;
    cout << "|              ANALISIS DE CORRECCION                   |" << endl;
    cout << "+========================================================+\n" << endl;
    
    cout << "PREGUNTA: ¿Cuando debe ser de igualdad (==) la unica comparacion?" << endl;
    cout << "\nRESPUESTA:" << endl;
    cout << "La comparacion de igualdad (==) debe usarse cuando:" << endl;
    cout << "  -> izq == der (el intervalo tiene un SOLO elemento)" << endl;
    cout << "\nRAZONAMIENTO:" << endl;
    cout << "1. Mientras izq < der, usamos '<' para dividir el espacio" << endl;
    cout << "2. Cuando izq == der, solo queda un elemento por verificar" << endl;
    cout << "3. En ese momento, hacemos la comparacion '==' para confirmar" << endl;
    cout << "4. Esto garantiza encontrar el elemento si existe" << endl;
    
    cout << "\n+========================================================+" << endl;
    cout << "|                    VENTAJAS                           |" << endl;
    cout << "+========================================================+\n" << endl;
    cout << "+ Una sola comparacion binaria por invocacion" << endl;
    cout << "+ Las comparaciones de intervalo no cuentan como binarias" << endl;
    cout << "+ Mismo orden de complejidad O(log n)" << endl;
    cout << "+ Facilita el analisis de comparaciones" << endl;
    
    return 0;
}