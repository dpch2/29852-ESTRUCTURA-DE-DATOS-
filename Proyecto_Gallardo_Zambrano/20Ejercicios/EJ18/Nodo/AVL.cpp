#include "AVL.hpp"
#include <iostream>

template<typename T>
AVL<T>::AVL() {
    raiz = nullptr;
}

template<typename T>
int AVL<T>::obtenerAltura(NodoAVL<T>* nodo) {
    if (nodo == nullptr) return 0;
    return nodo->getAltura();
}

template<typename T>
int AVL<T>::maximo(int a, int b) {
    return (a > b) ? a : b;
}

template<typename T>
int AVL<T>::obtenerBalance(NodoAVL<T>* nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAltura(nodo->getIzquierda()) - obtenerAltura(nodo->getDerecha());
}

// Rotación a la derecha (Caso Izquierda-Izquierda)
template<typename T>
NodoAVL<T>* AVL<T>::rotacionDerecha(NodoAVL<T>* y) {
    NodoAVL<T>* x = y->getIzquierda();
    NodoAVL<T>* T2 = x->getDerecha();

    // Realizar rotación
    x->setDerecha(y);
    y->setIzquierda(T2);

    // Actualizar alturas
    y->setAltura(maximo(obtenerAltura(y->getIzquierda()), obtenerAltura(y->getDerecha())) + 1);
    x->setAltura(maximo(obtenerAltura(x->getIzquierda()), obtenerAltura(x->getDerecha())) + 1);

    // Retornar nueva raíz
    return x;
}

// Rotación a la izquierda (Caso Derecha-Derecha)
template<typename T>
NodoAVL<T>* AVL<T>::rotacionIzquierda(NodoAVL<T>* x) {
    NodoAVL<T>* y = x->getDerecha();
    NodoAVL<T>* T2 = y->getIzquierda();

    // Realizar rotación
    y->setIzquierda(x);
    x->setDerecha(T2);

    // Actualizar alturas
    x->setAltura(maximo(obtenerAltura(x->getIzquierda()), obtenerAltura(x->getDerecha())) + 1);
    y->setAltura(maximo(obtenerAltura(y->getIzquierda()), obtenerAltura(y->getDerecha())) + 1);

    // Retornar nueva raíz
    return y;
}

template<typename T>
void AVL<T>::insertar(T dato) {
    raiz = insertarAux(raiz, dato);
}

template<typename T>
NodoAVL<T>* AVL<T>::insertarAux(NodoAVL<T>* nodo, T dato) {
    // 1. Inserción normal de BST
    if (nodo == nullptr)
        return new NodoAVL<T>(dato);

    if (dato < nodo->getDato())
        nodo->setIzquierda(insertarAux(nodo->getIzquierda(), dato));
    else if (dato > nodo->getDato())
        nodo->setDerecha(insertarAux(nodo->getDerecha(), dato));
    else // Claves duplicadas no permitidas
        return nodo;

    // 2. Actualizar altura de este nodo ancestro
    nodo->setAltura(1 + maximo(obtenerAltura(nodo->getIzquierda()), obtenerAltura(nodo->getDerecha())));

    // 3. Obtener el factor de balance para verificar si se desbalanceó
    int balance = obtenerBalance(nodo);

    // 4. Casos de rotación

    // Caso Izquierda Izquierda
    if (balance > 1 && dato < nodo->getIzquierda()->getDato())
        return rotacionDerecha(nodo);

    // Caso Derecha Derecha
    if (balance < -1 && dato > nodo->getDerecha()->getDato())
        return rotacionIzquierda(nodo);

    // Caso Izquierda Derecha
    if (balance > 1 && dato > nodo->getIzquierda()->getDato()) {
        nodo->setIzquierda(rotacionIzquierda(nodo->getIzquierda()));
        return rotacionDerecha(nodo);
    }

    // Caso Derecha Izquierda
    if (balance < -1 && dato < nodo->getDerecha()->getDato()) {
        nodo->setDerecha(rotacionDerecha(nodo->getDerecha()));
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

template<typename T>
void AVL<T>::inorden() {
    inordenAux(raiz);
    std::cout << std::endl;
}

template<typename T>
void AVL<T>::inordenAux(NodoAVL<T>* nodo) {
    if (nodo != nullptr) {
        inordenAux(nodo->getIzquierda());
        std::cout << nodo->getDato() << " ";
        inordenAux(nodo->getDerecha());
    }
}