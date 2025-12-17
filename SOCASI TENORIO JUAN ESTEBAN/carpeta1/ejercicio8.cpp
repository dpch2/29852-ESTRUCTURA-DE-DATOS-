#include <iostream>
#include <string>
// No se usan <vector> ni <list>

// 1. Estructura para el Nodo de nuestra Lista Enlazada
struct Nodo {
    int clave;
    Nodo* siguiente;

    Nodo(int val) : clave(val), siguiente(nullptr) {}
};

// Definimos el tamaño de nuestra tabla hash
const int TAMANO_TABLA = 10;

class TablaHash {
private:
    // El arreglo de punteros a Nodo (C-style array).
    Nodo* tabla[TAMANO_TABLA];

    /**
     * @brief La función hash simple.
     */
    int funcionHash(int clave) const {
        return clave % TAMANO_TABLA;
    }

public:
    // Constructor
    TablaHash() {
        for (int i = 0; i < TAMANO_TABLA; ++i) {
            tabla[i] = nullptr;
        }
    }
    
    // Destructor (MUY IMPORTANTE para liberar la memoria)
    ~TablaHash() {
        for (int i = 0; i < TAMANO_TABLA; ++i) {
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                Nodo* temp = actual;
                actual = actual->siguiente;
                delete temp;
            }
        }
    }

    // --- SOLUCIÓN TAREA 1: IMPLEMENTAR INSERCIÓN ---
    void insertar(int clave) {
        int indice = funcionHash(clave);
        
        // Creamos el nuevo nodo
        Nodo* nuevoNodo = new Nodo(clave);
        
        // 1. El 'siguiente' del nuevo nodo apunta a la cabeza actual.
        // nuevoNodo->siguiente = tabla[indice];
        nuevoNodo->siguiente = tabla[indice];
        
        // 2. La cabeza del arreglo (tabla[indice]) debe ser ahora el nuevo nodo.
        // tabla[indice] = nuevoNodo;
        tabla[indice] = nuevoNodo;
    }

    // --- SOLUCIÓN TAREA 2: IMPLEMENTAR BÚSQUEDA ---
    bool buscar(int clave) {
        int indice = funcionHash(clave);
        
        Nodo* actual = tabla[indice];

        while (actual != nullptr) {
            if (actual->clave == clave) {
                // Clave encontrada
                // return true;
                return true; 
            }
            // Avanzar al siguiente nodo
            // actual = actual->siguiente;
            actual = actual->siguiente;
        }
        
        return false; 
    }
    
    // Función de ayuda para visualizar la tabla (sin cambios)
    void mostrarTabla() const {
        std::cout << "\n--- Estado de la Tabla Hash ---" << std::endl;
        for (int i = 0; i < TAMANO_TABLA; ++i) {
            std::cout << "Indice " << i << ": ";
            Nodo* actual = tabla[i];
            while (actual != nullptr) {
                std::cout << actual->clave << " -> ";
                actual = actual->siguiente;
            }
            std::cout << "NULL" << std::endl;
        }
        std::cout << "------------------------------" << std::endl;
    }
};

int main() {
    TablaHash ht;

    // Insertar elementos
    std::cout << "Insertando: 12, 22, 5, 32, 11..." << std::endl;
    ht.insertar(12); // Indice 2
    ht.insertar(22); // Indice 2 (Colisión)
    ht.insertar(5);  // Indice 5
    ht.insertar(32); // Indice 2 (Colisión)
    ht.insertar(11); // Indice 1

    ht.mostrarTabla();

    // Buscar elementos
    std::cout << "\nBuscando clave 5 (Esperado: Encontrado)... ";
    std::cout << (ht.buscar(5) ? "Encontrado." : "No encontrado.") << std::endl;

    std::cout << "Buscando clave 32 (Esperado: Encontrado)... ";
    std::cout << (ht.buscar(32) ? "Encontrado." : "No encontrado.") << std::endl;

    std::cout << "Buscando clave 100 (Esperado: No encontrado)... ";
    std::cout << (ht.buscar(100) ? "Encontrado." : "No encontrado.") << std::endl;

    return 0;
}