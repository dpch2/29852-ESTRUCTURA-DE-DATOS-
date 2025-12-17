#pragma once

template<typename T>
class NodoAVL {
private:
    T dato;
    NodoAVL* izquierda;
    NodoAVL* derecha;
    int altura; // Altura del nodo para el balanceo

public:
    NodoAVL(T dato);
    ~NodoAVL();

    T getDato() const;
    void setDato(T dato);
    
    NodoAVL* getIzquierda() const;
    void setIzquierda(NodoAVL* nodo);
    
    NodoAVL* getDerecha() const;
    void setDerecha(NodoAVL* nodo);
    
    int getAltura() const;
    void setAltura(int altura);

    // Amistad para que la clase AVL acceda a los miembros privados si es necesario
    template<typename U> friend class AVL;
};