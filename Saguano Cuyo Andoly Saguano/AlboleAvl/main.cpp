#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;
};

// --- ALTURA ---
int altura(Nodo* n) {
    return (n == nullptr) ? 0 : n->altura;
}

// --- CREAR NODO ---
Nodo* crearNodo(int dato) {
    Nodo* n = new Nodo();
    n->dato = dato;
    n->izquierda = nullptr;
    n->derecha = nullptr;
    n->altura = 1;
    return n;
}

// --- FACTOR DE BALANCE ---
int balance(Nodo* n) {
    if (n == nullptr) return 0;
    return altura(n->izquierda) - altura(n->derecha);
}

// --- ROTACIÓN DERECHA ---
Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

    return x;
}

// --- ROTACIÓN IZQUIERDA ---
Nodo* rotarIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
    y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

    return y;
}

// --- INSERTAR EN AVL ---
Nodo* insertarAVL(Nodo* raiz, int dato) {
    // Inserción normal BST
    if (raiz == nullptr)
        return crearNodo(dato);

    if (dato < raiz->dato)
        raiz->izquierda = insertarAVL(raiz->izquierda, dato);
    else if (dato > raiz->dato)
        raiz->derecha = insertarAVL(raiz->derecha, dato);
    else
        return raiz; // no permitir duplicados

    // Actualizar altura
    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));

    // Balancear
    int b = balance(raiz);

    // Caso IZQ-IZQ
    if (b > 1 && dato < raiz->izquierda->dato)
        return rotarDerecha(raiz);

    // Caso DER-DER
    if (b < -1 && dato > raiz->derecha->dato)
        return rotarIzquierda(raiz);

    // Caso IZQ-DER
    if (b > 1 && dato > raiz->izquierda->dato) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // Caso DER-IZQ
    if (b < -1 && dato < raiz->derecha->dato) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

// --- BUSCAR ---
bool buscar(Nodo* raiz, int clave) {
    if (raiz == nullptr) return false;
    if (clave == raiz->dato) return true;
    if (clave < raiz->dato) return buscar(raiz->izquierda,clave);
    return buscar(raiz->derecha, clave);
}

// --- MÍNIMO (para eliminar) ---
Nodo* minimo(Nodo* nodo) {
    Nodo* actual = nodo;
    while (actual->izquierda != nullptr)
        actual = actual->izquierda;
    return actual;
}

// --- ELIMINAR ---
Nodo* eliminarAVL(Nodo* raiz, int clave) {
    if (raiz == nullptr)
        return raiz;

    // Búsqueda normal de BST
    if (clave < raiz->dato)
        raiz->izquierda = eliminarAVL(raiz->izquierda, clave);
    else if (clave > raiz->dato)
        raiz->derecha = eliminarAVL(raiz->derecha, clave);
    else {
        // Nodo con 0 o 1 hijo
        if (raiz->izquierda == nullptr || raiz->derecha == nullptr) {
            Nodo* temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;

            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp; // Copiar contenido
            }
            delete temp;
        }
        else {
            // 2 hijos → sucesor
            Nodo* temp = minimo(raiz->derecha);
            raiz->dato = temp->dato;
            raiz->derecha = eliminarAVL(raiz->derecha, temp->dato);
        }
    }

    // Si el árbol quedó vacío
    if (raiz == nullptr) return raiz;

    // Actualizar altura
    raiz->altura = 1 + max(altura(raiz->izquierda), altura(raiz->derecha));

    // Balancear
    int b = balance(raiz);

    // IZQ-IZQ
    if (b > 1 && balance(raiz->izquierda) >= 0)
        return rotarDerecha(raiz);

    // IZQ-DER
    if (b > 1 && balance(raiz->izquierda) < 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // DER-DER
    if (b < -1 && balance(raiz->derecha) <= 0)
        return rotarIzquierda(raiz);

    // DER-IZQ
    if (b < -1 && balance(raiz->derecha) > 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

// --- RECORRIDOS ---
void inOrden(Nodo* raiz) {
    if (raiz == nullptr) return;
    inOrden(raiz->izquierda);
    cout << raiz->dato << " ";
    inOrden(raiz->derecha);
}

void preOrden(Nodo* raiz) {
    if (raiz == nullptr) return;
    cout << raiz->dato << " ";
    preOrden(raiz->izquierda);
    preOrden(raiz->derecha);
}

void postOrden(Nodo* raiz) {
    if (raiz == nullptr) return;
    postOrden(raiz->izquierda);
    postOrden(raiz->derecha);
    cout << raiz->dato << " ";
}

// --- MAIN ---
int main() {
    Nodo* raiz = nullptr;
    int opcion, valor;

    do {
        cout << "\n--- ARBOL AVL ---\n";
        cout << "1. Insertar\n";
        cout << "2. Buscar\n";
        cout << "3. Eliminar\n";
        cout << "4. Mostrar Inorden\n";
        cout << "5. Mostrar Preorden\n";
        cout << "6. Mostrar Postorden\n";
        cout << "7. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Valor a insertar: ";
                cin >> valor;
                raiz = insertarAVL(raiz, valor);
                break;

            case 2:
                cout << "Valor a buscar: ";
                cin >> valor;
                if (buscar(raiz, valor))
                    cout << "El valor SI existe\n";
                else
                    cout << "El valor NO existe\n";
                break;

            case 3:
                cout << "Valor a eliminar: ";
                cin >> valor;
                raiz = eliminarAVL(raiz, valor);
                break;

            case 4:
                cout << "Inorden: ";
                inOrden(raiz);
                cout << endl;
                break;

            case 5:
                cout << "Preorden: ";
                preOrden(raiz);
                cout << endl;
                break;

            case 6:
                cout << "Postorden: ";
                postOrden(raiz);
                cout << endl;
                break;
        }

    } while (opcion != 7);

    return 0;
}
