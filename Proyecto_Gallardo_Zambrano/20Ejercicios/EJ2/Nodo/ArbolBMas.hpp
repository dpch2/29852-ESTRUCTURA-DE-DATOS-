#pragma once
#include "../Nodo/NodoB.cpp"

template<typename T>
class ArbolBMas {
private:
    NodoB<T>* raiz;
    int orden; // Grado del árbol

    // Métodos auxiliares privados
    NodoB<T>* buscarHoja(T clave);
    void insertarEnPadre(NodoB<T>* n, T clave, NodoB<T>* nuevoNodo);
    NodoB<T>* encontrarPadre(NodoB<T>* raiz, NodoB<T>* hijo);
    void imprimirArbol(NodoB<T>* nodo, int nivel);

public:
    ArbolBMas(int orden);
    ~ArbolBMas();
    
    void insertar(T clave);
    bool buscar(T clave);
    void imprimir();
    void imprimirListaEnlazada(); // Para verificar la conexión de las hojas
};