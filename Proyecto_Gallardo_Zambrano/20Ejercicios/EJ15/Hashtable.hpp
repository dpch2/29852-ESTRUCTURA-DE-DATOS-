#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "Bucket.hpp"
#include <string>

#define TAM 28

class HashTable {
private:
    Bucket *tabla;

    int funcionHash(std::string palabra);
    NodoABB* insertarABB(NodoABB *raiz, std::string p, std::string s);
    void buscarABB(NodoABB *raiz, std::string p);

public:
    HashTable();

    void insertar(std::string palabra, std::string significado);
    void buscar(std::string palabra);
    void eliminar(std::string palabra);
};

#endif
