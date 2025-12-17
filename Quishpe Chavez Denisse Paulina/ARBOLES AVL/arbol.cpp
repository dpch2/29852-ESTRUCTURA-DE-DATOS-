#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <algorithm>

using namespace std;

// ============ CLASE NODO AVL ============
class Nodo {
public:
    int dato;
    Nodo* izq;
    Nodo* der;
    int altura;
    
    Nodo(int val) {
        dato = val;
        izq = NULL;
        der = NULL;
        altura = 1;
    }
};

// ============ UTILIDADES GRAFICAS ============
void posicionar(int x, int y) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(h, pos);
}

void limpiarPantalla() {
    system("cls");
}

// ============ FUNCIONES AVL ============

int obtenerAltura(Nodo* n) {
    if (n == NULL) return 0;
    return n->altura;
}

int calcularBalance(Nodo* n) {
    if (n == NULL) return 0;
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

void actualizarAltura(Nodo* n) {
    if (n != NULL) {
        n->altura = 1 + max(obtenerAltura(n->izq), obtenerAltura(n->der));
    }
}

// ============ ROTACIONES ============

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izq;
    Nodo* T2 = x->der;
    
    x->der = y;
    y->izq = T2;
    
    actualizarAltura(y);
    actualizarAltura(x);
    
    return x;
}

Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->der;
    Nodo* T2 = y->izq;
    
    y->izq = x;
    x->der = T2;
    
    actualizarAltura(x);
    actualizarAltura(y);
    
    return y;
}

// ============ BALANCEAR ============

Nodo* balancear(Nodo* nodo) {
    if (nodo == NULL) return NULL;
    
    actualizarAltura(nodo);
    int balance = calcularBalance(nodo);
    
    // Caso Izquierda-Izquierda
    if (balance > 1 && calcularBalance(nodo->izq) >= 0) {
        return rotarDerecha(nodo);
    }
    
    // Caso Izquierda-Derecha
    if (balance > 1 && calcularBalance(nodo->izq) < 0) {
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }
    
    // Caso Derecha-Derecha
    if (balance < -1 && calcularBalance(nodo->der) <= 0) {
        return rotarIzquierda(nodo);
    }
    
    // Caso Derecha-Izquierda
    if (balance < -1 && calcularBalance(nodo->der) > 0) {
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }
    
    return nodo;
}

// ============ INSERTAR (PERMITE DUPLICADOS SIN RESTRICCION) ============

Nodo* insertar(Nodo* nodo, int valor) {
    // Insercion normal BST
    if (nodo == NULL) {
        return new Nodo(valor);
    }
    
    // CLAVE: Los valores menores van a izquierda
    // Los valores MAYORES O IGUALES van a derecha (permitiendo duplicados)
    if (valor < nodo->dato) {
        nodo->izq = insertar(nodo->izq, valor);
    } else {
        // Aqui entran tanto valores mayores COMO IGUALES (duplicados)
        nodo->der = insertar(nodo->der, valor);
    }
    
    // Balancear el nodo
    return balancear(nodo);
}

// ============ BUSCAR MINIMO ============

Nodo* buscarMinimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual && actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

// ============ ELIMINAR (Una ocurrencia) ============

Nodo* eliminar(Nodo* raiz, int valor, bool& encontrado) {
    if (raiz == NULL) {
        encontrado = false;
        return NULL;
    }
    
    // Buscar el nodo
    if (valor < raiz->dato) {
        raiz->izq = eliminar(raiz->izq, valor, encontrado);
    } 
    else if (valor > raiz->dato) {
        raiz->der = eliminar(raiz->der, valor, encontrado);
    } 
    else {
        // Nodo encontrado - eliminar
        encontrado = true;
        
        if (raiz->izq == NULL || raiz->der == NULL) {
            Nodo* temp = raiz->izq ? raiz->izq : raiz->der;
            
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            delete temp;
        } 
        else {
            Nodo* temp = buscarMinimo(raiz->der);
            raiz->dato = temp->dato;
            bool aux = false;
            raiz->der = eliminar(raiz->der, temp->dato, aux);
        }
    }
    
    if (raiz == NULL) return NULL;
    
    return balancear(raiz);
}

// ============ BUSCAR (verifica existencia) ============

bool existeValor(Nodo* raiz, int valor) {
    if (raiz == NULL) return false;
    if (raiz->dato == valor) return true;
    if (valor < raiz->dato) return existeValor(raiz->izq, valor);
    return existeValor(raiz->der, valor);
}

// ============ CONTAR OCURRENCIAS ============

int contarOcurrencias(Nodo* raiz, int valor) {
    if (raiz == NULL) return 0;
    int count = 0;
    if (raiz->dato == valor) count = 1;
    count += contarOcurrencias(raiz->izq, valor);
    count += contarOcurrencias(raiz->der, valor);
    return count;
}

// ============ DIBUJAR ARBOL ============

void dibujarArbol(Nodo* raiz, int x, int y, int espaciado) {
    if (raiz == NULL) return;
    
    // Dibujar el nodo actual
    posicionar(x, y);
    cout << "[" << raiz->dato << "]";
    
    // Dibujar hijo izquierdo
    if (raiz->izq != NULL) {
        posicionar(x - espaciado/2, y + 1);
        cout << "/";
        dibujarArbol(raiz->izq, x - espaciado, y + 2, espaciado/2);
    }
    
    // Dibujar hijo derecho
    if (raiz->der != NULL) {
        posicionar(x + espaciado/2, y + 1);
        cout << "\\";
        dibujarArbol(raiz->der, x + espaciado, y + 2, espaciado/2);
    }
}

// ============ RECORRIDOS ============

void inorden(Nodo* raiz) {
    if (raiz == NULL) return;
    inorden(raiz->izq);
    cout << raiz->dato << " ";
    inorden(raiz->der);
}

void preorden(Nodo* raiz) {
    if (raiz == NULL) return;
    cout << raiz->dato << " ";
    preorden(raiz->izq);
    preorden(raiz->der);
}

void postorden(Nodo* raiz) {
    if (raiz == NULL) return;
    postorden(raiz->izq);
    postorden(raiz->der);
    cout << raiz->dato << " ";
}

// ============ CALCULOS MATEMATICOS ============

int contarNodos(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNodos(raiz->izq) + contarNodos(raiz->der);
}

int calcularAltura(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return 1 + max(calcularAltura(raiz->izq), calcularAltura(raiz->der));
}

int sumarNodos(Nodo* raiz) {
    if (raiz == NULL) return 0;
    return raiz->dato + sumarNodos(raiz->izq) + sumarNodos(raiz->der);
}

// ============ MENU PRINCIPAL ============

int main() {
    Nodo* raiz = NULL;
    int opcion, valor, nuevoValor;
    string mensaje = "";
    
    do {
        limpiarPantalla();
        
        // Titulo
        posicionar(0, 0);
        cout << "=== ARBOL AVL: PERMITE VALORES REPETIDOS ===";
        posicionar(0, 1);
        cout << "1. Insertar";
        posicionar(0, 2);
        cout << "2. Editar";
        posicionar(0, 3);
        cout << "3. Eliminar";
        posicionar(0, 4);
        cout << "4. Mostrar recorridos";
        posicionar(0, 5);
        cout << "5. Calculos matematicos";
        posicionar(0, 6);
        cout << "6. Salir";
        posicionar(0, 7);
        cout << "---------------------------------------";
        
        // Dibujar arbol
        if (raiz != NULL) {
            dibujarArbol(raiz, 40, 9, 20);
        } else {
            posicionar(0, 9);
            cout << "        (Arbol vacio)";
        }
        
        // Mensaje de estado
        posicionar(0, 20);
        cout << "---------------------------------------";
        posicionar(0, 21);
        cout << ">> ESTADO: " << mensaje;
        posicionar(0, 22);
        cout << "---------------------------------------";
        
        // Estadisticas
        posicionar(0, 23);
        cout << "Nodos totales: " << contarNodos(raiz) << " | Altura: " << calcularAltura(raiz);
        
        // Entrada
        posicionar(0, 25);
        cout << "Seleccione opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                posicionar(0, 26);
                cout << "Valor a insertar: ";
                cin >> valor;
                raiz = insertar(raiz, valor);
                mensaje = "Valor insertado correctamente.";
                break;
                
            case 2:
                posicionar(0, 26);
                cout << "Valor a editar: ";
                cin >> valor;
                
                if (existeValor(raiz, valor)) {
                    int ocurrencias = contarOcurrencias(raiz, valor);
                    posicionar(0, 27);
                    cout << "Valor encontrado (" << ocurrencias << " ocurrencia(s))";
                    posicionar(0, 28);
                    cout << "Nuevo valor: ";
                    cin >> nuevoValor;
                    
                    bool encontrado = false;
                    raiz = eliminar(raiz, valor, encontrado);
                    raiz = insertar(raiz, nuevoValor);
                    mensaje = "Valor editado (1 ocurrencia modificada).";
                } else {
                    mensaje = "ERROR: Valor no encontrado.";
                }
                break;
                
            case 3:
                posicionar(0, 26);
                cout << "Valor a eliminar: ";
                cin >> valor;
                
                if (existeValor(raiz, valor)) {
                    int ocurrencias = contarOcurrencias(raiz, valor);
                    bool encontrado = false;
                    raiz = eliminar(raiz, valor, encontrado);
                    if (encontrado) {
                        mensaje = "Valor eliminado (1 ocurrencia). Quedan " + to_string(ocurrencias - 1);
                    }
                } else {
                    mensaje = "ERROR: Valor no encontrado.";
                }
                break;
                
            case 4:
                limpiarPantalla();
                posicionar(0, 0);
                cout << "=== RECORRIDOS DEL ARBOL ===";
                
                posicionar(0, 2);
                cout << "INORDEN (Izq-Raiz-Der): ";
                inorden(raiz);
                
                posicionar(0, 4);
                cout << "PREORDEN (Raiz-Izq-Der): ";
                preorden(raiz);
                
                posicionar(0, 6);
                cout << "POSTORDEN (Izq-Der-Raiz): ";
                postorden(raiz);
                
                posicionar(0, 8);
                cout << "Presione ENTER para continuar...";
                cin.ignore();
                cin.get();
                mensaje = "Recorridos mostrados.";
                break;
                
            case 5:
                limpiarPantalla();
                posicionar(0, 0);
                cout << "=== CALCULOS MATEMATICOS ===";
                
                posicionar(0, 2);
                cout << "Total de nodos: " << contarNodos(raiz);
                
                posicionar(0, 3);
                cout << "Altura del arbol: " << calcularAltura(raiz);
                
                posicionar(0, 4);
                cout << "Suma de todos los valores: " << sumarNodos(raiz);
                
                if (contarNodos(raiz) > 0) {
                    posicionar(0, 5);
                    cout << "Promedio: " << (float)sumarNodos(raiz) / contarNodos(raiz);
                }
                
                posicionar(0, 6);
                cout << "Balance de la raiz: " << calcularBalance(raiz);
                
                posicionar(0, 8);
                cout << "Presione ENTER para continuar...";
                cin.ignore();
                cin.get();
                mensaje = "Calculos realizados.";
                break;
                
            case 6:
                mensaje = "Saliendo del programa...";
                break;
                
            default:
                mensaje = "Opcion invalida.";
        }
        
    } while(opcion != 6);
    
    limpiarPantalla();
    posicionar(0, 0);
    cout << "Gracias por usar el programa!" << endl;
    
    return 0;
}