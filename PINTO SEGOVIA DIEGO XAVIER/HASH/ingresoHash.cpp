#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <map>

using namespace std;

// Estructura para almacenar una persona
struct Persona {
    string nombre;
    string apellido;
    string cedula;
    string hash_md5;
};

// Tabla hash usando un map (clave: hash MD5, valor: Persona)
map<string, Persona> tablaHash;

// Función simple para generar un "hash" (simulación de MD5)
string generarHashSimple(const string& texto) {
    unsigned long hash = 5381;
    
    for (char c : texto) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    // Convertir a hexadecimal (simulando formato MD5)
    stringstream ss;
    ss << hex << setfill('0') << setw(8) << hash;
    
    // Extender para que parezca más a MD5 (32 caracteres)
    string hashStr = ss.str();
    while (hashStr.length() < 32) {
        hashStr += hashStr;
    }
    hashStr = hashStr.substr(0, 32);
    
    return hashStr;
}

// Función para generar hash de una persona (nombre + apellido + cedula)
string generarHashPersona(const string& nombre, const string& apellido, const string& cedula) {
    string datos = nombre + apellido + cedula;
    return generarHashSimple(datos);
}

// Función para limpiar la pantalla
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para pausar
void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Opción 1: Registrar una persona
void registrarPersona() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "       REGISTRAR NUEVA PERSONA" << endl;
    cout << "========================================" << endl << endl;
    
    Persona p;
    
    cout << "Ingrese el nombre: ";
    cin.ignore();
    getline(cin, p.nombre);
    
    cout << "Ingrese el apellido: ";
    getline(cin, p.apellido);
    
    cout << "Ingrese la cedula: ";
    getline(cin, p.cedula);
    
    // Generar hash MD5 (simulado)
    p.hash_md5 = generarHashPersona(p.nombre, p.apellido, p.cedula);
    
    // Verificar si ya existe
    if (tablaHash.find(p.hash_md5) != tablaHash.end()) {
        cout << "\nERROR: Esta persona ya existe en el sistema" << endl;
    } else {
        // Agregar a la tabla hash
        tablaHash[p.hash_md5] = p;
        
        cout << "\nPersona registrada exitosamente" << endl;
        cout << "\n--- Informacion registrada ---" << endl;
        cout << "Nombre completo: " << p.nombre << " " << p.apellido << endl;
        cout << "Cedula: " << p.cedula << endl;
        cout << "Hash MD5: " << p.hash_md5 << endl;
    }
    
    pausar();
}

// Opción 2: Consultar persona por datos
void consultarPersona() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "         CONSULTAR PERSONA" << endl;
    cout << "========================================" << endl << endl;
    
    if (tablaHash.empty()) {
        cout << "No hay personas registradas en el sistema." << endl;
        pausar();
        return;
    }
    
    string nombre, apellido, cedula;
    
    cout << "Ingrese el nombre: ";
    cin.ignore();
    getline(cin, nombre);
    
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    
    cout << "Ingrese la cedula: ";
    getline(cin, cedula);
    
    // Generar hash de búsqueda
    string hashBusqueda = generarHashPersona(nombre, apellido, cedula);
    
    cout << "\n--- Buscando en la tabla hash ---" << endl;
    cout << "Hash generado: " << hashBusqueda << endl << endl;
    
    // Buscar en la tabla hash
    auto it = tablaHash.find(hashBusqueda);
    
    if (it != tablaHash.end()) {
        cout << "PERSONA ENCONTRADA" << endl << endl;
        cout << "--- Datos de la persona ---" << endl;
        cout << "Nombre: " << it->second.nombre << endl;
        cout << "Apellido: " << it->second.apellido << endl;
        cout << "Cedula: " << it->second.cedula << endl;
        cout << "Hash MD5: " << it->second.hash_md5 << endl;
    } else {
        cout << "Persona NO encontrada en el sistema." << endl;
    }
    
    pausar();
}

// Opción 3: Consultar por hash
void consultarPorHash() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "       CONSULTAR POR HASH MD5" << endl;
    cout << "========================================" << endl << endl;
    
    if (tablaHash.empty()) {
        cout << "No hay personas registradas en el sistema." << endl;
        pausar();
        return;
    }
    
    string hash;
    cout << "Ingrese el hash MD5: ";
    cin.ignore();
    getline(cin, hash);
    
    // Buscar en la tabla hash
    auto it = tablaHash.find(hash);
    
    if (it != tablaHash.end()) {
        cout << "\nPERSONA ENCONTRADA" << endl << endl;
        cout << "--- Datos de la persona ---" << endl;
        cout << "Nombre: " << it->second.nombre << endl;
        cout << "Apellido: " << it->second.apellido << endl;
        cout << "Cedula: " << it->second.cedula << endl;
        cout << "Hash MD5: " << it->second.hash_md5 << endl;
    } else {
        cout << "\nNo existe ninguna persona con ese hash." << endl;
    }
    
    pausar();
}

// Opción 4: Mostrar tabla hash completa
void mostrarTablaHash() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "          TABLA HASH COMPLETA" << endl;
    cout << "========================================" << endl << endl;
    
    if (tablaHash.empty()) {
        cout << "La tabla hash esta vacia." << endl;
        pausar();
        return;
    }
    
    cout << "Total de registros: " << tablaHash.size() << endl << endl;
    
    int contador = 1;
    for (const auto& entry : tablaHash) {
        cout << "--- Registro #" << contador << " ---" << endl;
        cout << "Hash MD5: " << entry.first << endl;
        cout << "Nombre: " << entry.second.nombre << endl;
        cout << "Apellido: " << entry.second.apellido << endl;
        cout << "Cedula: " << entry.second.cedula << endl;
        cout << endl;
        contador++;
    }
    
    pausar();
}

// Opción 5: Eliminar persona
void eliminarPersona() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "         ELIMINAR PERSONA" << endl;
    cout << "========================================" << endl << endl;
    
    if (tablaHash.empty()) {
        cout << "No hay personas registradas en el sistema." << endl;
        pausar();
        return;
    }
    
    string nombre, apellido, cedula;
    
    cout << "Ingrese el nombre: ";
    cin.ignore();
    getline(cin, nombre);
    
    cout << "Ingrese el apellido: ";
    getline(cin, apellido);
    
    cout << "Ingrese la cedula: ";
    getline(cin, cedula);
    
    // Generar hash de búsqueda
    string hashBusqueda = generarHashPersona(nombre, apellido, cedula);
    
    // Buscar y eliminar
    auto it = tablaHash.find(hashBusqueda);
    
    if (it != tablaHash.end()) {
        cout << "\nPersona encontrada" << endl;
        cout << "Nombre: " << it->second.nombre << " " << it->second.apellido << endl;
        cout << "Cedula: " << it->second.cedula << endl;
        
        cout << "\n¿Esta seguro de eliminar esta persona? (S/N): ";
        char confirmacion;
        cin >> confirmacion;
        
        if (confirmacion == 'S' || confirmacion == 's') {
            tablaHash.erase(it);
            cout << "\nPersona eliminada exitosamente" << endl;
        } else {
            cout << "\nOperacion cancelada." << endl;
        }
    } else {
        cout << "\nPersona NO encontrada en el sistema." << endl;
    }
    
    pausar();
}

// Menú principal
void mostrarMenu() {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "    SISTEMA DE GESTION CON HASH MD5" << endl;
    cout << "========================================" << endl << endl;
    cout << "1. Registrar nueva persona" << endl;
    cout << "2. Consultar persona por datos" << endl;
    cout << "3. Consultar persona por hash MD5" << endl;
    cout << "4. Mostrar tabla hash completa" << endl;
    cout << "5. Eliminar persona" << endl;
    cout << "6. Salir" << endl << endl;
    cout << "Seleccione una opcion: ";
}

int main() {
    int opcion;
    
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                registrarPersona();
                break;
            case 2:
                consultarPersona();
                break;
            case 3:
                consultarPorHash();
                break;
            case 4:
                mostrarTablaHash();
                break;
            case 5:
                eliminarPersona();
                break;
            case 6:
                limpiarPantalla();
                cout << "\nGracias por usar el sistema" << endl << endl;
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo." << endl;
                pausar();
        }
        
    } while (opcion != 6);
    
    return 0;
}