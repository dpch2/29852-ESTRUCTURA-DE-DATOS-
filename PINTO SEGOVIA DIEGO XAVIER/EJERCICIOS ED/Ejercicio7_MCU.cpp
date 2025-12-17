#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// Estructura para almacenar información del personaje
struct Personaje {
    string nombre;
    int anio;
    string tipo;  // "Heroe" o "Villano"
    
    Personaje(string n, int a, string t) : nombre(n), anio(a), tipo(t) {}
    
    // Sobrecarga del operador < para ordenamiento y búsqueda binaria
    bool operator<(const Personaje& otro) const {
        if (anio != otro.anio) return anio < otro.anio;
        return nombre < otro.nombre;  // Desempate por nombre
    }
};

// Clase para gestionar la lista de personajes MCU con búsqueda binaria
class ListaMCU {
private:
    vector<Personaje> personajes;  // Vector ordenado para búsqueda binaria
    int comparacionesBusqueda;     // Contador para análisis
    
    // Búsqueda binaria: encontrar PRIMER índice con año específico
    int busquedaBinariaPrimero(int anio) {
        int izq = 0;
        int der = personajes.size() - 1;
        int resultado = -1;
        
        cout << "\n  [Busqueda Binaria - Primera aparicion de " << anio << "]" << endl;
        int iter = 0;
        
        while (izq <= der) {
            iter++;
            int medio = izq + (der - izq) / 2;
            comparacionesBusqueda++;
            
            cout << "    Iter " << iter << ": izq=" << izq << ", medio=" << medio 
                 << ", der=" << der << " -> anio[" << medio << "]=" 
                 << personajes[medio].anio << endl;
            
            if (personajes[medio].anio == anio) {
                resultado = medio;
                // Seguir buscando hacia la izquierda para encontrar el PRIMERO
                der = medio - 1;
                cout << "      + Encontrado, buscar mas a la izquierda" << endl;
            } else if (personajes[medio].anio < anio) {
                izq = medio + 1;
                cout << "      -> Buscar a la derecha" << endl;
            } else {
                der = medio - 1;
                cout << "      <- Buscar a la izquierda" << endl;
            }
        }
        
        if (resultado != -1) {
            cout << "  + Primer indice encontrado: " << resultado << endl;
        }
        return resultado;
    }
    
    // Búsqueda binaria: encontrar ÚLTIMO índice con año específico
    int busquedaBinariaUltimo(int anio) {
        int izq = 0;
        int der = personajes.size() - 1;
        int resultado = -1;
        
        cout << "\n  [Busqueda Binaria - Ultima aparicion de " << anio << "]" << endl;
        int iter = 0;
        
        while (izq <= der) {
            iter++;
            int medio = izq + (der - izq) / 2;
            comparacionesBusqueda++;
            
            cout << "    Iter " << iter << ": izq=" << izq << ", medio=" << medio 
                 << ", der=" << der << " -> anio[" << medio << "]=" 
                 << personajes[medio].anio << endl;
            
            if (personajes[medio].anio == anio) {
                resultado = medio;
                // Seguir buscando hacia la derecha para encontrar el ÚLTIMO
                izq = medio + 1;
                cout << "      + Encontrado, buscar mas a la derecha" << endl;
            } else if (personajes[medio].anio < anio) {
                izq = medio + 1;
                cout << "      -> Buscar a la derecha" << endl;
            } else {
                der = medio - 1;
                cout << "      <- Buscar a la izquierda" << endl;
            }
        }
        
        if (resultado != -1) {
            cout << "  + Ultimo indice encontrado: " << resultado << endl;
        }
        return resultado;
    }
    
public:
    ListaMCU() : comparacionesBusqueda(0) {}
    
    // Insertar personaje y mantener ordenado
    void insertarOrdenado(const Personaje& p) {
        auto it = lower_bound(personajes.begin(), personajes.end(), p);
        personajes.insert(it, p);
        cout << "  -> Insertado '" << p.nombre << "' (" << p.anio << ")" << endl;
    }
    
    // Obtener PRIMEROS personajes usando búsqueda binaria
    vector<Personaje> obtenerPrimerosConBusquedaBinaria() {
        vector<Personaje> primeros;
        
        if (personajes.empty()) {
            return primeros;
        }
        
        // O(1) - Acceso directo al primer elemento para conocer el año
        int anio_minimo = personajes.front().anio;
        
        cout << "\n=== BUSCANDO PRIMEROS PERSONAJES (Anio " << anio_minimo << ") ===" << endl;
        comparacionesBusqueda = 0;
        
        // O(log n) - Búsqueda binaria del primer índice
        int inicio = busquedaBinariaPrimero(anio_minimo);
        
        // O(log n) - Búsqueda binaria del último índice
        int fin = busquedaBinariaUltimo(anio_minimo);
        
        // O(k) - Extraer el rango (k = personajes del mismo año)
        if (inicio != -1 && fin != -1) {
            cout << "\n  Extrayendo rango [" << inicio << ", " << fin << "]" << endl;
            for (int i = inicio; i <= fin; i++) {
                primeros.push_back(personajes[i]);
            }
        }
        
        cout << "  Total comparaciones: " << comparacionesBusqueda << endl;
        return primeros;
    }
    
    // Obtener ÚLTIMOS personajes usando búsqueda binaria
    vector<Personaje> obtenerUltimosConBusquedaBinaria() {
        vector<Personaje> ultimos;
        
        if (personajes.empty()) {
            return ultimos;
        }
        
        // O(1) - Acceso directo al último elemento para conocer el año
        int anio_maximo = personajes.back().anio;
        
        cout << "\n=== BUSCANDO ULTIMOS PERSONAJES (Anio " << anio_maximo << ") ===" << endl;
        comparacionesBusqueda = 0;
        
        // O(log n) - Búsqueda binaria del primer índice
        int inicio = busquedaBinariaPrimero(anio_maximo);
        
        // O(log n) - Búsqueda binaria del último índice
        int fin = busquedaBinariaUltimo(anio_maximo);
        
        // O(k) - Extraer el rango
        if (inicio != -1 && fin != -1) {
            cout << "\n  Extrayendo rango [" << inicio << ", " << fin << "]" << endl;
            for (int i = inicio; i <= fin; i++) {
                ultimos.push_back(personajes[i]);
            }
        }
        
        cout << "  Total comparaciones: " << comparacionesBusqueda << endl;
        return ultimos;
    }
    
    // Mostrar toda la lista
    void mostrarLista() {
        cout << "\n+========================================================+" << endl;
        cout << "|        LISTA COMPLETA DE PERSONAJES MCU (ORDENADA)    |" << endl;
        cout << "+========================================================+\n" << endl;
        
        cout << left << setw(5) << "IDX" << setw(30) << "NOMBRE" 
             << setw(10) << "ANIO" << setw(15) << "TIPO" << endl;
        cout << string(60, '-') << endl;
        
        for (size_t i = 0; i < personajes.size(); i++) {
            cout << left << setw(5) << i
                 << setw(30) << personajes[i].nombre 
                 << setw(10) << personajes[i].anio 
                 << setw(15) << personajes[i].tipo << endl;
        }
        cout << "\nTotal de personajes: " << personajes.size() << endl;
    }
    
    // Mostrar extremos usando búsqueda binaria
    void mostrarExtremosConBusquedaBinaria() {
        cout << "\n+========================================================+" << endl;
        cout << "|     PERSONAJES EXTREMOS (CON BUSQUEDA BINARIA)        |" << endl;
        cout << "+========================================================+" << endl;
        
        // Obtener primeros
        vector<Personaje> primeros = obtenerPrimerosConBusquedaBinaria();
        
        cout << "\n>>> RESULTADO: PRIMER(OS) PERSONAJE(S) <<<" << endl;
        if (!primeros.empty()) {
            cout << "Anio: " << primeros[0].anio << endl;
            cout << "Cantidad: " << primeros.size() << " personaje(s)" << endl;
            cout << "Personajes:" << endl;
            for (const auto& p : primeros) {
                cout << "  * " << p.nombre << " (" << p.tipo << ")" << endl;
            }
        }
        
        cout << "\n" << string(56, '=') << "\n" << endl;
        
        // Obtener últimos
        vector<Personaje> ultimos = obtenerUltimosConBusquedaBinaria();
        
        cout << ">>> RESULTADO: ULTIMO(S) PERSONAJE(S) <<<" << endl;
        if (!ultimos.empty()) {
            cout << "Anio: " << ultimos[0].anio << endl;
            cout << "Cantidad: " << ultimos.size() << " personaje(s)" << endl;
            cout << "Personajes:" << endl;
            for (const auto& p : ultimos) {
                cout << "  * " << p.nombre << " (" << p.tipo << ")" << endl;
            }
        }
    }
    
    int size() const {
        return personajes.size();
    }
};

int main() {
    cout << "\n+==========================================================+" << endl;
    cout << "|   EJERCICIO 7.2 - PERSONAJES MCU CON BUSQUEDA BINARIA   |" << endl;
    cout << "|   Encontrar primero y ultimo SIN recorrer toda la lista |" << endl;
    cout << "+=========================================================+\n" << endl;
    
    ListaMCU mcu;
    
    cout << "=== INSERTANDO PERSONAJES (orden automatico) ===\n" << endl;
    
    // Insertar personajes del MCU
    mcu.insertarOrdenado(Personaje("Iron Man", 2008, "Heroe"));
    mcu.insertarOrdenado(Personaje("Thanos", 2018, "Villano"));
    mcu.insertarOrdenado(Personaje("Hulk", 2008, "Heroe"));
    mcu.insertarOrdenado(Personaje("Captain America", 2011, "Heroe"));
    mcu.insertarOrdenado(Personaje("Thor", 2011, "Heroe"));
    mcu.insertarOrdenado(Personaje("Loki", 2011, "Villano"));
    mcu.insertarOrdenado(Personaje("Black Widow", 2010, "Heroe"));
    mcu.insertarOrdenado(Personaje("Hawkeye", 2011, "Heroe"));
    mcu.insertarOrdenado(Personaje("Nick Fury", 2008, "Heroe"));
    mcu.insertarOrdenado(Personaje("Doctor Strange", 2016, "Heroe"));
    mcu.insertarOrdenado(Personaje("Spider-Man", 2016, "Heroe"));
    mcu.insertarOrdenado(Personaje("Black Panther", 2016, "Heroe"));
    mcu.insertarOrdenado(Personaje("Scarlet Witch", 2015, "Heroe"));
    mcu.insertarOrdenado(Personaje("Vision", 2015, "Heroe"));
    mcu.insertarOrdenado(Personaje("Ant-Man", 2015, "Heroe"));
    mcu.insertarOrdenado(Personaje("Ultron", 2015, "Villano"));
    mcu.insertarOrdenado(Personaje("Winter Soldier", 2014, "Villano"));
    mcu.insertarOrdenado(Personaje("Star-Lord", 2014, "Heroe"));
    mcu.insertarOrdenado(Personaje("Gamora", 2014, "Heroe"));
    mcu.insertarOrdenado(Personaje("Groot", 2014, "Heroe"));
    mcu.insertarOrdenado(Personaje("Rocket", 2014, "Heroe"));
    mcu.insertarOrdenado(Personaje("Red Skull", 2011, "Villano"));
    mcu.insertarOrdenado(Personaje("Captain Marvel", 2019, "Heroe"));

        cout << "\n+ " << mcu.size() << " personajes insertados correctamente" << endl;
    
    // Mostrar la lista completa
    mcu.mostrarLista();
    
    // Mostrar extremos CON BÚSQUEDA BINARIA
    mcu.mostrarExtremosConBusquedaBinaria();
    
    // Explicación técnica detallada
    cout << "\n\n+==========================================================+" << endl;
    cout << "|           EXPLICACION: USO DE BUSQUEDA BINARIA          |" << endl;
    cout << "+=========================================================+\n" << endl;
    
    cout << "ALGORITMO IMPLEMENTADO:" << endl;
    cout << "\n1ACCESO O(1) A EXTREMOS:" << endl;
    cout << "   front() -> anio del primer personaje" << endl;
    cout << "   back() -> anio del ultimo personaje" << endl;
    
    cout << "\n2 BUSQUEDA BINARIA DEL PRIMER INDICE:" << endl;
    cout << "   Busca el PRIMER indice con el anio objetivo" << endl;
    cout << "   Cuando encuentra el anio, sigue buscando a la IZQUIERDA" << endl;
    cout << "   Complejidad: O(log n)" << endl;
    
    cout << "\n3BUSQUEDA BINARIA DEL ULTIMO INDICE:" << endl;
    cout << "   Busca el ULTIMO indice con el anio objetivo" << endl;
    cout << "   Cuando encuentra el anio, sigue buscando a la DERECHA" << endl;
    cout << "   Complejidad: O(log n)" << endl;
    
    cout << "\n4EXTRACCION DEL RANGO:" << endl;
    cout << "   Una vez conocidos inicio y fin" << endl;
    cout << "   Extrae [inicio...fin] en O(k)" << endl;
    cout << "   donde k = cantidad de personajes del anio" << endl;
    
    cout << "\n+==========================================================+" << endl;
    cout << "|              COMPLEJIDAD TOTAL                           |" << endl;
    cout << "+=========================================================+\n" << endl;
    
    cout << "Para encontrar PRIMEROS:" << endl;
    cout << "  Acceso a front(): O(1)" << endl;
    cout << "  Busqueda binaria primer indice: O(log n)" << endl;
    cout << "  Busqueda binaria ultimo indice: O(log n)" << endl;
    cout << "  Extracción rango: O(k)" << endl;
    cout << "  TOTAL: O(log n) + O(k)" << endl;
    
    cout << "\nPara encontrar ULTIMOS:" << endl;
    cout << "  Acceso a back(): O(1)" << endl;
    cout << "  Busqueda binaria primer indice: O(log n)" << endl;
    cout << "  Busqueda binaria ultimo indice: O(log n)" << endl;
    cout << "  Extraccion rango: O(k)" << endl;
    cout << "  TOTAL: O(log n) + O(k)" << endl;
      
    return 0;
}