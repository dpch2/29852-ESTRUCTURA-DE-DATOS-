#ifndef NODOLISTA_HPP
#define NODOLISTA_HPP

#include <string>

class NodoLista {
public:
    std::string palabra;
    std::string significado;
    NodoLista *siguiente;

    NodoLista(std::string p, std::string s) {
        palabra = p;
        significado = s;
        siguiente = nullptr;
    }
};

#endif
