#include "ArbolBMas.hpp"
#include <iostream>

template<typename T>
ArbolBMas<T>::ArbolBMas(int orden) {
    this->raiz = nullptr;
    this->orden = orden;
}

template<typename T>
ArbolBMas<T>::~ArbolBMas() {
    // Implementación simple de destructor (idealmente recursivo)
    // Aquí se omite por brevedad, pero debería eliminar todos los nodos.
}

// Busca el nodo hoja donde debería estar la clave
template<typename T>
NodoB<T>* ArbolBMas<T>::buscarHoja(T clave) {
    if (raiz == nullptr) return nullptr;
    
    NodoB<T>* cursor = raiz;
    while (!cursor->esHoja) {
        int i = 0;
        while (i < cursor->n && clave >= cursor->claves[i]) {
            i++;
        }
        cursor = cursor->hijos[i];
    }
    return cursor;
}

template<typename T>
bool ArbolBMas<T>::buscar(T clave) {
    if (raiz == nullptr) return false;
    NodoB<T>* hoja = buscarHoja(clave);
    
    for (int i = 0; i < hoja->n; i++) {
        if (hoja->claves[i] == clave) return true;
    }
    return false;
}

template<typename T>
void ArbolBMas<T>::insertar(T clave) {
    // 1. Si el árbol está vacío
    if (raiz == nullptr) {
        raiz = new NodoB<T>(orden, true);
        raiz->claves[0] = clave;
        raiz->n = 1;
        return;
    }

    // 2. Buscar la hoja adecuada
    NodoB<T>* hoja = buscarHoja(clave);

    // 3. Insertar ordenado en la hoja
    if (hoja->n < orden - 1) {
        int i = 0;
        while (i < hoja->n && clave > hoja->claves[i]) i++;
        
        for (int j = hoja->n; j > i; j--) {
            hoja->claves[j] = hoja->claves[j - 1];
        }
        hoja->claves[i] = clave;
        hoja->n++;
    } else {
        // 4. La hoja está llena, dividir (Split)
        NodoB<T>* nuevaHoja = new NodoB<T>(orden, true);
        T buffer[orden + 1]; // Buffer temporal
        
        int i = 0;
        while (i < orden - 1 && clave > hoja->claves[i]) i++;
        
        // Copiar claves al buffer insertando la nueva
        for(int j=0; j<i; j++) buffer[j] = hoja->claves[j];
        buffer[i] = clave;
        for(int j=i; j<orden-1; j++) buffer[j+1] = hoja->claves[j];

        // Distribuir claves
        hoja->n = (orden) / 2;
        nuevaHoja->n = orden - (orden) / 2;

        for(int j=0; j<hoja->n; j++) hoja->claves[j] = buffer[j];
        for(int j=0; j<nuevaHoja->n; j++) nuevaHoja->claves[j] = buffer[j + hoja->n];

        // Enlazar hojas
        nuevaHoja->siguiente = hoja->siguiente;
        hoja->siguiente = nuevaHoja;

        // Insertar la clave media en el padre
        insertarEnPadre(hoja, nuevaHoja->claves[0], nuevaHoja);
    }
}

template<typename T>
void ArbolBMas<T>::insertarEnPadre(NodoB<T>* n, T clave, NodoB<T>* nuevoNodo) {
    if (n == raiz) {
        NodoB<T>* nuevaRaiz = new NodoB<T>(orden, false);
        nuevaRaiz->claves[0] = clave;
        nuevaRaiz->hijos[0] = n;
        nuevaRaiz->hijos[1] = nuevoNodo;
        nuevaRaiz->n = 1;
        raiz = nuevaRaiz;
        return;
    }

    NodoB<T>* padre = encontrarPadre(raiz, n);
    
    if (padre->n < orden - 1) {
        int i = 0;
        while (i < padre->n && clave > padre->claves[i]) i++;
        
        for (int j = padre->n; j > i; j--) {
            padre->claves[j] = padre->claves[j - 1];
            padre->hijos[j + 1] = padre->hijos[j];
        }
        padre->claves[i] = clave;
        padre->hijos[i + 1] = nuevoNodo;
        padre->n++;
    } else {
        // División de nodo interno
        NodoB<T>* nuevoInterno = new NodoB<T>(orden, false);
        T bufferClaves[orden + 1];
        NodoB<T>* bufferHijos[orden + 2];

        int i = 0;
        while (i < padre->n && clave > padre->claves[i]) i++;

        // Copiar datos al buffer
        for(int j=0; j<i; j++) bufferClaves[j] = padre->claves[j];
        bufferClaves[i] = clave;
        for(int j=i; j<padre->n; j++) bufferClaves[j+1] = padre->claves[j];

        for(int j=0; j<=i; j++) bufferHijos[j] = padre->hijos[j];
        bufferHijos[i+1] = nuevoNodo;
        for(int j=i+1; j<=padre->n; j++) bufferHijos[j+1] = padre->hijos[j];

        // Dividir
        int splitIndex = orden / 2; // Índice de la clave que sube
        T claveArriba = bufferClaves[splitIndex];

        padre->n = splitIndex;
        nuevoInterno->n = orden - splitIndex - 1; // -1 porque una clave sube

        for(int j=0; j<padre->n; j++) padre->claves[j] = bufferClaves[j];
        for(int j=0; j<=padre->n; j++) padre->hijos[j] = bufferHijos[j];

        for(int j=0; j<nuevoInterno->n; j++) nuevoInterno->claves[j] = bufferClaves[j + splitIndex + 1];
        for(int j=0; j<=nuevoInterno->n; j++) nuevoInterno->hijos[j] = bufferHijos[j + splitIndex + 1];

        insertarEnPadre(padre, claveArriba, nuevoInterno);
    }
}

template<typename T>
NodoB<T>* ArbolBMas<T>::encontrarPadre(NodoB<T>* cursor, NodoB<T>* hijo) {
    if (cursor->esHoja || cursor->hijos[0]->esHoja) {
        // Si los hijos son hojas, verificamos si alguno es el hijo buscado
        // Pero en B+, navegamos por claves.
        // Manera simple: recorrer hijos
        for(int i=0; i<=cursor->n; i++){
            if(cursor->hijos[i] == hijo) return cursor;
        }
    }
    
    // Navegación estándar
    if (cursor->esHoja) return nullptr;

    for (int i = 0; i <= cursor->n; i++) {
        if (cursor->hijos[i] == hijo) return cursor; // Encontrado directo
        
        // Si no, buscar recursivamente en el hijo adecuado
        // Nota: Esta lógica simplificada asume que podemos bajar. 
        // Para una implementación robusta de encontrarPadre se suele usar la clave del hijo.
        T claveHijo = hijo->claves[0];
        if (i == cursor->n || claveHijo < cursor->claves[i]) {
             NodoB<T>* res = encontrarPadre(cursor->hijos[i], hijo);
             if(res != nullptr) return res;
        }
    }
    return nullptr;
}

template<typename T>
void ArbolBMas<T>::imprimirListaEnlazada() {
    NodoB<T>* cursor = raiz;
    if(cursor == nullptr) return;
    while(!cursor->esHoja) cursor = cursor->hijos[0];

    std::cout << "Lista de Hojas: ";
    while(cursor != nullptr){
        for(int i=0; i<cursor->n; i++) std::cout << cursor->claves[i] << " ";
        std::cout << " -> ";
        cursor = cursor->siguiente;
    }
    std::cout << "NULL" << std::endl;
}

template<typename T>
void ArbolBMas<T>::imprimir() {
    imprimirListaEnlazada();
}

// Eliminación básica en B+ (maneja borrado en hojas, préstamo y fusión simple)
template<typename T>
void ArbolBMas<T>::eliminar(T clave) {
    if (raiz == nullptr) return;
    NodoB<T>* hoja = buscarHoja(clave);
    if (hoja == nullptr) return;

    // Buscar la clave en la hoja
    int pos = -1;
    for (int i = 0; i < hoja->n; ++i) {
        if (hoja->claves[i] == clave) { pos = i; break; }
    }
    if (pos == -1) return; // no encontrada

    // Eliminar de la hoja
    for (int i = pos; i < hoja->n - 1; ++i) hoja->claves[i] = hoja->claves[i+1];
    hoja->n--;

    // Si la hoja es la raíz, manejamos caso simple
    if (hoja == raiz) {
        if (hoja->n == 0) { delete raiz; raiz = nullptr; }
        return;
    }

    int minKeys = orden / 2; // umbral mínimo aproximado

    if (hoja->n >= minKeys) return; // no hay bajo-llenado

    // Encontrar padre y el índice de la hoja
    NodoB<T>* padre = encontrarPadre(raiz, hoja);
    if (!padre) return;
    int idx = 0;
    while (idx <= padre->n && padre->hijos[idx] != hoja) ++idx;

    // Intentar pedir prestado del hermano izquierdo
    if (idx - 1 >= 0) {
        NodoB<T>* izq = padre->hijos[idx - 1];
        if (izq->n > minKeys) {
            // mover última clave de izq al inicio de hoja
            for (int j = hoja->n; j > 0; --j) hoja->claves[j] = hoja->claves[j-1];
            hoja->claves[0] = izq->claves[izq->n - 1];
            hoja->n++;
            izq->n--;
            // actualizar separador en padre
            padre->claves[idx - 1] = hoja->claves[0];
            std::cout << "Redistribucion: prestado de hermano izquierdo\n";
            return;
        }
    }

    // Intentar pedir prestado del hermano derecho
    if (idx + 1 <= padre->n) {
        NodoB<T>* der = padre->hijos[idx + 1];
        if (der->n > minKeys) {
            // mover primera clave de der al final de hoja
            hoja->claves[hoja->n++] = der->claves[0];
            for (int j = 0; j < der->n - 1; ++j) der->claves[j] = der->claves[j+1];
            der->n--;
            padre->claves[idx] = der->claves[0];
            std::cout << "Redistribucion: prestado de hermano derecho\n";
            return;
        }
    }

    // Si no puede pedir prestado, fusionar
    if (idx - 1 >= 0) {
        // fusionar con izquierdo
        NodoB<T>* izq = padre->hijos[idx - 1];
        // copiar claves de hoja a izq
        for (int j = 0; j < hoja->n; ++j) izq->claves[izq->n + j] = hoja->claves[j];
        izq->n += hoja->n;
        izq->siguiente = hoja->siguiente;

        // eliminar hijo derecho (hoja) del padre
        for (int j = idx; j < padre->n; ++j) {
            padre->claves[j-1] = padre->claves[j];
            padre->hijos[j] = padre->hijos[j+1];
        }
        padre->hijos[padre->n] = nullptr;
        padre->n--;
        delete hoja;
        std::cout << "Fusion: hoja fusionada con hermano izquierdo\n";
    } else {
        // fusionar con derecho
        NodoB<T>* der = padre->hijos[idx + 1];
        for (int j = 0; j < der->n; ++j) hoja->claves[hoja->n + j] = der->claves[j];
        hoja->n += der->n;
        hoja->siguiente = der->siguiente;

        // eliminar hijo derecho (der) del padre
        for (int j = idx + 1; j < padre->n; ++j) {
            padre->claves[j-1] = padre->claves[j];
            padre->hijos[j] = padre->hijos[j+1];
        }
        padre->hijos[padre->n] = nullptr;
        padre->n--;
        delete der;
        std::cout << "Fusion: hoja fusionada con hermano derecho\n";
    }

    // Si padre queda vacío y es raíz, promover primer hijo
    if (padre == raiz && padre->n == 0) {
        NodoB<T>* nuevaRaiz = padre->hijos[0];
        raiz = nuevaRaiz;
        delete padre;
    }
}