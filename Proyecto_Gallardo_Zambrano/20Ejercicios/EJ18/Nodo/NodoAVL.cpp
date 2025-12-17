#include "NodoAVL.hpp"

template<typename T>
NodoAVL<T>::NodoAVL(T dato) {
    this->dato = dato;
    this->izquierda = nullptr;
    this->derecha = nullptr;
    this->altura = 1; // Un nodo nuevo es una hoja, altura 1
}

template<typename T>
NodoAVL<T>::~NodoAVL() {
    // El destructor del árbol se encargará de la memoria recursivamente si es necesario
}

template<typename T>
T NodoAVL<T>::getDato() const {
    return dato;
}

template<typename T>
void NodoAVL<T>::setDato(T dato) {
    this->dato = dato;
}

template<typename T>
NodoAVL<T>* NodoAVL<T>::getIzquierda() const {
    return izquierda;
}

template<typename T>
void NodoAVL<T>::setIzquierda(NodoAVL<T>* nodo) {
    this->izquierda = nodo;
}

template<typename T>
NodoAVL<T>* NodoAVL<T>::getDerecha() const {
    return derecha;
}

template<typename T>
void NodoAVL<T>::setDerecha(NodoAVL<T>* nodo) {
    this->derecha = nodo;
}

template<typename T>
int NodoAVL<T>::getAltura() const {
    return altura;
}

template<typename T>
void NodoAVL<T>::setAltura(int altura) {
    this->altura = altura;
}