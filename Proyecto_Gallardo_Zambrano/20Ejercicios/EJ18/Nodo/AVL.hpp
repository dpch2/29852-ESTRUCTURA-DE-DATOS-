#pragma once
#include "../Nodo/NodoAVL.cpp"

template<typename T>
class AVL {
private:
    NodoAVL<T>* raiz;

    // Métodos auxiliares para el balanceo
    int obtenerAltura(NodoAVL<T>* nodo);
    int obtenerBalance(NodoAVL<T>* nodo);
    int maximo(int a, int b);
    
    // Rotaciones
    NodoAVL<T>* rotacionDerecha(NodoAVL<T>* y);
    NodoAVL<T>* rotacionIzquierda(NodoAVL<T>* x);
    
    // Recursivos
    NodoAVL<T>* insertarAux(NodoAVL<T>* nodo, T dato);
    void inordenAux(NodoAVL<T>* nodo);

public:
    AVL();
    void insertar(T dato);
    void inorden();
};