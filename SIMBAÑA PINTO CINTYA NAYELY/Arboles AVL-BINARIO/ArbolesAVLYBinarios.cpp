#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

// ==================== ÁRBOL BINARIO DE BÚSQUEDA ====================
struct NodoBinario {
    int dato;
    NodoBinario* izq;
    NodoBinario* der;
    
    NodoBinario(int val) : dato(val), izq(NULL), der(NULL) {}
};

class ArbolBinario {
private:
    NodoBinario* raiz;
    
    NodoBinario* insertarRecursivo(NodoBinario* nodo, int valor) {
        if (nodo == NULL) {
            return new NodoBinario(valor);
        }
        
        if (valor < nodo->dato) {
            nodo->izq = insertarRecursivo(nodo->izq, valor);
        } else if (valor > nodo->dato) {
            nodo->der = insertarRecursivo(nodo->der, valor);
        }
        
        return nodo;
    }
    
    NodoBinario* buscarMinimo(NodoBinario* nodo) {
        while (nodo->izq != NULL) {
            nodo = nodo->izq;
        }
        return nodo;
    }
    
    NodoBinario* eliminarRecursivo(NodoBinario* nodo, int valor, bool& encontrado) {
        if (nodo == NULL) {
            encontrado = false;
            return NULL;
        }
        
        if (valor < nodo->dato) {
            nodo->izq = eliminarRecursivo(nodo->izq, valor, encontrado);
        } else if (valor > nodo->dato) {
            nodo->der = eliminarRecursivo(nodo->der, valor, encontrado);
        } else {
            encontrado = true;
            
            if (nodo->izq == NULL) {
                NodoBinario* temp = nodo->der;
                delete nodo;
                return temp;
            } else if (nodo->der == NULL) {
                NodoBinario* temp = nodo->izq;
                delete nodo;
                return temp;
            }
            
            NodoBinario* temp = buscarMinimo(nodo->der);
            nodo->dato = temp->dato;
            nodo->der = eliminarRecursivo(nodo->der, temp->dato, encontrado);
        }
        
        return nodo;
    }
    
    bool buscarRecursivo(NodoBinario* nodo, int valor) {
        if (nodo == NULL) return false;
        if (nodo->dato == valor) return true;
        if (valor < nodo->dato) return buscarRecursivo(nodo->izq, valor);
        return buscarRecursivo(nodo->der, valor);
    }
    
    void imprimirEspacios(int n) {
        for (int i = 0; i < n; i++) cout << " ";
    }
    
    int calcularAltura(NodoBinario* nodo) {
        if (nodo == NULL) return 0;
        return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
    }
    
    void imprimirNivel(NodoBinario* nodo, int nivel, int espacioInicial, int espacioEntre) {
        if (nodo == NULL) {
            if (nivel == 1) {
                imprimirEspacios(espacioInicial);
                cout << "  ";
                imprimirEspacios(espacioEntre);
            }
            return;
        }
        
        if (nivel == 1) {
            imprimirEspacios(espacioInicial);
            cout << setw(2) << nodo->dato;
            imprimirEspacios(espacioEntre);
        } else if (nivel > 1) {
            imprimirNivel(nodo->izq, nivel - 1, espacioInicial, espacioEntre);
            imprimirNivel(nodo->der, nivel - 1, espacioInicial, espacioEntre);
        }
    }
    
public:
    ArbolBinario() : raiz(NULL) {}
    
    void insertar(int valor) {
        raiz = insertarRecursivo(raiz, valor);
        cout << "Valor " << valor << " insertado en Arbol Binario.\n";
    }
    
    void eliminar(int valor) {
        bool encontrado = true;
        raiz = eliminarRecursivo(raiz, valor, encontrado);
        if (encontrado) {
            cout << "Valor " << valor << " eliminado del Arbol Binario.\n";
        } else {
            cout << "Valor " << valor << " no encontrado en Arbol Binario.\n";
        }
    }
    
    void buscar(int valor) {
        if (buscarRecursivo(raiz, valor)) {
            cout << "Valor " << valor << " ENCONTRADO en Arbol Binario.\n";
        } else {
            cout << "Valor " << valor << " NO ENCONTRADO en Arbol Binario.\n";
        }
    }
    
    void mostrarGrafico() {
        if (raiz == NULL) {
            cout << "Arbol Binario vacio.\n";
            return;
        }
        
        cout << "\n=== ARBOL BINARIO DE BUSQUEDA ===\n\n";
        int altura = calcularAltura(raiz);
        
        for (int i = 1; i <= altura; i++) {
            int espacioInicial = (int)pow(2, altura - i) - 1;
            int espacioEntre = (int)pow(2, altura - i + 1) - 1;
            imprimirNivel(raiz, i, espacioInicial * 2, espacioEntre * 2);
            cout << "\n\n";
        }
    }
};

// ==================== ÁRBOL AVL ====================
struct NodoAVL {
    int dato;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;
    
    NodoAVL(int val) : dato(val), altura(1), izq(NULL), der(NULL) {}
};

class ArbolAVL {
private:
    NodoAVL* raiz;
    
    int obtenerAltura(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return nodo->altura;
    }
    
    int obtenerBalance(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return obtenerAltura(nodo->izq) - obtenerAltura(nodo->der);
    }
    
    void actualizarAltura(NodoAVL* nodo) {
        if (nodo != NULL) {
            nodo->altura = 1 + max(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));
        }
    }
    
    NodoAVL* rotarDerecha(NodoAVL* y) {
        NodoAVL* x = y->izq;
        NodoAVL* T2 = x->der;
        
        x->der = y;
        y->izq = T2;
        
        actualizarAltura(y);
        actualizarAltura(x);
        
        return x;
    }
    
    NodoAVL* rotarIzquierda(NodoAVL* x) {
        NodoAVL* y = x->der;
        NodoAVL* T2 = y->izq;
        
        y->izq = x;
        x->der = T2;
        
        actualizarAltura(x);
        actualizarAltura(y);
        
        return y;
    }
    
    NodoAVL* insertarRecursivo(NodoAVL* nodo, int valor) {
        if (nodo == NULL) {
            return new NodoAVL(valor);
        }
        
        if (valor < nodo->dato) {
            nodo->izq = insertarRecursivo(nodo->izq, valor);
        } else if (valor > nodo->dato) {
            nodo->der = insertarRecursivo(nodo->der, valor);
        } else {
            return nodo;
        }
        
        actualizarAltura(nodo);
        
        int balance = obtenerBalance(nodo);
        
        // Caso Izquierda-Izquierda
        if (balance > 1 && valor < nodo->izq->dato) {
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha-Derecha
        if (balance < -1 && valor > nodo->der->dato) {
            return rotarIzquierda(nodo);
        }
        
        // Caso Izquierda-Derecha
        if (balance > 1 && valor > nodo->izq->dato) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha-Izquierda
        if (balance < -1 && valor < nodo->der->dato) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }
        
        return nodo;
    }
    
    NodoAVL* buscarMinimo(NodoAVL* nodo) {
        while (nodo->izq != NULL) {
            nodo = nodo->izq;
        }
        return nodo;
    }
    
    NodoAVL* eliminarRecursivo(NodoAVL* nodo, int valor, bool& encontrado) {
        if (nodo == NULL) {
            encontrado = false;
            return NULL;
        }
        
        if (valor < nodo->dato) {
            nodo->izq = eliminarRecursivo(nodo->izq, valor, encontrado);
        } else if (valor > nodo->dato) {
            nodo->der = eliminarRecursivo(nodo->der, valor, encontrado);
        } else {
            encontrado = true;
            
            if (nodo->izq == NULL || nodo->der == NULL) {
                NodoAVL* temp = nodo->izq ? nodo->izq : nodo->der;
                
                if (temp == NULL) {
                    temp = nodo;
                    nodo = NULL;
                } else {
                    *nodo = *temp;
                }
                delete temp;
            } else {
                NodoAVL* temp = buscarMinimo(nodo->der);
                nodo->dato = temp->dato;
                nodo->der = eliminarRecursivo(nodo->der, temp->dato, encontrado);
            }
        }
        
        if (nodo == NULL) return nodo;
        
        actualizarAltura(nodo);
        
        int balance = obtenerBalance(nodo);
        
        // Caso Izquierda-Izquierda
        if (balance > 1 && obtenerBalance(nodo->izq) >= 0) {
            return rotarDerecha(nodo);
        }
        
        // Caso Izquierda-Derecha
        if (balance > 1 && obtenerBalance(nodo->izq) < 0) {
            nodo->izq = rotarIzquierda(nodo->izq);
            return rotarDerecha(nodo);
        }
        
        // Caso Derecha-Derecha
        if (balance < -1 && obtenerBalance(nodo->der) <= 0) {
            return rotarIzquierda(nodo);
        }
        
        // Caso Derecha-Izquierda
        if (balance < -1 && obtenerBalance(nodo->der) > 0) {
            nodo->der = rotarDerecha(nodo->der);
            return rotarIzquierda(nodo);
        }
        
        return nodo;
    }
    
    bool buscarRecursivo(NodoAVL* nodo, int valor) {
        if (nodo == NULL) return false;
        if (nodo->dato == valor) return true;
        if (valor < nodo->dato) return buscarRecursivo(nodo->izq, valor);
        return buscarRecursivo(nodo->der, valor);
    }
    
    void imprimirEspacios(int n) {
        for (int i = 0; i < n; i++) cout << " ";
    }
    
    int calcularAltura(NodoAVL* nodo) {
        if (nodo == NULL) return 0;
        return 1 + max(calcularAltura(nodo->izq), calcularAltura(nodo->der));
    }
    
    void imprimirNivel(NodoAVL* nodo, int nivel, int espacioInicial, int espacioEntre) {
        if (nodo == NULL) {
            if (nivel == 1) {
                imprimirEspacios(espacioInicial);
                cout << "  ";
                imprimirEspacios(espacioEntre);
            }
            return;
        }
        
        if (nivel == 1) {
            imprimirEspacios(espacioInicial);
            cout << setw(2) << nodo->dato;
            imprimirEspacios(espacioEntre);
        } else if (nivel > 1) {
            imprimirNivel(nodo->izq, nivel - 1, espacioInicial, espacioEntre);
            imprimirNivel(nodo->der, nivel - 1, espacioInicial, espacioEntre);
        }
    }
    
public:
    ArbolAVL() : raiz(NULL) {}
    
    void insertar(int valor) {
        raiz = insertarRecursivo(raiz, valor);
        cout << "Valor " << valor << " insertado en Arbol AVL.\n";
    }
    
    void eliminar(int valor) {
        bool encontrado = true;
        raiz = eliminarRecursivo(raiz, valor, encontrado);
        if (encontrado) {
            cout << "Valor " << valor << " eliminado del Arbol AVL.\n";
        } else {
            cout << "Valor " << valor << " no encontrado en Arbol AVL.\n";
        }
    }
    
    void buscar(int valor) {
        if (buscarRecursivo(raiz, valor)) {
            cout << "Valor " << valor << " ENCONTRADO en Arbol AVL.\n";
        } else {
            cout << "Valor " << valor << " NO ENCONTRADO en Arbol AVL.\n";
        }
    }
    
    void mostrarGrafico() {
        if (raiz == NULL) {
            cout << "Arbol AVL vacio.\n";
            return;
        }
        
        cout << "\n=== ARBOL AVL (BALANCEADO) ===\n\n";
        int altura = calcularAltura(raiz);
        
        for (int i = 1; i <= altura; i++) {
            int espacioInicial = (int)pow(2, altura - i) - 1;
            int espacioEntre = (int)pow(2, altura - i + 1) - 1;
            imprimirNivel(raiz, i, espacioInicial * 2, espacioEntre * 2);
            cout << "\n\n";
        }
    }
};

// ==================== MENÚ PRINCIPAL ====================
int main() {
    ArbolBinario arbolBinario;
    ArbolAVL arbolAVL;
    int opcion, valor, tipoArbol;
    
    do {
        cout << "\n========================================\n";
        cout << "   ARBOLES BINARIOS Y AVL - MODO DOS\n";
        cout << "========================================\n";
        cout << "1. Insertar valor\n";
        cout << "2. Eliminar valor\n";
        cout << "3. Buscar valor\n";
        cout << "4. Mostrar arboles (Grafico)\n";
        cout << "5. Salir\n";
        cout << "========================================\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                cout << "\nIngrese el valor a insertar: ";
                cin >> valor;
                cout << "Seleccione arbol (1=Binario, 2=AVL, 3=Ambos): ";
                cin >> tipoArbol;
                
                if (tipoArbol == 1 || tipoArbol == 3) {
                    arbolBinario.insertar(valor);
                }
                if (tipoArbol == 2 || tipoArbol == 3) {
                    arbolAVL.insertar(valor);
                }
                break;
                
            case 2:
                cout << "\nIngrese el valor a eliminar: ";
                cin >> valor;
                cout << "Seleccione arbol (1=Binario, 2=AVL, 3=Ambos): ";
                cin >> tipoArbol;
                
                if (tipoArbol == 1 || tipoArbol == 3) {
                    arbolBinario.eliminar(valor);
                }
                if (tipoArbol == 2 || tipoArbol == 3) {
                    arbolAVL.eliminar(valor);
                }
                break;
                
            case 3:
                cout << "\nIngrese el valor a buscar: ";
                cin >> valor;
                cout << "Seleccione arbol (1=Binario, 2=AVL, 3=Ambos): ";
                cin >> tipoArbol;
                
                if (tipoArbol == 1 || tipoArbol == 3) {
                    arbolBinario.buscar(valor);
                }
                if (tipoArbol == 2 || tipoArbol == 3) {
                    arbolAVL.buscar(valor);
                }
                break;
                
            case 4:
                arbolBinario.mostrarGrafico();
                cout << "\n";
                arbolAVL.mostrarGrafico();
                break;
                
            case 5:
                cout << "\nSaliendo del programa...\n";
                break;
                
            default:
                cout << "\nOpcion invalida. Intente nuevamente.\n";
        }
        
    } while(opcion != 5);
    
    return 0;
}  