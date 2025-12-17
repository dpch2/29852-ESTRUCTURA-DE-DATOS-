#include <iostream>
#include <conio.h>
#include <stdlib.h>

using namespace std;

// ------------------------- NODOS -------------------------

struct NodoBST {
    int clave;
    NodoBST* izquierdo;
    NodoBST* derecho;
};

struct NodoAVL {
    int clave;
    int altura;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
};

// ------------------------- FUNCIONES AUXILIARES -------------------------

int maxEntero(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int alturaNodo(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}

// ------------------------- ABB: INSERCIÓN, BÚSQUEDA, ELIMINACIÓN, IMPRESIÓN -------------------------

NodoBST* crearNodoBST(int clave) {
    NodoBST* nuevo = new NodoBST;
    nuevo->clave = clave;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}

NodoBST* insertarBST(NodoBST* raiz, int clave) {
    if (raiz == nullptr) {
        return crearNodoBST(clave);
    }
    if (clave < raiz->clave) {
        raiz->izquierdo = insertarBST(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = insertarBST(raiz->derecho, clave);
    }
    return raiz;
}

NodoBST* buscarBST(NodoBST* raiz, int clave) {
    if (raiz == nullptr) {
        return nullptr;
    }
    if (clave == raiz->clave) {
        return raiz;
    }
    if (clave < raiz->clave) {
        return buscarBST(raiz->izquierdo, clave);
    }
    return buscarBST(raiz->derecho, clave);
}

NodoBST* minimoBST(NodoBST* nodo) {
    NodoBST* actual = nodo;
    while (actual != nullptr && actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}

NodoBST* eliminarBST(NodoBST* raiz, int clave) {
    if (raiz == nullptr) {
        return nullptr;
    }

    if (clave < raiz->clave) {
        raiz->izquierdo = eliminarBST(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = eliminarBST(raiz->derecho, clave);
    } else {
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            delete raiz;
            return nullptr;
        } else if (raiz->izquierdo == nullptr) {
            NodoBST* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            NodoBST* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        } else {
            NodoBST* temp = minimoBST(raiz->derecho);
            raiz->clave = temp->clave;
            raiz->derecho = eliminarBST(raiz->derecho, temp->clave);
        }
    }
    return raiz;
}

void imprimirInordenBST(NodoBST* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirInordenBST(raiz->izquierdo);
    cout << raiz->clave << " ";
    imprimirInordenBST(raiz->derecho);
}

// ------------------------- AVL: ROTACIONES -------------------------

NodoAVL* crearNodoAVL(int clave) {
    NodoAVL* nuevo = new NodoAVL;
    nuevo->clave = clave;
    nuevo->altura = 1;
    nuevo->izquierdo = nullptr;
    nuevo->derecho = nullptr;
    return nuevo;
}

int factorEquilibrio(NodoAVL* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    int alturaIzq = alturaNodo(nodo->izquierdo);
    int alturaDer = alturaNodo(nodo->derecho);
    return alturaIzq - alturaDer;
}

NodoAVL* rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierdo;
    NodoAVL* T = x->derecho;

    x->derecho = y;
    y->izquierdo = T;

    y->altura = maxEntero(alturaNodo(y->izquierdo), alturaNodo(y->derecho)) + 1;
    x->altura = maxEntero(alturaNodo(x->izquierdo), alturaNodo(x->derecho)) + 1;

    return x;
}

NodoAVL* rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecho;
    NodoAVL* T = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T;

    x->altura = maxEntero(alturaNodo(x->izquierdo), alturaNodo(x->derecho)) + 1;
    y->altura = maxEntero(alturaNodo(y->izquierdo), alturaNodo(y->derecho)) + 1;

    return y;
}

// ------------------------- AVL: INSERCIÓN -------------------------

NodoAVL* insertarAVL(NodoAVL* raiz, int clave) {
    if (raiz == nullptr) {
        return crearNodoAVL(clave);
    }

    if (clave < raiz->clave) {
        raiz->izquierdo = insertarAVL(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = insertarAVL(raiz->derecho, clave);
    } else {
        return raiz;
    }

    raiz->altura = 1 + maxEntero(alturaNodo(raiz->izquierdo), alturaNodo(raiz->derecho));

    int balance = factorEquilibrio(raiz);

    if (balance > 1 && clave < raiz->izquierdo->clave) {
        return rotacionDerecha(raiz);
    }

    if (balance < -1 && clave > raiz->derecho->clave) {
        return rotacionIzquierda(raiz);
    }

    if (balance > 1 && clave > raiz->izquierdo->clave) {
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    if (balance < -1 && clave < raiz->derecho->clave) {
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

// ------------------------- AVL: BÚSQUEDA, MÍNIMO, ELIMINACIÓN, IMPRESIÓN -------------------------

NodoAVL* buscarAVL(NodoAVL* raiz, int clave) {
    if (raiz == nullptr) {
        return nullptr;
    }
    if (clave == raiz->clave) {
        return raiz;
    }
    if (clave < raiz->clave) {
        return buscarAVL(raiz->izquierdo, clave);
    }
    return buscarAVL(raiz->derecho, clave);
}

NodoAVL* minimoAVL(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    while (actual != nullptr && actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}

NodoAVL* eliminarAVL(NodoAVL* raiz, int clave) {
    if (raiz == nullptr) {
        return nullptr;
    }

    if (clave < raiz->clave) {
        raiz->izquierdo = eliminarAVL(raiz->izquierdo, clave);
    } else if (clave > raiz->clave) {
        raiz->derecho = eliminarAVL(raiz->derecho, clave);
    } else {
        if (raiz->izquierdo == nullptr && raiz->derecho == nullptr) {
            delete raiz;
            return nullptr;
        } else if (raiz->izquierdo == nullptr) {
            NodoAVL* temp = raiz->derecho;
            delete raiz;
            return temp;
        } else if (raiz->derecho == nullptr) {
            NodoAVL* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        } else {
            NodoAVL* temp = minimoAVL(raiz->derecho);
            raiz->clave = temp->clave;
            raiz->derecho = eliminarAVL(raiz->derecho, temp->clave);
        }
    }

    if (raiz == nullptr) {
        return nullptr;
    }

    raiz->altura = 1 + maxEntero(alturaNodo(raiz->izquierdo), alturaNodo(raiz->derecho));

    int balance = factorEquilibrio(raiz);

    if (balance > 1 && factorEquilibrio(raiz->izquierdo) >= 0) {
        return rotacionDerecha(raiz);
    }

    if (balance > 1 && factorEquilibrio(raiz->izquierdo) < 0) {
        raiz->izquierdo = rotacionIzquierda(raiz->izquierdo);
        return rotacionDerecha(raiz);
    }

    if (balance < -1 && factorEquilibrio(raiz->derecho) <= 0) {
        return rotacionIzquierda(raiz);
    }

    if (balance < -1 && factorEquilibrio(raiz->derecho) > 0) {
        raiz->derecho = rotacionDerecha(raiz->derecho);
        return rotacionIzquierda(raiz);
    }

    return raiz;
}

void imprimirInordenAVL(NodoAVL* raiz) {
    if (raiz == nullptr) {
        return;
    }
    imprimirInordenAVL(raiz->izquierdo);
    cout << raiz->clave << " ";
    imprimirInordenAVL(raiz->derecho);
}

// ------------------------- MENÚ TIPO 2 (CON FLECHAS) -------------------------

int menuConFlechas(const char* titulo, const char* op1, const char* op2, const char* op3, const char* op4, const char* op5) {
    int opcion = 0;
    int tecla = 0;
    int total = 5;

    while (true) {
        system("cls");
        cout << titulo << "\n\n";

        cout << (opcion == 0 ? " -> " : "    ") << op1 << "\n";
        cout << (opcion == 1 ? " -> " : "    ") << op2 << "\n";
        cout << (opcion == 2 ? " -> " : "    ") << op3 << "\n";
        cout << (opcion == 3 ? " -> " : "    ") << op4 << "\n";
        cout << (opcion == 4 ? " -> " : "    ") << op5 << "\n";

        tecla = getch();

        if (tecla == 72) {
            if (opcion > 0) {
                opcion = opcion - 1;
            } else {
                opcion = total - 1;
            }
        } else if (tecla == 80) {
            if (opcion < total - 1) {
                opcion = opcion + 1;
            } else {
                opcion = 0;
            }
        } else if (tecla == 13) {
            return opcion;
        }
    }
}

// ------------------------- SUBMENÚS -------------------------

void menuBST(NodoBST*& raizBST) {
    bool salir = false;

    while (!salir) {
        int opcion = menuConFlechas(
            "MENU ARBOL DE BUSQUEDA BINARIA",
            "Insertar",
            "Buscar",
            "Eliminar",
            "Imprimir inorden",
            "Regresar al menu principal"
        );

        int valor;
        NodoBST* resultado;

        switch (opcion) {
            case 0:
                system("cls");
                cout << "Insercion en ABB\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                raizBST = insertarBST(raizBST, valor);
                cout << "Insertado.\n";
                system("pause");
                break;

            case 1:
                system("cls");
                cout << "Busqueda en ABB\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                resultado = buscarBST(raizBST, valor);
                if (resultado != nullptr) {
                    cout << "Elemento encontrado.\n";
                } else {
                    cout << "Elemento no encontrado.\n";
                }
                system("pause");
                break;

            case 2:
                system("cls");
                cout << "Eliminacion en ABB\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                raizBST = eliminarBST(raizBST, valor);
                cout << "Eliminado si existia.\n";
                system("pause");
                break;

            case 3:
                system("cls");
                cout << "Impresion inorden ABB\n\n";
                imprimirInordenBST(raizBST);
                cout << "\n";
                system("pause");
                break;

            case 4:
                salir = true;
                break;
        }
    }
}

void menuAVL(NodoAVL*& raizAVL) {
    bool salir = false;

    while (!salir) {
        int opcion = menuConFlechas(
            "MENU ARBOL AVL",
            "Insertar",
            "Buscar",
            "Eliminar",
            "Imprimir inorden",
            "Regresar al menu principal"
        );

        int valor;
        NodoAVL* resultado;

        switch (opcion) {
            case 0:
                system("cls");
                cout << "Insercion en AVL\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                raizAVL = insertarAVL(raizAVL, valor);
                cout << "Insertado.\n";
                system("pause");
                break;

            case 1:
                system("cls");
                cout << "Busqueda en AVL\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                resultado = buscarAVL(raizAVL, valor);
                if (resultado != nullptr) {
                    cout << "Elemento encontrado.\n";
                } else {
                    cout << "Elemento no encontrado.\n";
                }
                system("pause");
                break;

            case 2:
                system("cls");
                cout << "Eliminacion en AVL\n\n";
                cout << "Ingrese un entero: ";
                cin >> valor;
                raizAVL = eliminarAVL(raizAVL, valor);
                cout << "Eliminado si existia.\n";
                system("pause");
                break;

            case 3:
                system("cls");
                cout << "Impresion inorden AVL\n\n";
                imprimirInordenAVL(raizAVL);
                cout << "\n";
                system("pause");
                break;

            case 4:
                salir = true;
                break;
        }
    }
}

// ------------------------- MENU PRINCIPAL -------------------------

int main() {
    NodoBST* raizBST = nullptr;
    NodoAVL* raizAVL = nullptr;

    bool salir = false;

    while (!salir) {
        int opcion = menuConFlechas(
            "MENU PRINCIPAL",
            "Trabajar con ABB",
            "Trabajar con AVL",
            "Imprimir ambos inorden",
            "Salir del programa",
            "Salir del programa"
        );

        switch (opcion) {
            case 0:
                menuBST(raizBST);
                break;
            case 1:
                menuAVL(raizAVL);
                break;
            case 2:
                system("cls");
                cout << "ABB inorden: ";
                imprimirInordenBST(raizBST);
                cout << "\nAVL inorden: ";
                imprimirInordenAVL(raizAVL);
                cout << "\n";
                system("pause");
                break;
            case 3:
            case 4:
                salir = true;
                break;
        }
    }

    return 0;
}
