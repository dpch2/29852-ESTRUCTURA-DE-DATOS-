
#pragma once
template<typename T>
class Nodo{

    private:
    Nodo* Derecha;
    Nodo* Izquierda;
    T dato;

    public:
    Nodo();
    Nodo(T dato);
    Nodo(Nodo* izquierda, T dato);
    Nodo(T dato, Nodo* derecha);
    Nodo(Nodo* derecha, Nodo* izquierda, T dato);

    void setDerecha(Nodo* derecha);
    void setIzquierda(Nodo* izquierda);
    void setDato(T dato);

    Nodo* getIzquierda()const;
    Nodo* getDerecha()const;
    T getDato()const;

    void insertar(T datoInsertar);
};
