#include "NodoB.hpp"

template<typename T>
NodoB<T>::NodoB(int orden, bool esHoja) {
    this->orden = orden;
    this->esHoja = esHoja;
    this->n = 0;
    this->siguiente = nullptr;

    // Reservamos espacio. 
    // Nota: A veces se reserva orden+1 para facilitar la división temporal.
    this->claves = new T[orden]; 
    this->hijos = new NodoB*[orden + 1];

    for (int i = 0; i <= orden; i++) {
        hijos[i] = nullptr;
    }
}

template<typename T>
NodoB<T>::~NodoB() {
    delete[] claves;
    delete[] hijos;
}

template<typename T>
T NodoB<T>::getClave(int index) const {
    return claves[index];
}

template<typename T>
void NodoB<T>::setClave(int index, T valor) {
    claves[index] = valor;
}

template<typename T>
NodoB<T>* NodoB<T>::getHijo(int index) const {
    return hijos[index];
}

template<typename T>
void NodoB<T>::setHijo(int index, NodoB<T>* nodo) {
    hijos[index] = nodo;
}

template<typename T>
NodoB<T>* NodoB<T>::getSiguiente() const {
    return siguiente;
}

template<typename T>
void NodoB<T>::setSiguiente(NodoB<T>* nodo) {
    siguiente = nodo;
}

template<typename T>
int NodoB<T>::getN() const { return n; }

template<typename T>
void NodoB<T>::setN(int val) { n = val; }

template<typename T>
bool NodoB<T>::getEsHoja() const { return esHoja; }