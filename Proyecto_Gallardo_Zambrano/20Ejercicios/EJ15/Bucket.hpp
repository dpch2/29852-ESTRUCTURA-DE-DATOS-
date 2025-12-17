#ifndef BUCKET_HPP
#define BUCKET_HPP

#include "NodoLista.hpp"
#include "NodoABB.hpp"

class Bucket {
public:
    NodoLista *lista;
    NodoABB *arbol;
    bool usarArbol;

    Bucket() {
        lista = nullptr;
        arbol = nullptr;
        usarArbol = false;
    }
};

#endif
