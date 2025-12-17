#include "HashTable.hpp"
#include <iostream>

HashTable::HashTable() {
    tabla = new Bucket[TAM];
}

int HashTable::funcionHash(std::string palabra) {
    int suma = 0;
    for (char c : palabra)
        suma += c;
    return suma % TAM;
}

NodoABB* HashTable::insertarABB(NodoABB *raiz, std::string p, std::string s) {
    if (raiz == nullptr)
        return new NodoABB(p, s);

    if (p < raiz->palabra)
        raiz->izq = insertarABB(raiz->izq, p, s);
    else if (p > raiz->palabra)
        raiz->der = insertarABB(raiz->der, p, s);

    return raiz;
}

void HashTable::insertar(std::string palabra, std::string significado) {
    int i = funcionHash(palabra);
    Bucket *b = tabla + i;

    if (b->usarArbol) {
        b->arbol = insertarABB(b->arbol, palabra, significado);
        return;
    }

    NodoLista *nuevo = new NodoLista(palabra, significado);
    nuevo->siguiente = b->lista;
    b->lista = nuevo;

    int contador = 0;
    NodoLista *aux = b->lista;

    while (aux != nullptr) {
        contador++;
        aux = aux->siguiente;
    }

    if (contador > 3) {
        aux = b->lista;
        while (aux != nullptr) {
            b->arbol = insertarABB(b->arbol, aux->palabra, aux->significado);
            aux = aux->siguiente;
        }
        b->usarArbol = true;
    }
}
void HashTable::buscarABB(NodoABB *raiz, std::string p) {
    if (raiz == nullptr) {
        std::cout << "Palabra no encontrada\n";
        return;
    }

    if (p == raiz->palabra) {
        std::cout << "Significado: " << raiz->significado << std::endl;
        return;
    }

    if (p < raiz->palabra)
        buscarABB(raiz->izq, p);
    else
        buscarABB(raiz->der, p);
}
void HashTable::buscar(std::string palabra) {
    int i = funcionHash(palabra);
    Bucket *b = tabla + i;

    if (b->usarArbol) {
        buscarABB(b->arbol, palabra);
        return;
    }

    NodoLista *aux = b->lista;
    while (aux != nullptr) {
        if (aux->palabra == palabra) {
            std::cout << "Significado: " << aux->significado << std::endl;
            return;
        }
        aux = aux->siguiente;
    }
    std::cout << "Palabra no encontrada\n";
}
void HashTable::eliminar(std::string palabra) {
    int i = funcionHash(palabra);
    Bucket *b = tabla + i;

    NodoLista *aux = b->lista;
    NodoLista *ant = nullptr;

    while (aux != nullptr) {
        if (aux->palabra == palabra) {
            if (ant == nullptr)
                b->lista = aux->siguiente;
            else
                ant->siguiente = aux->siguiente;

            delete aux;
            std::cout << "Palabra eliminada\n";
            return;
        }
        ant = aux;
        aux = aux->siguiente;
    }
    std::cout << "Palabra no encontrada\n";
}
