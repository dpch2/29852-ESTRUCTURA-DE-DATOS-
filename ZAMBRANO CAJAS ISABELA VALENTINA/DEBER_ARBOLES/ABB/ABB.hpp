#pragma once

#include "../common/Nodo.hpp"

template<typename T>
class ABB{
    
    private:
    Nodo<T>* Raiz;
    
    // Métodos auxiliares privados recursivos
    Nodo<T>* insertarAux(Nodo<T>* nodo, T valor);
    Nodo<T>* buscarAux(Nodo<T>* nodo, T valor);
    Nodo<T>* eliminarNodoAux(Nodo<T>* nodo, T valor);
    Nodo<T>* encontrarMinimo(Nodo<T>* nodo);
    void eliminarAux(Nodo<T>* nodo);
    
    public:
    ABB();
    ~ABB();
    void insertarNodo(T valorInsertar);
    bool buscar(T valorBuscar);
    void eliminarNodo(T valorEliminar);
    void inorden(Nodo<T>* nodo);
    void preorden(Nodo<T>* nodo);
    void postorden(Nodo<T>* nodo);
    Nodo<T>* getRaiz()const;

};