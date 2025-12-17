#include "Nodo.hpp"

// Constructor por defecto
template<typename T>
Nodo<T>::Nodo(){
    this->Derecha = nullptr;
    this->Izquierda = nullptr;
}

// Constructor con solo dato y puntero izquierdo
template<typename T>
Nodo<T>::Nodo(Nodo* izquierda, T dato){
    this->Izquierda = izquierda;
    this->Derecha = nullptr;
    this->dato = dato;
}

template<typename T>
Nodo<T>::Nodo(T dato){
    this->Izquierda=nullptr;
    this->Derecha=nullptr;
    this->dato = dato;
}

// Constructor con dato y puntero derecho
template<typename T>
Nodo<T>::Nodo(T dato, Nodo* derecha){
    this->dato = dato;
    this->Derecha = derecha;
    this->Izquierda = nullptr;
}

// Constructor con ambos punteros y dato
template<typename T>
Nodo<T>::Nodo(Nodo* izquierda, Nodo* derecha, T dato){
    this->Izquierda = izquierda;
    this->Derecha = derecha;
    this->dato = dato;
}

// Setter para puntero derecho
template<typename T>
void Nodo<T>::setDerecha(Nodo* derecha){
    this->Derecha = derecha;
}

// Setter para puntero izquierdo
template<typename T>
void Nodo<T>::setIzquierda(Nodo* izquierda){
    this->Izquierda = izquierda;
}

// Setter para dato
template<typename T>
void Nodo<T>::setDato(T dato){
    this->dato = dato;
}

// Getter para puntero izquierdo
template<typename T>
Nodo<T>* Nodo<T>::getIzquierda()const{
    return this->Izquierda;
}

// Getter para puntero derecho
template<typename T>
Nodo<T>* Nodo<T>::getDerecha()const{
    return this->Derecha;
}

// Getter para dato
template<typename T>
T Nodo<T>::getDato()const{
    return this->dato;
}

template<typename T>
void Nodo<T>::insertar(T datoInsertar){
    if(datoInsertar<dato){
        if(Izquierda==nullptr){
            Izquierda=new Nodo(datoInsertar);
        }
        else
        Izquierda->insertar(datoInsertar);
    }
    else if(datoInsertar>dato){
        if(Derecha==nullptr){
            Derecha=new Nodo(datoInsertar);
        }
        else
        Derecha->insertar(datoInsertar);
    }

}

