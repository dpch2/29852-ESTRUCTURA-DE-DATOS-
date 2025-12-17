#ifndef NODOABB_HPP
#define NODOABB_HPP

#include <string>

class NodoABB {
public:
    std::string palabra;
    std::string significado;
    NodoABB *izq;
    NodoABB *der;

    NodoABB(std::string p, std::string s) {
        palabra = p;
        significado = s;
        izq = nullptr;
        der = nullptr;
    }
};

#endif
