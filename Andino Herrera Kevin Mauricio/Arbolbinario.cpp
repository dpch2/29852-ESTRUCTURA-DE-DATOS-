#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* izquierda;
    Nodo* derecha;
};

// --- Funciones Básicas ---

Nodo* crearNodo(int valor) {
    Nodo* nuevoNodo = new Nodo();
    nuevoNodo->dato = valor;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

void insertar(Nodo*& raiz, int valor) {
    if (raiz == NULL) {
        raiz = crearNodo(valor);
        cout << ">> Insertado: " << valor << "\n";
    }
    else if (valor < raiz->dato) {
        insertar(raiz->izquierda, valor);
    }
    else if (valor > raiz->dato) {
        insertar(raiz->derecha, valor);
    }
    else {
        cout << ">> El valor ya existe.\n";
    }
}

bool buscar(Nodo* raiz, int valor) {
    if (raiz == NULL) return false;
    if (raiz->dato == valor) return true;
    if (valor < raiz->dato) return buscar(raiz->izquierda, valor);
    return buscar(raiz->derecha, valor);
}

// --- NUEVA FUNCIÓN: Calcular Altura ---
// Retorna la cantidad de niveles (Profundidad máxima)
int calcularAltura(Nodo* raiz) {
    if (raiz == NULL) {
        return 0; // Si no hay nodo, altura es 0
    } else {
        int alturaIzq = calcularAltura(raiz->izquierda);
        int alturaDer = calcularAltura(raiz->derecha);
        
        // Retornamos la mayor altura + 1 (por el nodo actual)
        if (alturaIzq > alturaDer) {
            return alturaIzq + 1;
        } else {
            return alturaDer + 1;
        }
    }
}

// --- Funciones de Visualización ---

void mostrarDetalle(Nodo* raiz) {
    if (raiz == NULL) return;
    cout << "Nodo " << raiz->dato << ": ";
    
    if (raiz->izquierda) cout << "[Izq: " << raiz->izquierda->dato << "] ";
    else cout << "[Izq: VACIO] ";
    
    if (raiz->derecha) cout << "[Der: " << raiz->derecha->dato << "]";
    else cout << "[Der: VACIO]";
    
    cout << "\n";
    
    mostrarDetalle(raiz->izquierda);
    mostrarDetalle(raiz->derecha);
}

void mostrarGrafico(Nodo* raiz, int espacio) {
    if (raiz == NULL) return;
    int DISTANCIA = 5;
    espacio += DISTANCIA;
    mostrarGrafico(raiz->derecha, espacio);
    cout << endl;
    for (int i = DISTANCIA; i < espacio; i++) cout << " ";
    cout << raiz->dato << "\n";
    mostrarGrafico(raiz->izquierda, espacio);
}

// --- Funciones de Eliminación ---

Nodo* encontrarMinimo(Nodo* raiz) {
    while (raiz && raiz->izquierda != NULL) raiz = raiz->izquierda;
    return raiz;
}

Nodo* eliminar(Nodo* raiz, int valor) {
    if (raiz == NULL) return raiz;
    if (valor < raiz->dato) raiz->izquierda = eliminar(raiz->izquierda, valor);
    else if (valor > raiz->dato) raiz->derecha = eliminar(raiz->derecha, valor);
    else {
        if (raiz->izquierda == NULL && raiz->derecha == NULL) {
            delete raiz; raiz = NULL;
        }
        else if (raiz->izquierda == NULL) {
            Nodo* temp = raiz; raiz = raiz->derecha; delete temp;
        }
        else if (raiz->derecha == NULL) {
            Nodo* temp = raiz; raiz = raiz->izquierda; delete temp;
        }
        else {
            Nodo* temp = encontrarMinimo(raiz->derecha);
            raiz->dato = temp->dato;
            raiz->derecha = eliminar(raiz->derecha, temp->dato);
        }
    }
    return raiz;
}

// --- MAIN COMPLETO ---

int main() {
    Nodo* raiz = NULL;
    int opcion, valor;

    do {
        cout << "\n----------------------------\n";
        cout << "   ARBOL BINARIO COMPLETO\n";
        cout << "----------------------------\n";
        cout << "1. Insertar\n";
        cout << "2. Eliminar\n";
        cout << "3. Buscar\n";
        cout << "4. Ver Detalle (Izq/Der)\n";
        cout << "5. Ver Grafico (Visual)\n";
        cout << "6. Ver Altura del Arbol\n"; // NUEVA OPCIÓN
        cout << "7. Salir\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Numero: "; cin >> valor;
            insertar(raiz, valor);
            break;
        case 2:
            cout << "Numero a borrar: "; cin >> valor;
            if (buscar(raiz, valor)) {
                raiz = eliminar(raiz, valor);
                cout << "Eliminado.\n";
            } else cout << "No encontrado.\n";
            break;
        case 3:
            cout << "Numero a buscar: "; cin >> valor;
            if (buscar(raiz, valor)) cout << "Encontrado.\n";
            else cout << "No existe.\n";
            break;
        case 4:
            cout << "\n--- RELACIONES ---\n";
            if (raiz == NULL) cout << "(Vacio)\n";
            else mostrarDetalle(raiz);
            break;
        case 5:
             cout << "\n--- GRAFICO  ---\n";
             mostrarGrafico(raiz, 0);
             break;
        case 6:
             // Llamada a la nueva función
             cout << "\n>>> La altura (niveles maximos) es: " << calcularAltura(raiz) << "\n";
             break;
        case 7:
            cout << "Cerrando programa...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 7);

    return 0;
}