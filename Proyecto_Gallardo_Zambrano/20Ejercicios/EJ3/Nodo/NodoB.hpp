#pragma once
#include <iostream>

template<typename T>
class NodoB {
private:
    T* claves;          
    NodoB** hijos;    
    NodoB* siguiente;  
    int n;              
    bool esHoja;        
    int orden;          

public:
    NodoB(int orden, bool esHoja);
    ~NodoB();

    // Getters y Setters básicos
    T getClave(int index) const;
    void setClave(int index, T valor);
    NodoB* getHijo(int index) const;
    void setHijo(int index, NodoB* nodo);
    NodoB* getSiguiente() const;
    void setSiguiente(NodoB* nodo);
    int getN() const;
    void setN(int val);
    bool getEsHoja() const;
    
    // Amistad para facilitar acceso desde el árbol
    template<typename U> friend class ArbolBMas;
};