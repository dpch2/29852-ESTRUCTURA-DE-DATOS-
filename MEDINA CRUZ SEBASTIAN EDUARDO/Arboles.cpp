#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

// ==================== FUNCIONES AUXILIARES ====================
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausa() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(10000, '\n');
    cin.get();
}

void esperar(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

void imprimirLinea(char c, int n) {
    for(int i = 0; i < n; i++) cout << c;
    cout << endl;
}

// ==================== NODO PARA ÁRBOL BINARIO ====================
struct NodoBinario {
    int valor;
    NodoBinario* izq;
    NodoBinario* der;
    
    NodoBinario(int val) : valor(val), izq(nullptr), der(nullptr) {}
};

// ==================== ÁRBOL BINARIO DE BÚSQUEDA ====================
class ArbolBinario {
private:
    NodoBinario* raiz;
    
    void insertarRecursivo(NodoBinario*& nodo, int valor, string posicion) {
        if (nodo == nullptr) {
            nodo = new NodoBinario(valor);
            cout << "✓ " << valor << " insertado en " << posicion << endl;
            return;
        }
        
        if (valor < nodo->valor) {
            cout << "→ Comparando " << valor << " < " << nodo->valor << ", ir a la izquierda" << endl;
            if (nodo->izq == nullptr) {
                nodo->izq = new NodoBinario(valor);
                cout << "✓ " << valor << " insertado a la IZQUIERDA de " << nodo->valor << endl;
            } else {
                insertarRecursivo(nodo->izq, valor, "izq de " + to_string(nodo->valor));
            }
        } else if (valor > nodo->valor) {
            cout << "→ Comparando " << valor << " > " << nodo->valor << ", ir a la derecha" << endl;
            if (nodo->der == nullptr) {
                nodo->der = new NodoBinario(valor);
                cout << "✓ " << valor << " insertado a la DERECHA de " << nodo->valor << endl;
            } else {
                insertarRecursivo(nodo->der, valor, "der de " + to_string(nodo->valor));
            }
        } else {
            cout << "✗ El valor " << valor << " ya existe en el árbol" << endl;
        }
    }
    
    NodoBinario* encontrarMinimo(NodoBinario* nodo) {
        while (nodo->izq != nullptr) {
            nodo = nodo->izq;
        }
        return nodo;
    }
    
    NodoBinario* eliminarRecursivo(NodoBinario* nodo, int valor) {
        if (nodo == nullptr) {
            cout << "✗ El valor " << valor << " no existe en el árbol" << endl;
            return nullptr;
        }
        
        if (valor < nodo->valor) {
            nodo->izq = eliminarRecursivo(nodo->izq, valor);
        } else if (valor > nodo->valor) {
            nodo->der = eliminarRecursivo(nodo->der, valor);
        } else {
            cout << "✓ Nodo " << valor << " encontrado" << endl;
            
            // Caso 1: Sin hijo izquierdo
            if (nodo->izq == nullptr) {
                cout << "  → Reemplazando con hijo derecho" << endl;
                NodoBinario* temp = nodo->der;
                delete nodo;
                return temp;
            }
            // Caso 2: Sin hijo derecho
            else if (nodo->der == nullptr) {
                cout << "  → Reemplazando con hijo izquierdo" << endl;
                NodoBinario* temp = nodo->izq;
                delete nodo;
                return temp;
            }
            
            // Caso 3: Dos hijos
            cout << "  → Nodo tiene dos hijos, buscando sucesor" << endl;
            NodoBinario* sucesor = encontrarMinimo(nodo->der);
            cout << "  → Sucesor encontrado: " << sucesor->valor << endl;
            nodo->valor = sucesor->valor;
            nodo->der = eliminarRecursivo(nodo->der, sucesor->valor);
        }
        return nodo;
    }
    
    bool buscarRecursivo(NodoBinario* nodo, int valor, string posicion) {
        if (nodo == nullptr) {
            cout << "→ Llegamos a nullptr en " << posicion << endl;
            return false;
        }
        
        cout << "→ Visitando nodo " << nodo->valor << " en " << posicion << endl;
        
        if (valor == nodo->valor) {
            return true;
        } else if (valor < nodo->valor) {
            cout << "→ " << valor << " < " << nodo->valor << ", ir a la izquierda" << endl;
            return buscarRecursivo(nodo->izq, valor, "izq de " + to_string(nodo->valor));
        } else {
            cout << "→ " << valor << " > " << nodo->valor << ", ir a la derecha" << endl;
            return buscarRecursivo(nodo->der, valor, "der de " + to_string(nodo->valor));
        }
    }
    
    void imprimirNodo(NodoBinario* nodo, string prefijo, bool esIzquierdo) {
        if (nodo != nullptr) {
            cout << prefijo;
            cout << (esIzquierdo ? "├──" : "└──");
            cout << nodo->valor << endl;
            
            if (nodo->izq != nullptr || nodo->der != nullptr) {
                if (nodo->izq != nullptr) {
                    imprimirNodo(nodo->izq, prefijo + (esIzquierdo ? "│   " : "    "), true);
                } else {
                    cout << prefijo << (esIzquierdo ? "│   " : "    ") << "├──(vacío)" << endl;
                }
                
                if (nodo->der != nullptr) {
                    imprimirNodo(nodo->der, prefijo + (esIzquierdo ? "│   " : "    "), false);
                } else {
                    cout << prefijo << (esIzquierdo ? "│   " : "    ") << "└──(vacío)" << endl;
                }
            }
        }
    }
    
    void destruirArbol(NodoBinario* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->izq);
            destruirArbol(nodo->der);
            delete nodo;
        }
    }
    
public:
    ArbolBinario() : raiz(nullptr) {}
    
    ~ArbolBinario() {
        destruirArbol(raiz);
    }
    
    void insertar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "INSERTANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        if (raiz == nullptr) {
            raiz = new NodoBinario(valor);
            cout << "✓ " << valor << " insertado como raíz" << endl;
        } else {
            insertarRecursivo(raiz, valor, "raíz");
        }
        
        esperar(500);
        visualizar();
    }
    
    void eliminar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "ELIMINANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        raiz = eliminarRecursivo(raiz, valor);
        esperar(500);
        visualizar();
    }
    
    void buscar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "BUSCANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        bool encontrado = buscarRecursivo(raiz, valor, "raíz");
        
        if (encontrado) {
            cout << "\n✓ ¡Valor " << valor << " ENCONTRADO!" << endl;
        } else {
            cout << "\n✗ Valor " << valor << " NO ENCONTRADO" << endl;
        }
        pausa();
    }
    
    void visualizar() {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "VISUALIZACIÓN DEL ÁRBOL BINARIO DE BÚSQUEDA" << endl;
        imprimirLinea('=', 60);
        
        if (raiz == nullptr) {
            cout << "El árbol está vacío" << endl;
        } else {
            cout << "RAÍZ" << endl;
            imprimirNodo(raiz, "", false);
        }
        
        imprimirLinea('=', 60);
        cout << endl;
    }
};

// ==================== NODO PARA ÁRBOL AVL ====================
struct NodoAVL {
    int valor;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    
    NodoAVL(int val) : valor(val), izq(nullptr), der(nullptr), altura(1) {}
};

// ==================== ÁRBOL AVL ====================
class ArbolAVL {
private:
    NodoAVL* raiz;
    
    int obtenerAltura(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return nodo->altura;
    }
    
    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == nullptr) return 0;
        return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
    }
    
    void actualizarAltura(NodoAVL* nodo) {
        if (nodo != nullptr) {
            nodo->altura = 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
        }
    }
    
    NodoAVL* rotacionDerecha(NodoAVL* z) {
        cout << "\n🔄 ROTACIÓN DERECHA en nodo " << z->valor << endl;
        NodoAVL* y = z->izq;
        NodoAVL* T3 = y->der;
        
        cout << "   Antes: " << z->valor << " (raíz)" << endl;
        cout << "          ↙" << endl;
        cout << "         " << y->valor << endl;
        
        y->der = z;
        z->izq = T3;
        
        actualizarAltura(z);
        actualizarAltura(y);
        
        cout << "   Después: " << y->valor << " (nueva raíz)" << endl;
        cout << "            ↘" << endl;
        cout << "           " << z->valor << endl;
        
        return y;
    }
    
    NodoAVL* rotacionIzquierda(NodoAVL* z) {
        cout << "\n🔄 ROTACIÓN IZQUIERDA en nodo " << z->valor << endl;
        NodoAVL* y = z->der;
        NodoAVL* T2 = y->izq;
        
        cout << "   Antes: " << z->valor << " (raíz)" << endl;
        cout << "          ↘" << endl;
        cout << "         " << y->valor << endl;
        
        y->izq = z;
        z->der = T2;
        
        actualizarAltura(z);
        actualizarAltura(y);
        
        cout << "   Después: " << y->valor << " (nueva raíz)" << endl;
        cout << "            ↙" << endl;
        cout << "           " << z->valor << endl;
        
        return y;
    }
    
    NodoAVL* insertarRecursivo(NodoAVL* nodo, int valor, string posicion) {
        if (nodo == nullptr) {
            cout << "✓ " << valor << " insertado en " << posicion << endl;
            return new NodoAVL(valor);
        }
        
        if (valor < nodo->valor) {
            cout << "→ " << valor << " < " << nodo->valor << ", ir a la izquierda" << endl;
            nodo->izq = insertarRecursivo(nodo->izq, valor, "izq de " + to_string(nodo->valor));
        } else if (valor > nodo->valor) {
            cout << "→ " << valor << " > " << nodo->valor << ", ir a la derecha" << endl;
            nodo->der = insertarRecursivo(nodo->der, valor, "der de " + to_string(nodo->valor));
        } else {
            cout << "✗ El valor " << valor << " ya existe" << endl;
            return nodo;
        }
        
        actualizarAltura(nodo);
        
        int balance = obtenerBalance(nodo);
        cout << "⚖️  Factor de balance de " << nodo->valor << ": " << balance << endl;
        
        // Caso Izquierda-Izquierda
        if (balance > 1 && valor < nodo->izq->valor) {
            cout << "⚠️  Desbalance detectado: Caso Izquierda-Izquierda" << endl;
            return rotacionDerecha(nodo);
        }
        
        // Caso Derecha-Derecha
        if (balance < -1 && valor > nodo->der->valor) {
            cout << "⚠️  Desbalance detectado: Caso Derecha-Derecha" << endl;
            return rotacionIzquierda(nodo);
        }
        
        // Caso Izquierda-Derecha
        if (balance > 1 && valor > nodo->izq->valor) {
            cout << "⚠️  Desbalance detectado: Caso Izquierda-Derecha" << endl;
            cout << "   → Primera rotación izquierda en " << nodo->izq->valor << endl;
            nodo->izq = rotacionIzquierda(nodo->izq);
            cout << "   → Segunda rotación derecha en " << nodo->valor << endl;
            return rotacionDerecha(nodo);
        }
        
        // Caso Derecha-Izquierda
        if (balance < -1 && valor < nodo->der->valor) {
            cout << "⚠️  Desbalance detectado: Caso Derecha-Izquierda" << endl;
            cout << "   → Primera rotación derecha en " << nodo->der->valor << endl;
            nodo->der = rotacionDerecha(nodo->der);
            cout << "   → Segunda rotación izquierda en " << nodo->valor << endl;
            return rotacionIzquierda(nodo);
        }
        
        if (balance >= -1 && balance <= 1) {
            cout << "✓ Nodo " << nodo->valor << " está balanceado" << endl;
        }
        
        return nodo;
    }
    
    NodoAVL* encontrarMinimo(NodoAVL* nodo) {
        while (nodo->izq != nullptr) {
            nodo = nodo->izq;
        }
        return nodo;
    }
    
    NodoAVL* eliminarRecursivo(NodoAVL* nodo, int valor) {
        if (nodo == nullptr) {
            cout << "✗ El valor " << valor << " no existe" << endl;
            return nullptr;
        }
        
        if (valor < nodo->valor) {
            nodo->izq = eliminarRecursivo(nodo->izq, valor);
        } else if (valor > nodo->valor) {
            nodo->der = eliminarRecursivo(nodo->der, valor);
        } else {
            cout << "✓ Nodo " << valor << " encontrado" << endl;
            
            if (nodo->izq == nullptr) {
                cout << "  → Reemplazando con hijo derecho" << endl;
                NodoAVL* temp = nodo->der;
                delete nodo;
                return temp;
            } else if (nodo->der == nullptr) {
                cout << "  → Reemplazando con hijo izquierdo" << endl;
                NodoAVL* temp = nodo->izq;
                delete nodo;
                return temp;
            }
            
            cout << "  → Nodo tiene dos hijos" << endl;
            NodoAVL* sucesor = encontrarMinimo(nodo->der);
            cout << "  → Sucesor: " << sucesor->valor << endl;
            nodo->valor = sucesor->valor;
            nodo->der = eliminarRecursivo(nodo->der, sucesor->valor);
        }
        
        if (nodo == nullptr) return nodo;
        
        actualizarAltura(nodo);
        int balance = obtenerBalance(nodo);
        cout << "⚖️  Factor de balance de " << nodo->valor << ": " << balance << endl;
        
        // Rebalanceo después de eliminación
        if (balance > 1 && obtenerBalance(nodo->izq) >= 0) {
            cout << "⚠️  Rebalanceando: Rotación derecha" << endl;
            return rotacionDerecha(nodo);
        }
        
        if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
            cout << "⚠️  Rebalanceando: Izquierda-Derecha" << endl;
            nodo->izq = rotacionIzquierda(nodo->izq);
            return rotacionDerecha(nodo);
        }
        
        if (balance < -1 && obtenerBalance(nodo->der) <= 0) {
            cout << "⚠️  Rebalanceando: Rotación izquierda" << endl;
            return rotacionIzquierda(nodo);
        }
        
        if (balance < -1 && obtenerBalance(nodo->der) > 0) {
            cout << "⚠️  Rebalanceando: Derecha-Izquierda" << endl;
            nodo->der = rotacionDerecha(nodo->der);
            return rotacionIzquierda(nodo);
        }
        
        return nodo;
    }
    
    bool buscarRecursivo(NodoAVL* nodo, int valor, string posicion) {
        if (nodo == nullptr) {
            cout << "→ Llegamos a nullptr en " << posicion << endl;
            return false;
        }
        
        cout << "→ Visitando nodo " << nodo->valor << " en " << posicion << endl;
        
        if (valor == nodo->valor) {
            return true;
        } else if (valor < nodo->valor) {
            cout << "→ " << valor << " < " << nodo->valor << ", ir a la izquierda" << endl;
            return buscarRecursivo(nodo->izq, valor, "izq de " + to_string(nodo->valor));
        } else {
            cout << "→ " << valor << " > " << nodo->valor << ", ir a la derecha" << endl;
            return buscarRecursivo(nodo->der, valor, "der de " + to_string(nodo->valor));
        }
    }
    
    void imprimirNodo(NodoAVL* nodo, string prefijo, bool esIzquierdo) {
        if (nodo != nullptr) {
            cout << prefijo;
            cout << (esIzquierdo ? "├──" : "└──");
            cout << nodo->valor << "[" << obtenerBalance(nodo) << "]" << endl;
            
            if (nodo->izq != nullptr || nodo->der != nullptr) {
                if (nodo->izq != nullptr) {
                    imprimirNodo(nodo->izq, prefijo + (esIzquierdo ? "│   " : "    "), true);
                } else {
                    cout << prefijo << (esIzquierdo ? "│   " : "    ") << "├──(vacío)" << endl;
                }
                
                if (nodo->der != nullptr) {
                    imprimirNodo(nodo->der, prefijo + (esIzquierdo ? "│   " : "    "), false);
                } else {
                    cout << prefijo << (esIzquierdo ? "│   " : "    ") << "└──(vacío)" << endl;
                }
            }
        }
    }
    
    void destruirArbol(NodoAVL* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->izq);
            destruirArbol(nodo->der);
            delete nodo;
        }
    }
    
public:
    ArbolAVL() : raiz(nullptr) {}
    
    ~ArbolAVL() {
        destruirArbol(raiz);
    }
    
    void insertar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "INSERTANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        raiz = insertarRecursivo(raiz, valor, "raíz");
        esperar(800);
        visualizar();
    }
    
    void eliminar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "ELIMINANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        raiz = eliminarRecursivo(raiz, valor);
        esperar(800);
        visualizar();
    }
    
    void buscar(int valor) {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "BUSCANDO: " << valor << endl;
        imprimirLinea('=', 60);
        
        bool encontrado = buscarRecursivo(raiz, valor, "raíz");
        
        if (encontrado) {
            cout << "\n✓ ¡Valor " << valor << " ENCONTRADO!" << endl;
        } else {
            cout << "\n✗ Valor " << valor << " NO ENCONTRADO" << endl;
        }
        pausa();
    }
    
    void visualizar() {
        cout << "\n";
        imprimirLinea('=', 60);
        cout << "VISUALIZACIÓN DEL ÁRBOL AVL" << endl;
        cout << "(Formato: valor[balance])" << endl;
        imprimirLinea('=', 60);
        
        if (raiz == nullptr) {
            cout << "El árbol está vacío" << endl;
        } else {
            cout << "RAÍZ" << endl;
            imprimirNodo(raiz, "", false);
        }
        
        imprimirLinea('=', 60);
        cout << endl;
    }
};

// ==================== MENÚS ====================
void menuArbol(ArbolBinario& arbol, string tipo) {
    int opcion, valor;
    
    while (true) {
        limpiarPantalla();
        cout << "╔";
        imprimirLinea('=', 58);
        cout << "║  ÁRBOL " << tipo << endl;
        cout << "╚";
        imprimirLinea('=', 58);
        cout << "\n1. Insertar valor" << endl;
        cout << "2. Eliminar valor" << endl;
        cout << "3. Buscar valor" << endl;
        cout << "4. Imprimir árbol" << endl;
        cout << "5. Volver al menú principal" << endl;
        cout << "\n";
        imprimirLinea('-', 60);
        cout << "Selecciona una opción: ";
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opción inválida" << endl;
            esperar(1000);
            continue;
        }
        
        switch (opcion) {
            case 1:
                cout << "Ingresa el valor a insertar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.insertar(valor);
                    pausa();
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 2:
                cout << "Ingresa el valor a eliminar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.eliminar(valor);
                    pausa();
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 3:
                cout << "Ingresa el valor a buscar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.buscar(valor);
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 4:
                arbol.visualizar();
                pausa();
                break;
            case 5:
                return;
            default:
                cout << "Opción inválida" << endl;
                esperar(1000);
        }
    }
}

void menuArbolAVL(ArbolAVL& arbol, string tipo) {
    int opcion, valor;
    
    while (true) {
        limpiarPantalla();
        cout << "╔";
        imprimirLinea('=', 58);
        cout << "║  ÁRBOL " << tipo << endl;
        cout << "╚";
        imprimirLinea('=', 58);
        cout << "\n1. Insertar valor" << endl;
        cout << "2. Eliminar valor" << endl;
        cout << "3. Buscar valor" << endl;
        cout << "4. Imprimir árbol" << endl;
        cout << "5. Volver al menú principal" << endl;
        cout << "\n";
        imprimirLinea('-', 60);
        cout << "Selecciona una opción: ";
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opción inválida" << endl;
            esperar(1000);
            continue;
        }
        
        switch (opcion) {
            case 1:
                cout << "Ingresa el valor a insertar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.insertar(valor);
                    pausa();
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 2:
                cout << "Ingresa el valor a eliminar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.eliminar(valor);
                    pausa();
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 3:
                cout << "Ingresa el valor a buscar: ";
                cin >> valor;
                if (!cin.fail()) {
                    arbol.buscar(valor);
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Valor inválido" << endl;
                    esperar(1000);
                }
                break;
            case 4:
                arbol.visualizar();
                pausa();
                break;
            case 5:
                return;
            default:
                cout << "Opción inválida" << endl;
                esperar(1000);
        }
    }
}

void menuPrincipal() {
    int opcion;
    
    while (true) {
        limpiarPantalla();
        cout << "╔";
        imprimirLinea('=', 58);
        cout << "║              SIMULADOR DE ÁRBOLES" << endl;
        cout << "╚";
        imprimirLinea('=', 58);
        cout << "\n1. Árbol Binario de Búsqueda" << endl;
        cout << "2. Árbol AVL" << endl;
        cout << "3. Salir" << endl;
        cout << "\n";
        imprimirLinea('-', 60);
        cout << "Selecciona una opción: ";
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Opción inválida" << endl;
            esperar(1000);
            continue;
        }
        
        switch (opcion) {
            case 1: {
                ArbolBinario arbol;
                menuArbol(arbol, "BINARIO DE BÚSQUEDA");
                break;
            }
            case 2: {
                ArbolAVL arbol;
                menuArbolAVL(arbol, "AVL");
                break;
            }
            case 3:
                cout << "\n¡Hasta luego!" << endl;
                return;
            default:
                cout << "Opción inválida" << endl;
                esperar(1000);
        }
    }
}

// ==================== FUNCIÓN PRINCIPAL ====================
int main() {
    menuPrincipal();
    return 0;
}