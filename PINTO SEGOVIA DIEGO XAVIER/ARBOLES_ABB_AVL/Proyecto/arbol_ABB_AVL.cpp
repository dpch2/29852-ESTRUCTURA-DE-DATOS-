#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <limits>
#include "Validaciones.hpp"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
using namespace std;

class Nodo {
public:
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
    int altura;

    Nodo(int val) {
        valor = val;
        izquierdo = NULL;
        derecho = NULL;
        altura = 1;
    }
};

class ArbolBase {
protected:
    Nodo* raiz;

    void imprimirNodoVertical(Nodo* nodo, string espacios, bool esDerecho) {
        if (nodo != NULL) {
            cout << espacios;
            if (esDerecho) {
                cout << "\\-- ";
                espacios += "    ";
            } else {
                cout << "/-- ";
                espacios += "|   ";
            }
            cout << nodo->valor << endl;
            
            if (nodo->izquierdo != NULL || nodo->derecho != NULL) {
                if (nodo->izquierdo != NULL)
                    imprimirNodoVertical(nodo->izquierdo, espacios, false);
                else {
                    cout << espacios << "/-- [vacio]" << endl;
                }
                
                if (nodo->derecho != NULL)
                    imprimirNodoVertical(nodo->derecho, espacios, true);
                else {
                    cout << espacios << "\\-- [vacio]" << endl;
                }
            }
        }
    }
    
    void imprimirVertical() {
        if (raiz == NULL) {
            cout << "\n[Arbol vacio]\n";
            return;
        }
        cout << "\n";
        cout << raiz->valor << endl;
        if (raiz->izquierdo != NULL)
            imprimirNodoVertical(raiz->izquierdo, "", false);
        else
            cout << "/-- [vacio]" << endl;
            
        if (raiz->derecho != NULL)
            imprimirNodoVertical(raiz->derecho, "", true);
        else
            cout << "\\-- [vacio]" << endl;
        cout << "\n";
    }

    // CORREGIDO: Ahora encuentra el MÁXIMO (nodo mayor) del subárbol izquierdo
    Nodo* encontrarMaximo(Nodo* nodo) {
        while (nodo->derecho != NULL) {
            nodo = nodo->derecho;
        }
        return nodo;
    }

    Nodo* encontrarMinimo(Nodo* nodo) {
        while (nodo->izquierdo != NULL) {
            nodo = nodo->izquierdo;
        }
        return nodo;
    }

    // NUEVO: Recorridos
    void inordenRec(Nodo* nodo) {
        if (nodo != NULL) {
            inordenRec(nodo->izquierdo);
            cout << nodo->valor << " ";
            inordenRec(nodo->derecho);
        }
    }

    void preordenRec(Nodo* nodo) {
        if (nodo != NULL) {
            cout << nodo->valor << " ";
            preordenRec(nodo->izquierdo);
            preordenRec(nodo->derecho);
        }
    }

    void postordenRec(Nodo* nodo) {
        if (nodo != NULL) {
            postordenRec(nodo->izquierdo);
            postordenRec(nodo->derecho);
            cout << nodo->valor << " ";
        }
    }

public:
    ArbolBase() {
        raiz = NULL;
    }

    virtual void insertar(int valor) = 0;
    virtual void eliminar(int valor) = 0;
    virtual bool buscar(int valor) = 0;
    virtual ~ArbolBase() {}

    void imprimir() {
        if (raiz == NULL) {
            cout << "\n[Arbol vacio]\n";
            return;
        }
        imprimirVertical();
    }

    // NUEVO: Métodos de recorrido públicos
    void inorden() {
        cout << "\nRecorrido INORDEN: ";
        if (raiz == NULL) {
            cout << "[Arbol vacio]";
        } else {
            inordenRec(raiz);
        }
        cout << "\n";
    }

    void preorden() {
        cout << "\nRecorrido PREORDEN: ";
        if (raiz == NULL) {
            cout << "[Arbol vacio]";
        } else {
            preordenRec(raiz);
        }
        cout << "\n";
    }

    void postorden() {
        cout << "\nRecorrido POSTORDEN: ";
        if (raiz == NULL) {
            cout << "[Arbol vacio]";
        } else {
            postordenRec(raiz);
        }
        cout << "\n";
    }

    bool estaVacio() {
        return raiz == NULL;
    }
};

class ArbolBinario : public ArbolBase {
private:
    Nodo* insertarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Insertando " << valor << " como nuevo nodo\n";
            return new Nodo(valor);
        }

        if (valor < nodo->valor) {
            cout << "   " << valor << " < " << nodo->valor << " -> Ir a la izquierda\n";
            nodo->izquierdo = insertarRec(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            cout << "   " << valor << " > " << nodo->valor << " -> Ir a la derecha\n";
            nodo->derecho = insertarRec(nodo->derecho, valor);
        } else {
            // DUPLICADO: Regla especial - derecha→izquierda
            cout << "   " << valor << " == " << nodo->valor << " (DUPLICADO)\n";
            if (nodo->derecho == NULL) {
                cout << "   Insertando duplicado a la derecha (espacio libre)\n";
                nodo->derecho = new Nodo(valor);
            } else if (nodo->derecho->izquierdo == NULL) {
                cout << "   Insertando duplicado en derecha->izquierda\n";
                nodo->derecho->izquierdo = new Nodo(valor);
            } else {
                cout << "   Derecha->izquierda ocupado, buscando a la izquierda de ese nodo\n";
                nodo->derecho->izquierdo = insertarRec(nodo->derecho->izquierdo, valor);
            }
        }
        return nodo;
    }

    Nodo* eliminarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Valor " << valor << " no encontrado\n";
            return NULL;
        }

        if (valor < nodo->valor) {
            cout << "   Buscando en subarbol izquierdo\n";
            nodo->izquierdo = eliminarRec(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            cout << "   Buscando en subarbol derecho\n";
            nodo->derecho = eliminarRec(nodo->derecho, valor);
        } else {
            // Nodo encontrado
            if (nodo->izquierdo == NULL && nodo->derecho == NULL) {
                cout << "   Eliminando nodo hoja\n";
                delete nodo;
                return NULL;
            }
            if (nodo->izquierdo == NULL) {
                cout << "   Nodo con un hijo (derecho)\n";
                Nodo* temp = nodo->derecho;
                delete nodo;
                return temp;
            }
            if (nodo->derecho == NULL) {
                cout << "   Nodo con un hijo (izquierdo)\n";
                Nodo* temp = nodo->izquierdo;
                delete nodo;
                return temp;
            }
            // CORREGIDO: Usa el predecesor (mayor del subárbol izquierdo)
            Nodo* predecesor = encontrarMaximo(nodo->izquierdo);
            cout << "   Reemplazando con predecesor " << predecesor->valor << " (mayor del subarbol izquierdo)\n";
            nodo->valor = predecesor->valor;
            nodo->izquierdo = eliminarRec(nodo->izquierdo, predecesor->valor);
        }
        return nodo;
    }

    bool buscarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Valor no encontrado\n";
            return false;
        }
        if (valor == nodo->valor) {
            cout << "   Valor encontrado!\n";
            return true;
        }
        if (valor < nodo->valor) {
            cout << "   Buscar a la izquierda\n";
            return buscarRec(nodo->izquierdo, valor);
        } else {
            cout << "   Buscar a la derecha\n";
            return buscarRec(nodo->derecho, valor);
        }
    }

public:
    void insertar(int valor) {
        cout << "\nINSERTANDO " << valor << " EN ARBOL BINARIO:\n";
        raiz = insertarRec(raiz, valor);
    }

    void eliminar(int valor) {
        cout << "\nELIMINANDO " << valor << " DEL ARBOL BINARIO:\n";
        raiz = eliminarRec(raiz, valor);
    }

    bool buscar(int valor) {
        cout << "\nBUSCANDO " << valor << " EN ARBOL BINARIO:\n";
        return buscarRec(raiz, valor);
    }
};

class ArbolAVL : public ArbolBase {
private:
    int obtenerAltura(Nodo* nodo) {
        if (nodo == NULL) return 0;
        return nodo->altura;
    }

    int obtenerBalance(Nodo* nodo) {
        if (nodo == NULL) return 0;
        return obtenerAltura(nodo->izquierdo) - obtenerAltura(nodo->derecho);
    }

    void actualizarAltura(Nodo* nodo) {
        int altIzq = obtenerAltura(nodo->izquierdo);
        int altDer = obtenerAltura(nodo->derecho);
        nodo->altura = 1 + (altIzq > altDer ? altIzq : altDer);
    }

    Nodo* rotarDerecha(Nodo* y) {
        cout << "   [ROTACION DERECHA en nodo " << y->valor << "]\n";
        Nodo* x = y->izquierdo;
        Nodo* T2 = x->derecho;
        x->derecho = y;
        y->izquierdo = T2;
        actualizarAltura(y);
        actualizarAltura(x);
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        cout << "   [ROTACION IZQUIERDA en nodo " << x->valor << "]\n";
        Nodo* y = x->derecho;
        Nodo* T2 = y->izquierdo;
        y->izquierdo = x;
        x->derecho = T2;
        actualizarAltura(x);
        actualizarAltura(y);
        return y;
    }

    Nodo* insertarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Insertando " << valor << "\n";
            return new Nodo(valor);
        }

        if (valor < nodo->valor) {
            cout << "   " << valor << " < " << nodo->valor << " -> Izquierda\n";
            nodo->izquierdo = insertarRec(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            cout << "   " << valor << " > " << nodo->valor << " -> Derecha\n";
            nodo->derecho = insertarRec(nodo->derecho, valor);
        } else {
            // DUPLICADO: Regla especial - derecha→izquierda
            cout << "   " << valor << " == " << nodo->valor << " (DUPLICADO)\n";
            if (nodo->derecho == NULL) {
                cout << "   Insertando duplicado a la derecha (espacio libre)\n";
                nodo->derecho = new Nodo(valor);
            } else if (nodo->derecho->izquierdo == NULL) {
                cout << "   Insertando duplicado en derecha->izquierda\n";
                nodo->derecho->izquierdo = new Nodo(valor);
            } else {
                cout << "   Derecha->izquierda ocupado, buscando a la izquierda de ese nodo\n";
                nodo->derecho->izquierdo = insertarRec(nodo->derecho->izquierdo, valor);
            }
            // No necesita balanceo al insertar duplicado de esta forma especial
            return nodo;
        }

        actualizarAltura(nodo);
        int balance = obtenerBalance(nodo);
        cout << "   Balance en nodo " << nodo->valor << ": " << balance << "\n";

        if (balance > 1 && valor < nodo->izquierdo->valor) {
            cout << "   Desbalance IZQUIERDA-IZQUIERDA\n";
            return rotarDerecha(nodo);
        }
        if (balance < -1 && valor > nodo->derecho->valor) {
            cout << "   Desbalance DERECHA-DERECHA\n";
            return rotarIzquierda(nodo);
        }
        if (balance > 1 && valor > nodo->izquierdo->valor) {
            cout << "   Desbalance IZQUIERDA-DERECHA\n";
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && valor < nodo->derecho->valor) {
            cout << "   Desbalance DERECHA-IZQUIERDA\n";
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    Nodo* eliminarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Valor no encontrado\n";
            return NULL;
        }

        if (valor < nodo->valor) {
            nodo->izquierdo = eliminarRec(nodo->izquierdo, valor);
        } else if (valor > nodo->valor) {
            nodo->derecho = eliminarRec(nodo->derecho, valor);
        } else {
            // Nodo encontrado
            if (nodo->izquierdo == NULL || nodo->derecho == NULL) {
                Nodo* temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
                if (temp == NULL) {
                    temp = nodo;
                    nodo = NULL;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                // CORREGIDO: Usa el predecesor (mayor del subárbol izquierdo)
                Nodo* predecesor = encontrarMaximo(nodo->izquierdo);
                cout << "   Reemplazando con predecesor " << predecesor->valor << " (mayor del subarbol izquierdo)\n";
                nodo->valor = predecesor->valor;
                nodo->izquierdo = eliminarRec(nodo->izquierdo, predecesor->valor);
            }
        }

        if (nodo == NULL) return nodo;

        actualizarAltura(nodo);
        int balance = obtenerBalance(nodo);

        if (balance > 1 && obtenerBalance(nodo->izquierdo) >= 0)
            return rotarDerecha(nodo);
        if (balance > 1 && obtenerBalance(nodo->izquierdo) < 0) {
            nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
            return rotarDerecha(nodo);
        }
        if (balance < -1 && obtenerBalance(nodo->derecho) <= 0)
            return rotarIzquierda(nodo);
        if (balance < -1 && obtenerBalance(nodo->derecho) > 0) {
            nodo->derecho = rotarDerecha(nodo->derecho);
            return rotarIzquierda(nodo);
        }
        return nodo;
    }

    bool buscarRec(Nodo* nodo, int valor) {
        if (nodo == NULL) {
            cout << "   Valor no encontrado\n";
            return false;
        }
        if (valor == nodo->valor) {
            cout << "   Valor encontrado!\n";
            return true;
        }
        if (valor < nodo->valor)
            return buscarRec(nodo->izquierdo, valor);
        else
            return buscarRec(nodo->derecho, valor);
    }

public:
    void insertar(int valor) {
        cout << "\nINSERTANDO " << valor << " EN ARBOL AVL:\n";
        raiz = insertarRec(raiz, valor);
    }

    void eliminar(int valor) {
        cout << "\nELIMINANDO " << valor << " DEL ARBOL AVL:\n";
        raiz = eliminarRec(raiz, valor);
    }

    bool buscar(int valor) {
        cout << "\nBUSCANDO " << valor << " EN ARBOL AVL:\n";
        return buscarRec(raiz, valor);
    }
};

// Función para leer solo números tecla por tecla (solo muestra números en pantalla)
int leerNumeroEntero(const string& mensaje) {
    string numero = "";
    char tecla;
    
    cout << mensaje;
    
    while (true) {
        #ifdef _WIN32
            tecla = _getch(); // Captura tecla sin mostrarla
        #else
            tecla = getchar();
        #endif
        
        // Si es Enter y tenemos al menos un dígito
        if (tecla == '\r' || tecla == '\n') {
            if (!numero.empty()) {
                break;
            }
            continue;
        }
        
        // Si es Backspace
        if (tecla == '\b' || tecla == 127) {
            if (!numero.empty()) {
                numero.pop_back();
                cout << "\b \b"; // Borra el carácter en pantalla
            }
            continue;
        }
        
        // Solo acepta dígitos (el signo menos se ignora completamente)
        if (isdigit(tecla)) {
            numero += tecla;
            cout << tecla; // Muestra el dígito
        }
        // Cualquier otra tecla (incluyendo -) es ignorada (no se muestra nada)
    }
    
    cout << endl;
    
    // Convertir a entero
    int resultado = 0;
    if (!numero.empty()) {
        resultado = stoi(numero);
    }
    
    return resultado;
}

// Función para leer opciones de menú con validación específica
int leerOpcionMenu(const string& mensaje, int opcionMin, int opcionMax) {
    int opcion;
    
    while (true) {
        opcion = leerNumeroEntero(mensaje);
        
        if (opcion >= opcionMin && opcion <= opcionMax) {
            return opcion;
        } else {
            cout << "\nError: Opcion invalida. Ingrese un numero entre " << opcionMin << " y " << opcionMax << ".\n";
        }
    }
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}

void mostrarMenu() {
    cout << "\n============================================\n";
    cout << "   SIMULADOR DE ARBOLES AVL Y BINARIOS\n";
    cout << "============================================\n";
    cout << "1. Insertar valor\n";
    cout << "2. Eliminar valor\n";
    cout << "3. Buscar valor\n";
    cout << "4. Imprimir arbol (estructura)\n";
    cout << "5. Recorrido Inorden\n";
    cout << "6. Recorrido Preorden\n";
    cout << "7. Recorrido Postorden\n";
    cout << "8. Cambiar tipo de arbol\n";
    cout << "9. Salir\n";
    cout << "\nOpcion: ";
}

int main() {
    ArbolBase* arbol = NULL;
    int tipoArbol = 1;
    int opcion, valor;

    cout << "============================================\n";
    cout << "   SIMULADOR DE ARBOLES AVL Y BINARIOS\n";
    cout << "============================================\n";
    cout << "\n1. Arbol AVL\n";
    cout << "2. Arbol Binario\n";
    tipoArbol = leerOpcionMenu("\nOpcion: ", 1, 2);

    if (tipoArbol == 1) {
        arbol = new ArbolAVL();
        cout << "\nArbol AVL seleccionado\n";
    } else {
        arbol = new ArbolBinario();
        cout << "\nArbol Binario seleccionado\n";
    }

    pausar();

    do {
        limpiarPantalla();
        cout << "\nTIPO: " << (tipoArbol == 1 ? "AVL" : "BINARIO") << "\n";
        mostrarMenu();
        opcion = leerOpcionMenu("", 1, 9);

        switch (opcion) {
        case 1:
            valor = leerNumeroEntero("\nValor a insertar: ");
            cout << "Los nodos izquierdos (menores) se muestran con /-- y los derechos (mayores) con \\--\n";
            arbol->insertar(valor);
            arbol->imprimir();
            pausar();
            break;
        case 2:
            if (!arbol->estaVacio()) {
                valor = leerNumeroEntero("\nValor a eliminar: ");
                arbol->eliminar(valor);
                arbol->imprimir();
            } else {
                cout << "\nArbol vacio\n";
            }
            pausar();
            break;
        case 3:
            if (!arbol->estaVacio()) {
                valor = leerNumeroEntero("\nValor a buscar: ");
                arbol->buscar(valor);
            } else {
                cout << "\nArbol vacio\n";
            }
            pausar();
            break;
        case 4:
            arbol->imprimir();
            pausar();
            break;
        case 5:
            arbol->inorden();
            pausar();
            break;
        case 6:
            arbol->preorden();
            pausar();
            break;
        case 7:
            arbol->postorden();
            pausar();
            break;
        case 8:
            delete arbol;
            tipoArbol = leerOpcionMenu("\n1. AVL\n2. Binario\nOpcion: ", 1, 2);
            if (tipoArbol == 1)
                arbol = new ArbolAVL();
            else
                arbol = new ArbolBinario();
            pausar();
            break;
        case 9:
            cout << "\nGracias!\n";
            break;
        default:
            cout << "\nOpcion invalida\n";
            pausar();
        }
    } while (opcion != 9);

    delete arbol;
    return 0;
}
