#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izq;
    Nodo* der;
    Nodo(int x) : dato(x), izq(NULL), der(NULL) {}
};

// INSERTAR

Nodo* insertar(Nodo* r, int x) {
    if (r == NULL) return new Nodo(x);
    if (x < r->dato) r->izq = insertar(r->izq, x);
    else if (x > r->dato) r->der = insertar(r->der, x);
    return r;
}


// BUSCAR

bool buscar(Nodo* r, int x) {
    if (!r) return false;
    if (x == r->dato) return true;
    if (x < r->dato) return buscar(r->izq, x);
    return buscar(r->der, x);
}


// MÍNIMO (para eliminar)

Nodo* minimo(Nodo* r) {
    while (r->izq) r = r->izq;
    return r;
}


// ELIMINAR

Nodo* eliminarNodo(Nodo* r, int x) {
    if (!r) return r;

    if (x < r->dato) r->izq = eliminarNodo(r->izq, x);
    else if (x > r->dato) r->der = eliminarNodo(r->der, x);
    else {
        if (!r->izq && !r->der) { delete r; return NULL; }
        else if (!r->izq) { Nodo* t = r->der; delete r; return t; }
        else if (!r->der) { Nodo* t = r->izq; delete r; return t; }
        Nodo* t = minimo(r->der);
        r->dato = t->dato;
        r->der = eliminarNodo(r->der, t->dato);
    }
    return r;
}

// MOSTRAR ARBOL (HORIZONTAL ASCII)

void mostrarHorizontal(Nodo* r, string prefijo = "", bool esIzq = false) {
    if (r == NULL) return;

    if (r->der)
        mostrarHorizontal(r->der, prefijo + (esIzq ? "│   " : "    "), false);

    cout << prefijo;

    if (esIzq)
        cout << "└── ";
    else
        cout << "┌── ";

    cout << r->dato << endl;

    if (r->izq)
        mostrarHorizontal(r->izq, prefijo + (esIzq ? "    " : "│   "), true);
}


// MENÚ

int main() {
    Nodo* raiz = NULL;
    int opc, x;

    do {
        cout << "\n===== ARBOL BINARIO (BST) =====\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
        cout << "3. Eliminar\n";
        cout << "4. Mostrar arbol (horizontal)\n";
        cout << "5. Salir\n";
        cout << "Seleccione: ";
        cin >> opc;

        switch (opc) {
        case 1:
            cout << "Valor a insertar: ";
            cin >> x;
            raiz = insertar(raiz, x);
            break;

        case 2:
            cout << "Valor a buscar: ";
            cin >> x;
            cout << (buscar(raiz, x) ? "Encontrado\n" : "NO encontrado\n");
            break;

        case 3:
            cout << "Valor a eliminar: ";
            cin >> x;
            raiz = eliminarNodo(raiz, x);
            break;

        case 4:
            cout << "\n=== ARBOL (HORIZONTAL) ===\n";
            mostrarHorizontal(raiz);
            cout << "==========================\n";
            break;
        }

    } while (opc != 5);

    return 0;
}
