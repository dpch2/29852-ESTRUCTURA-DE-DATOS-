
#pragma once

#include "Nodo.hpp"

template<typename T>
class ABB{
    
    private:
    Nodo<T>* Raiz;
    
    // Métodos auxiliares privados recursivos
    Nodo<T>* insertarAux(Nodo<T>* nodo, T valor);
    Nodo<T>* buscarAux(Nodo<T>* nodo, T valor);
    void eliminarAux(Nodo<T>* nodo);
    int contarNodosAux(Nodo<T>* nodo);
    int contarHojasAux(Nodo<T>* nodo);
    void imprimirHojasAux(Nodo<T>* nodo);
    int obtenerAlturaAux(Nodo<T>* nodo);
    
    public:
    ABB();
    ~ABB();
    void insertarNodo(T valorInsertar);
    bool buscar(T valorBuscar);
    void inorden(Nodo<T>* nodo);
    void preorden(Nodo<T>* nodo);
    void postorden(Nodo<T>* nodo);
    Nodo<T>* getRaiz()const;
    Nodo<T>* buscarMayor()const;
    Nodo<T>* buscarMenor()const;
    int contarNodos();
    int contarHojas();
    void imprimirHojas();
    Nodo<T>* obtenerPadre(Nodo<T>* hijo);
    int obtenerAltura();
};
