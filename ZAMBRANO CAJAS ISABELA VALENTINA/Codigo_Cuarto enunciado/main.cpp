#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

const int TAM_TABLA = 20; // Tamaño de la tabla hash

// ============================================
// ESTRUCTURAS DE DATOS
// ============================================
struct Persona {
    string nombre;
    string cedula;
    Persona* siguiente;
    bool ocupado;
    
    Persona() : nombre(""), cedula(""), siguiente(nullptr), ocupado(false) {}
    
    Persona(string n, string c) : nombre(n), cedula(c), siguiente(nullptr), ocupado(true) {}
};

struct TablaHash {
    Persona** tabla; // Puntero doble usando malloc
    int totalPersonas;
    int totalColisiones;
    
    // Constructor usando malloc
    TablaHash() : totalPersonas(0), totalColisiones(0) {
        // Reservar memoria con malloc (equivalente a Persona* tabla[TAM_TABLA])
        tabla = (Persona**)malloc(TAM_TABLA * sizeof(Persona*));
        
        for(int i = 0; i < TAM_TABLA; i++) {
            Persona* nuevaPersona = new Persona();
            *(tabla + i) = nuevaPersona;
        }
    }
    
    // Destructor
    ~TablaHash() {
        limpiar();
        // Liberar memoria malloc
        for(int i = 0; i < TAM_TABLA; i++) {
            delete *(tabla + i);
        }
        free(tabla);
    }
    
    // Limpiar toda la tabla
    void limpiar() {
        for(int i = 0; i < TAM_TABLA; i++) {
            Persona* actual = *(tabla + i);
            
            // Limpiar lista enlazada
            Persona* temp = actual->siguiente;
            while(temp != nullptr) {
                Persona* siguiente = temp->siguiente;
                delete temp;
                temp = siguiente;
            }
            
            // Reiniciar nodo principal
            actual->nombre = "";
            actual->cedula = "";
            actual->siguiente = nullptr;
            actual->ocupado = false;
        }
        totalPersonas = 0;
        totalColisiones = 0;
    }
};

// ============================================
// VARIABLES GLOBALES
// ============================================
TablaHash* tablaPersonas = new TablaHash();

// ============================================
// FUNCIONES AUXILIARES
// ============================================

// Función para obtener un carácter de un string sin []
char obtenerCaracter(const string& str, int indice) {
    if(indice < 0 || indice >= str.length()) return '\0';
    return str.c_str()[indice];
}

// Extraer subcadena sin substr()
string extraerSubcadena(const string& str, int inicio, int longitud) {
    string resultado = "";
    int fin = inicio + longitud;
    if(fin > str.length()) fin = str.length();
    
    for(int i = inicio; i < fin; i++) {
        resultado += obtenerCaracter(str, i);
    }
    return resultado;
}

// Convertir string a número sin stoi()
int stringANumero(const string& str) {
    int resultado = 0;
    for(int i = 0; i < str.length(); i++) {
        char c = obtenerCaracter(str, i);
        if(c >= '0' && c <= '9') {
            resultado = resultado * 10 + (c - '0');
        }
    }
    return resultado;
}

// ============================================
// FUNCIONES DE VALIDACIÓN
// ============================================

bool validarNombre(const string& nombre) {
    if(nombre.empty() || nombre.length() < 2) {
        cout << "Error: El nombre debe tener al menos 2 caracteres.\n";
        return false;
    }
    
    for(int i = 0; i < nombre.length(); i++) {
        char c = obtenerCaracter(nombre, i);
        if(!isalpha(c) && c != ' ' && c != '.') {
            cout << "Error: El nombre solo puede contener letras, espacios y puntos.\n";
            return false;
        }
    }
    return true;
}

bool validarCedulaEcuatoriana(const string& cedula) {
    if(cedula.length() != 10) {
        cout << "Error: La cédula debe tener 10 dígitos.\n";
        return false;
    }
    
    // Verificar que todos sean dígitos
    for(int i = 0; i < 10; i++) {
        char c = obtenerCaracter(cedula, i);
        if(!(c >= '0' && c <= '9')) {
            cout << "Error: La cédula solo puede contener números.\n";
            return false;
        }
    }
    
    // Validar provincia (01-24, 30)
    string provincia = extraerSubcadena(cedula, 0, 2);
    int prov = stringANumero(provincia);
    if(prov < 1 || (prov > 24 && prov != 30)) {
        cout << "Error: Los primeros dos dígitos no corresponden a una provincia válida (01-24, 30).\n";
        return false;
    }
    
    // Validar tercer dígito (0-6)
    int tercerDigito = obtenerCaracter(cedula, 2) - '0';
    if(tercerDigito > 6) {
        cout << "Error: El tercer dígito debe estar entre 0 y 6.\n";
        return false;
    }
    
    // Algoritmo de validación
    int suma = 0;
    int coeficientes[9] = {2, 1, 2, 1, 2, 1, 2, 1, 2};
    
    for(int i = 0; i < 9; i++) {
        int digito = obtenerCaracter(cedula, i) - '0';
        int producto = digito * *(coeficientes + i);
        
        if(producto >= 10) {
            producto -= 9;
        }
        suma += producto;
    }
    
    int decenaSuperior = ((suma / 10) + 1) * 10;
    int digitoVerificador = decenaSuperior - suma;
    
    if(digitoVerificador == 10) digitoVerificador = 0;
    
    int ultimoDigito = obtenerCaracter(cedula, 9) - '0';
    
    if(digitoVerificador != ultimoDigito) {
        cout << "Error: Cédula inválida según el dígito verificador.\n";
        return false;
    }
    
    return true;
}

bool validarCedulaGeneral(const string& cedula) {
    if(cedula.empty()) {
        cout << "Error: La cédula no puede estar vacía.\n";
        return false;
    }
    
    for(int i = 0; i < cedula.length(); i++) {
        char c = obtenerCaracter(cedula, i);
        if(!(c >= '0' && c <= '9')) {
            cout << "Error: La cédula debe contener solo números.\n";
            return false;
        }
    }
    
    if(cedula.length() < 5 || cedula.length() > 15) {
        cout << "Error: La cédula debe tener entre 5 y 15 dígitos.\n";
        return false;
    }
    
    return true;
}

// ============================================
// FUNCIONES HASH
// ============================================

int hashCedula(const string& cedula) {
    long long suma = 0;
    for(int i = 0; i < cedula.length(); i++) {
        char c = obtenerCaracter(cedula, i);
        suma = (suma * 31 + c) % TAM_TABLA;
    }
    return suma % TAM_TABLA;
}

int hashNombre(const string& nombre) {
    int suma = 0;
    for(int i = 0; i < nombre.length(); i++) {
        char c = obtenerCaracter(nombre, i);
        suma = (suma * 17 + tolower(c)) % TAM_TABLA;
    }
    return suma % TAM_TABLA;
}

// ============================================
// OPERACIONES CON LA TABLA HASH
// ============================================

bool existeCedula(const string& cedula) {
    int pos = hashCedula(cedula);
    Persona* posicion = *(tablaPersonas->tabla + pos);
    
    // Buscar en la posición principal
    if(posicion->ocupado && posicion->cedula == cedula) {
        return true;
    }
    
    // Buscar en la lista enlazada
    Persona* actual = posicion->siguiente;
    while(actual != nullptr) {
        if(actual->ocupado && actual->cedula == cedula) {
            return true;
        }
        actual = actual->siguiente;
    }
    
    return false;
}

bool existeNombre(const string& nombre) {
    for(int i = 0; i < TAM_TABLA; i++) {
        Persona* posicion = *(tablaPersonas->tabla + i);
        
        if(posicion->ocupado && posicion->nombre == nombre) {
            return true;
        }
        
        Persona* actual = posicion->siguiente;
        while(actual != nullptr) {
            if(actual->ocupado && actual->nombre == nombre) {
                return true;
            }
            actual = actual->siguiente;
        }
    }
    return false;
}

bool insertarPersona(const string& nombre, const string& cedula) {
    // Validar datos
    if(!validarNombre(nombre)) {
        return false;
    }
    
    cout << "\nTipo de cédula:\n";
    cout << "1. Ecuatoriana (10 dígitos con validación completa)\n";
    cout << "2. Otro país (validación básica)\n";
    cout << "Seleccione opción: ";
    
    int opcion;
    cin >> opcion;
    cin.ignore();
    
    bool cedulaValida = false;
    if(opcion == 1) {
        cedulaValida = validarCedulaEcuatoriana(cedula);
    } else {
        cedulaValida = validarCedulaGeneral(cedula);
    }
    
    if(!cedulaValida) {
        return false;
    }
    
    // Verificar si la cédula ya existe
    if(existeCedula(cedula)) {
        cout << "Error: La cédula " << cedula << " ya está registrada.\n";
        return false;
    }
    
    // Calcular hash
    int pos = hashCedula(cedula);
    int hashNom = hashNombre(nombre);
    
    // Crear nueva persona
    Persona* nuevaPersona = new Persona(nombre, cedula);
    
    // Obtener posición en la tabla
    Persona* posicion = *(tablaPersonas->tabla + pos);
    
    // Insertar en la tabla
    if(!posicion->ocupado) {
        // Caso: posición vacía
        posicion->nombre = nombre;
        posicion->cedula = cedula;
        posicion->ocupado = true;
        delete nuevaPersona;
        
        cout << "\n✓ Persona insertada exitosamente.\n";
        cout << "  Posición en tabla: " << pos << "\n";
        cout << "  Hash de nombre: " << hashNom << "\n";
        cout << "  Hash de cédula: " << pos << "\n";
    } else {
        // Caso: colisión - agregar a lista enlazada
        Persona* actual = posicion;
        while(actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevaPersona;
        tablaPersonas->totalColisiones++;
        
        cout << "\n✓ Persona insertada exitosamente (con colisión).\n";
        cout << "  Posición base: " << pos << "\n";
        cout << "  Hash de nombre: " << hashNom << "\n";
        cout << "  Hash de cédula: " << pos << "\n";
        cout << "  Se resolvió con lista enlazada.\n";
    }
    
    tablaPersonas->totalPersonas++;
    return true;
}

void buscarPorCedula(const string& cedula) {
    int pos = hashCedula(cedula);
    int intentos = 0;
    
    cout << "\n=== BUSCANDO CÉDULA: " << cedula << " ===\n";
    cout << "Hash calculado: " << pos << "\n";
    
    // Obtener posición
    Persona* posicion = *(tablaPersonas->tabla + pos);
    
    // Buscar en posición principal
    if(posicion->ocupado && posicion->cedula == cedula) {
        cout << "\n✓ PERSONA ENCONTRADA EN POSICIÓN PRINCIPAL " << pos << "\n";
        cout << "  Nombre: " << posicion->nombre << "\n";
        cout << "  Cédula: " << posicion->cedula << "\n";
        cout << "  Hash de nombre: " << hashNombre(posicion->nombre) << "\n";
        return;
    }
    
    // Buscar en lista enlazada
    Persona* actual = posicion->siguiente;
    int posEnLista = 0;
    while(actual != nullptr) {
        intentos++;
        if(actual->ocupado && actual->cedula == cedula) {
            cout << "\n✓ PERSONA ENCONTRADA EN LISTA ENLAZADA\n";
            cout << "  Posición base: " << pos << "\n";
            cout << "  Posición en lista: " << posEnLista << "\n";
            cout << "  Intentos de búsqueda: " << intentos << "\n";
            cout << "  Nombre: " << actual->nombre << "\n";
            cout << "  Cédula: " << actual->cedula << "\n";
            cout << "  Hash de nombre: " << hashNombre(actual->nombre) << "\n";
            return;
        }
        actual = actual->siguiente;
        posEnLista++;
    }
    
    cout << "\n✗ PERSONA NO ENCONTRADA\n";
    cout << "  La cédula " << cedula << " no existe en la tabla.\n";
}

void buscarPorNombre(const string& nombre) {
    cout << "\n=== BUSCANDO NOMBRE: " << nombre << " ===\n";
    int hashNom = hashNombre(nombre);
    int encontrados = 0;
    
    cout << "Hash calculado del nombre: " << hashNom << "\n\n";
    
    for(int i = 0; i < TAM_TABLA; i++) {
        Persona* posicion = *(tablaPersonas->tabla + i);
        
        if(posicion->ocupado && posicion->nombre == nombre) {
            encontrados++;
            cout << "\n  Persona " << encontrados << ":\n";
            cout << "    Nombre: " << posicion->nombre << "\n";
            cout << "    Cédula: " << posicion->cedula << "\n";
            cout << "    Hash de cédula: " << hashCedula(posicion->cedula) << "\n";
            cout << "    Posición en tabla: " << i << "\n";
        }
        
        Persona* actual = posicion->siguiente;
        while(actual != nullptr) {
            if(actual->ocupado && actual->nombre == nombre) {
                encontrados++;
                cout << "\n  Persona " << encontrados << " (en lista enlazada):\n";
                cout << "    Nombre: " << actual->nombre << "\n";
                cout << "    Cédula: " << actual->cedula << "\n";
                cout << "    Hash de cédula: " << hashCedula(actual->cedula) << "\n";
                cout << "    Posición base: " << i << "\n";
            }
            actual = actual->siguiente;
        }
    }
    
    if(encontrados == 0) {
        cout << "✗ No se encontraron personas con el nombre '" << nombre << "'\n";
    } else {
        cout << "\n✓ Total encontrados: " << encontrados << " persona(s)\n";
    }
}

// ============================================
// VISUALIZACIÓN DE LA TABLA HASH
// ============================================

void mostrarTablaHash() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "                       TABLA HASH COMPLETA\n";
    cout << string(70, '=') << "\n\n";
    
    cout << "Tamaño de tabla: " << TAM_TABLA << " posiciones\n";
    cout << "Total personas: " << tablaPersonas->totalPersonas << "\n";
    cout << "Total colisiones: " << tablaPersonas->totalColisiones << "\n";
    double factorCarga = (double)tablaPersonas->totalPersonas / TAM_TABLA;
    cout << "Factor de carga: " << factorCarga << "\n\n";
    
    for(int i = 0; i < TAM_TABLA; i++) {
        Persona* posicion = *(tablaPersonas->tabla + i);
        
        cout << "[" << i << "] ";
        
        if(posicion->ocupado) {
            // Mostrar persona principal
            cout << "* " << posicion->nombre 
                 << " | Ced: " << posicion->cedula
                 << " | H(ced):" << hashCedula(posicion->cedula)
                 << " | H(nom):" << hashNombre(posicion->nombre);
            
            // Mostrar lista enlazada si existe
            Persona* actual = posicion->siguiente;
            int elementosEnLista = 0;
            while(actual != nullptr) {
                if(elementosEnLista == 0) cout << " \n     |";
                else cout << "     |";
                
                cout << "--> " << actual->nombre 
                     << " | Ced: " << actual->cedula
                     << " | H(ced):" << hashCedula(actual->cedula);
                
                actual = actual->siguiente;
                elementosEnLista++;
                
                if(actual != nullptr) cout << "\n";
            }
            
            if(elementosEnLista > 0) {
                cout << " \n     |-> Total en lista: " << elementosEnLista << " persona(s)";
            }
        } else {
            cout << "[VACIO]";
        }
        cout << "\n" << string(50, '-') << "\n";
    }
}

void mostrarEstadisticas() {
    cout << "\n" << string(60, '=') << "\n";
    cout << "                  ESTADÍSTICAS DETALLADAS\n";
    cout << string(60, '=') << "\n";
    
    int posicionesOcupadas = 0;
    int maxElementosEnLista = 0;
    int totalListasNoVacias = 0;
    
    // Array temporal para distribución
    int* distribucion = (int*)malloc(TAM_TABLA * sizeof(int));
    
    for(int i = 0; i < TAM_TABLA; i++) {
        int elementosEnPosicion = 0;
        Persona* posicion = *(tablaPersonas->tabla + i);
        
        if(posicion->ocupado) {
            elementosEnPosicion++;
            posicionesOcupadas++;
            
            Persona* actual = posicion->siguiente;
            while(actual != nullptr) {
                elementosEnPosicion++;
                actual = actual->siguiente;
            }
        }
        
        *(distribucion + i) = elementosEnPosicion;
        
        if(elementosEnPosicion > 0) {
            totalListasNoVacias++;
        }
        
        if(elementosEnPosicion > maxElementosEnLista) {
            maxElementosEnLista = elementosEnPosicion;
        }
    }
    
    cout << "\nDISTRIBUCION DE ELEMENTOS:\n";
    for(int i = 0; i < TAM_TABLA; i++) {
        cout << "  Posicion " << i << ": " << *(distribucion + i) << " persona(s) | ";
        for(int j = 0; j < *(distribucion + i); j++) cout << "#";
        cout << "\n";
    }
    
    cout << "\nESTADISTICAS:\n";
    cout << "  * Posiciones ocupadas: " << posicionesOcupadas << "/" << TAM_TABLA << "\n";
    cout << "  * Posiciones vacias: " << (TAM_TABLA - posicionesOcupadas) << "\n";
    cout << "  * Total personas: " << tablaPersonas->totalPersonas << "\n";
    cout << "  * Total colisiones: " << tablaPersonas->totalColisiones << "\n";
    cout << "  * Maximo en una posicion: " << maxElementosEnLista << " persona(s)\n";
    double factorCarga = (double)tablaPersonas->totalPersonas / TAM_TABLA;
    cout << "  * Factor de carga: " << factorCarga << "\n";
    cout << "  * Eficiencia de busqueda promedio: " 
         << (tablaPersonas->totalColisiones > 0 ? "O(n)" : "O(1)") << "\n";
    
    // Liberar memoria del array temporal
    free(distribucion);
}

// ============================================
// FUNCIONES DE PRUEBA
// ============================================

void generarDatosPrueba() {
    struct PersonaPrueba {
        string nombre;
        string cedula;
    };
    
    // Array de prueba usando malloc
    PersonaPrueba* datosPrueba = (PersonaPrueba*)malloc(10 * sizeof(PersonaPrueba));
    
    // Inicializar datos de prueba
    *(datosPrueba + 0) = {"Juan Perez", "1710034567"};
    *(datosPrueba + 1) = {"Maria Garcia", "0912345678"};
    *(datosPrueba + 2) = {"Carlos Lopez", "1712345678"};
    *(datosPrueba + 3) = {"Ana Martinez", "0912345698"};
    *(datosPrueba + 4) = {"Luis Rodriguez", "1712345698"};
    *(datosPrueba + 5) = {"Sofia Gonzalez", "0912345687"};
    *(datosPrueba + 6) = {"Pedro Sanchez", "1712345687"};
    *(datosPrueba + 7) = {"Laura Fernandez", "0912345667"};
    *(datosPrueba + 8) = {"Diego Ramirez", "1712345667"};
    *(datosPrueba + 9) = {"Elena Torres", "0912345657"};
    
    cout << "\n=== GENERANDO DATOS DE PRUEBA ===\n";
    
    for(int i = 0; i < 10; i++) {
        cout << "\nInsertando: " << (*(datosPrueba + i)).nombre 
             << " - " << (*(datosPrueba + i)).cedula;
        insertarPersona((*(datosPrueba + i)).nombre, (*(datosPrueba + i)).cedula);
    }
    
    cout << "\n✓ 10 personas de prueba insertadas correctamente.\n";
    
    // Liberar memoria
    free(datosPrueba);
}

// ============================================
// FUNCIÓN PRINCIPAL
// ============================================
int main() {
    int opcion;
    string nombre, cedula;
    
    cout << "=====================================================\n";
    cout << "     SISTEMA DE GESTION DE PERSONAS CON TABLA HASH   \n";
    cout << "          (Implementado con malloc sin arrays)       \n";
    cout << "=====================================================\n\n";
    
    do {
        cout << "\n" << string(50, '=') << "\n";
        cout << "                    MENU PRINCIPAL\n";
        cout << string(50, '=') << "\n";
        cout << "1. Insertar nueva persona\n";
        cout << "2. Buscar persona por cedula\n";
        cout << "3. Buscar personas por nombre\n";
        cout << "4. Mostrar tabla hash completa\n";
        cout << "5. Mostrar estadisticas detalladas\n";
        cout << "6. Generar datos de prueba (10 personas)\n";
        cout << "7. Limpiar toda la tabla\n";
        cout << "8. Validar una cedula ecuatoriana\n";
        cout << "9. Salir del programa\n";
        cout << "\nSeleccione una opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch(opcion) {
            case 1:
                cout << "\n=== INSERTAR NUEVA PERSONA ===\n";
                cout << "Ingrese el nombre completo: ";
                getline(cin, nombre);
                cout << "Ingrese la cedula: ";
                getline(cin, cedula);
                
                if(insertarPersona(nombre, cedula)) {
                    cout << "\n✓ Operacion completada exitosamente.\n";
                } else {
                    cout << "\n✗ No se pudo insertar la persona.\n";
                }
                break;
                
            case 2:
                cout << "\n=== BUSCAR POR CEDULA ===\n";
                cout << "Ingrese la cedula a buscar: ";
                getline(cin, cedula);
                buscarPorCedula(cedula);
                break;
                
            case 3:
                cout << "\n=== BUSCAR POR NOMBRE ===\n";
                cout << "Ingrese el nombre a buscar: ";
                getline(cin, nombre);
                buscarPorNombre(nombre);
                break;
                
            case 4:
                mostrarTablaHash();
                break;
                
            case 5:
                mostrarEstadisticas();
                break;
                
            case 6:
                generarDatosPrueba();
                break;
                
            case 7:
                cout << "\n¿Está seguro de limpiar toda la tabla? (s/n): ";
                char confirmar;
                cin >> confirmar;
                if(tolower(confirmar) == 's') {
                    tablaPersonas->limpiar();
                    cout << "✓ Tabla limpiada correctamente.\n";
                }
                break;
                
            case 8:
                cout << "\n=== VALIDAR CEDULA ECUATORIANA ===\n";
                cout << "Ingrese la cedula a validar: ";
                getline(cin, cedula);
                if(validarCedulaEcuatoriana(cedula)) {
                    cout << "\n✓ Cedula ecuatoriana valida.\n";
                } else {
                    cout << "\n✗ Cedula invalida.\n";
                }
                break;
                
            case 9:
                cout << "\n¡Gracias por usar el sistema! Hasta pronto.\n";
                break;
                
            default:
                cout << "\n✗ Opcion invalida. Intente nuevamente.\n";
        }
        
        if(opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
        
    } while(opcion != 9);
    
    // Liberar memoria
    delete tablaPersonas;
    
    return 0;
}