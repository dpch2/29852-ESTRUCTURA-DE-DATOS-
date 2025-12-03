#include <iostream>
#include <string>
#include <vector>

// --- 1. Definición de la Estructura Persona ---
// Almacena los datos de una persona.
struct Persona {
    std::string nombre;
    std::string cedula;
    std::string telefono;
};

// --- 2. Implementación de la Tabla Hash con Punteros ---

// Nodo para la lista enlazada (encadenamiento separado)
template<typename K, typename V>
struct HashNode {
    K clave;
    V valor;
    HashNode* siguiente;

    // Constructor para facilitar la creación de nodos
    HashNode(const K& k, const V& v) : clave(k), valor(v), siguiente(nullptr) {}
};

// Clase TablaHash genérica
template<typename K, typename V>
class TablaHash {
private:
    HashNode<K, V>** tabla; // Array de punteros a HashNode
    int capacidad;          // Tamaño del array

    // Función hash para convertir una clave string a un índice
    int funcionHash(const std::string& clave) {
        unsigned long hash = 5381;
        for (char c : clave) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % capacidad;
    }

public:
    // Constructor: inicializa la tabla
    TablaHash(int cap = 10) : capacidad(cap) {
        tabla = new HashNode<K, V>*[capacidad];
        for (int i = 0; i < capacidad; ++i) {
            tabla[i] = nullptr;
        }
    }

    // Destructor: libera toda la memoria dinámica
    ~TablaHash() {
        for (int i = 0; i < capacidad; ++i) {
            HashNode<K, V>* entrada = tabla[i];
            while (entrada != nullptr) {
                HashNode<K, V>* prev = entrada;
                entrada = entrada->siguiente;
                delete prev;
            }
        }
        delete[] tabla;
    }

    // Inserta un par clave-valor en la tabla hash
    void insertar(const K& clave, const V& valor) {
        int indiceHash = funcionHash(clave);
        HashNode<K, V>* nuevoNodo = new HashNode<K, V>(clave, valor);
        
        // Si la cubeta está vacía, el nuevo nodo es el primero
        if (tabla[indiceHash] == nullptr) {
            tabla[indiceHash] = nuevoNodo;
        } else {
            // Si no, lo añadimos al principio de la lista (manejo de colisión)
            nuevoNodo->siguiente = tabla[indiceHash];
            tabla[indiceHash] = nuevoNodo;
        }
    }

    // Busca un valor por su clave. Devuelve un puntero al valor si se encuentra.
    V* buscar(const K& clave) {
        int indiceHash = funcionHash(clave);
        HashNode<K, V>* entrada = tabla[indiceHash];

        // Recorre la lista enlazada en la cubeta correspondiente
        while (entrada != nullptr) {
            if (entrada->clave == clave) {
                return &(entrada->valor); // Devuelve la dirección del valor
            }
            entrada = entrada->siguiente;
        }
        return nullptr; // No se encontró la clave
    }
};

// --- 3. Programa Principal ---

void mostrarPersona(const Persona& p) {
    std::cout << "\n--- Persona Encontrada ---\n";
    std::cout << "Nombre:   " << p.nombre << "\n";
    std::cout << "Cédula:   " << p.cedula << "\n";
    std::cout << "Teléfono: " << p.telefono << "\n";
    std::cout << "--------------------------\n";
}

int main() {
    const int NUM_PERSONAS = 9;
    Persona personas[NUM_PERSONAS];
    
    // Creamos dos tablas hash. El valor que guardan es el índice en el array 'personas'.
    // Usamos una capacidad ligeramente mayor que el número de elementos para reducir colisiones.
    TablaHash<std::string, int> tablaPorNombre(13);
    TablaHash<std::string, int> tablaPorCedula(13);

    std::cout << "==============================================\n";
    std::cout << "  INGRESO DE DATOS DE " << NUM_PERSONAS << " PERSONAS\n";
    std::cout << "==============================================\n";

    // Bucle para ingresar los datos de 9 personas
    for (int i = 0; i < NUM_PERSONAS; ++i) {
        std::cout << "\n--- Persona " << i + 1 << " ---\n";
        std::cout << "Ingrese nombre: ";
        std::getline(std::cin, personas[i].nombre);

        std::cout << "Ingrese cedula: ";
        std::getline(std::cin, personas[i].cedula);

        std::cout << "Ingrese telefono: ";
        std::getline(std::cin, personas[i].telefono);

        // Mapear los datos en las tablas hash
        tablaPorNombre.insertar(personas[i].nombre, i);
        tablaPorCedula.insertar(personas[i].cedula, i);
    }

    // Menú de búsqueda
    int opcion;
    do {
        std::cout << "\n==============================================\n";
        std::cout << "              MENU DE BUSQUEDA\n";
        std::cout << "==============================================\n";
        std::cout << "1. Buscar por Nombre\n";
        std::cout << "2. Buscar por Cedula\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;
        std::cin.ignore(); 

        if (opcion == 1) {
            std::string nombreBusqueda;
            std::cout << "Ingrese el nombre a buscar: ";
            std::getline(std::cin, nombreBusqueda);

            int* indice = tablaPorNombre.buscar(nombreBusqueda);
            if (indice != nullptr) {
                mostrarPersona(personas[*indice]);
            } else {
                std::cout << "\n[ERROR] Persona con nombre '" << nombreBusqueda << "' no encontrada.\n";
            }
        } else if (opcion == 2) {
            std::string cedulaBusqueda;
            std::cout << "Ingrese la cedula a buscar: ";
            std::getline(std::cin, cedulaBusqueda);

            int* indice = tablaPorCedula.buscar(cedulaBusqueda);
            if (indice != nullptr) {
                mostrarPersona(personas[*indice]);
            } else {
                std::cout << "\n[ERROR] Persona con cedula '" << cedulaBusqueda << "' no encontrada.\n";
            }
        }

    } while (opcion != 0);

    std::cout << "\nPrograma finalizado.\n";

    return 0;
}
