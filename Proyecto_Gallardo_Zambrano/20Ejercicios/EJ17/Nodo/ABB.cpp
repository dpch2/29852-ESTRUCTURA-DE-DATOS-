#include "ABB.hpp"
#include <iostream>

// Constructor
template<typename T>
ABB<T>::ABB(){
    Raiz = nullptr;
}

template<typename T>
ABB<T>::~ABB(){
    eliminarAux(Raiz);
}

template<typename T>
void ABB<T>::insertarNodo(T valorInsertar){
    Raiz = insertarAux(Raiz, valorInsertar);
}

template<typename T>
Nodo<T>* ABB<T>::insertarAux(Nodo<T>* nodo, T valor){
    // Caso base: crear nuevo nodo
    if(nodo == nullptr){
        return new Nodo<T>(valor, nullptr);
    }
    
    // Insertar en subárbol izquierdo si es menor
    if(valor < nodo->getDato()){
        nodo->setIzquierda(insertarAux(nodo->getIzquierda(), valor));
    }
    // Insertar en subárbol derecho si es mayor
    else if(valor > nodo->getDato()){
        nodo->setDerecha(insertarAux(nodo->getDerecha(), valor));
    }
    // Si es igual, no insertar (evitar duplicados)
    
    return nodo;
}

// Método público para buscar
template<typename T>
bool ABB<T>::buscar(T valorBuscar){
    return buscarAux(Raiz, valorBuscar) != nullptr;
}

// Método auxiliar recursivo para buscar
template<typename T>
Nodo<T>* ABB<T>::buscarAux(Nodo<T>* nodo, T valor){
    // Caso base: nodo no encontrado
    if(nodo == nullptr){
        return nullptr;
    }
    
    // Si el valor es igual, retornar el nodo
    if(nodo->getDato() == valor){
        return nodo;
    }
    // Si el valor es menor, buscar en subárbol izquierdo
    else if(valor < nodo->getDato()){
        return buscarAux(nodo->getIzquierda(), valor);
    }
    // Si el valor es mayor, buscar en subárbol derecho
    else{
        return buscarAux(nodo->getDerecha(), valor);
    }
}

// Método auxiliar para eliminar todo el árbol
template<typename T>
void ABB<T>::eliminarAux(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    eliminarAux(nodo->getIzquierda());
    eliminarAux(nodo->getDerecha());
    delete nodo;
}

// Recorrido en orden (izquierda, raíz, derecha)
template<typename T>
void ABB<T>::inorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    inorden(nodo->getIzquierda());
    std::cout << nodo->getDato() << " ";
    inorden(nodo->getDerecha());
}

// Recorrido en pre-orden (raíz, izquierda, derecha)
template<typename T>
void ABB<T>::preorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    std::cout << nodo->getDato() << " ";
    preorden(nodo->getIzquierda());
    preorden(nodo->getDerecha());
}

// Recorrido en post-orden (izquierda, derecha, raíz)
template<typename T>
void ABB<T>::postorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    postorden(nodo->getIzquierda());
    postorden(nodo->getDerecha());
    std::cout << nodo->getDato() << " ";
}

// Getter para la raíz
template<typename T>
Nodo<T>* ABB<T>::getRaiz()const{
    return Raiz;
}

// Método para buscar el nodo con el valor mayor (extremo derecho)
template<typename T>
Nodo<T>* ABB<T>::buscarMayor() const {
    if (Raiz == nullptr) return nullptr;

    Nodo<T>* actual = Raiz;
    while (actual->getDerecha() != nullptr) {
        actual = actual->getDerecha();
    }
    return actual;
}

// Método para buscar el nodo con el valor menor (extremo izquierdo)
template<typename T>
Nodo<T>* ABB<T>::buscarMenor() const {
    if (Raiz == nullptr) return nullptr;

    Nodo<T>* actual = Raiz;
    while (actual->getIzquierda() != nullptr) {
        actual = actual->getIzquierda();
    }
    return actual;
}

template<typename T>
int ABB<T>::contarNodos(){
    return contarNodosAux(Raiz);
}

template<typename T>
int ABB<T>::contarNodosAux(Nodo<T>* nodo){
    if(nodo == nullptr) return 0;
    return 1 + contarNodosAux(nodo->getIzquierda()) + contarNodosAux(nodo->getDerecha());
}

template<typename T>
int ABB<T>::contarHojas(){
    return contarHojasAux(Raiz);
}

template<typename T>
int ABB<T>::contarHojasAux(Nodo<T>* nodo){
    if(nodo == nullptr) return 0;
    if(nodo->getIzquierda() == nullptr && nodo->getDerecha() == nullptr){
        return 1;
    }
    return contarHojasAux(nodo->getIzquierda()) + contarHojasAux(nodo->getDerecha());
}

template<typename T>
void ABB<T>::imprimirHojas(){
    imprimirHojasAux(Raiz);
    std::cout << std::endl;
}

template<typename T>
void ABB<T>::imprimirHojasAux(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    // Si es hoja, imprimir
    if(nodo->getIzquierda() == nullptr && nodo->getDerecha() == nullptr){
        std::cout << nodo->getDato() << " ";
        return;
    }
    
    imprimirHojasAux(nodo->getIzquierda());
    imprimirHojasAux(nodo->getDerecha());
}

template<typename T>
Nodo<T>* ABB<T>::obtenerPadre(Nodo<T>* hijo){
    // Si el hijo es nulo, o es la raíz (no tiene padre), retornamos nullptr
    if(hijo == nullptr || Raiz == nullptr || hijo == Raiz) return nullptr;

    Nodo<T>* actual = Raiz;
    T valorHijo = hijo->getDato();

    while(actual != nullptr){
        if(valorHijo < actual->getDato()){
            if(actual->getIzquierda() == hijo) return actual;
            actual = actual->getIzquierda();
        }
        else if(valorHijo > actual->getDato()){
            if(actual->getDerecha() == hijo) return actual;
            actual = actual->getDerecha();
        }
        else {
            // Encontró el valor pero no es hijo directo (caso raro si el puntero es válido)
            return nullptr;
        }
    }
    return nullptr;
}

template<typename T>
int ABB<T>::obtenerAltura(){
    return obtenerAlturaAux(Raiz);
}

template<typename T>
int ABB<T>::obtenerAlturaAux(Nodo<T>* nodo){
    if(nodo == nullptr) return 0;
    
    int alturaIzq = obtenerAlturaAux(nodo->getIzquierda());
    int alturaDer = obtenerAlturaAux(nodo->getDerecha());
    
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}