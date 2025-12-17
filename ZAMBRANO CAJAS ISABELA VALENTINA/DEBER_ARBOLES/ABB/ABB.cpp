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

// Método público para eliminar un nodo
template<typename T>
void ABB<T>::eliminarNodo(T valorEliminar){
    Raiz = eliminarNodoAux(Raiz, valorEliminar);
}

// Método auxiliar recursivo para eliminar un nodo
template<typename T>
Nodo<T>* ABB<T>::eliminarNodoAux(Nodo<T>* nodo, T valor){
    // Caso base: árbol vacío
    if(nodo == nullptr){
        std::cout << "El valor " << valor << " no se encontro en el arbol.\n";
        return nullptr;
    }
    
    // Buscar el nodo a eliminar
    if(valor < nodo->getDato()){
        // Buscar en subárbol izquierdo
        nodo->setIzquierda(eliminarNodoAux(nodo->getIzquierda(), valor));
    }
    else if(valor > nodo->getDato()){
        // Buscar en subárbol derecho
        nodo->setDerecha(eliminarNodoAux(nodo->getDerecha(), valor));
    }
    else{
        // Nodo encontrado, proceder a eliminación
        
        // Caso 1: Nodo sin hijos (hoja)
        if(nodo->getIzquierda() == nullptr && nodo->getDerecha() == nullptr){
            std::cout << "Eliminando nodo hoja: " << valor << "\n";
            delete nodo;
            return nullptr;
        }
        
        // Caso 2: Nodo con solo hijo derecho
        if(nodo->getIzquierda() == nullptr){
            std::cout << "Eliminando nodo con solo hijo derecho: " << valor << "\n";
            Nodo<T>* temp = nodo->getDerecha();
            delete nodo;
            return temp;
        }
        
        // Caso 3: Nodo con solo hijo izquierdo
        if(nodo->getDerecha() == nullptr){
            std::cout << "Eliminando nodo con solo hijo izquierdo: " << valor << "\n";
            Nodo<T>* temp = nodo->getIzquierda();
            delete nodo;
            return temp;
        }
        
        // Caso 4: Nodo con dos hijos
        std::cout << "Eliminando nodo con dos hijos: " << valor << "\n";
        // Encontrar el nodo mínimo en el subárbol derecho (sucesor)
        Nodo<T>* sucesor = encontrarMinimo(nodo->getDerecha());
        T valorSucesor = sucesor->getDato();
        
        // Reemplazar el valor del nodo actual con el del sucesor
        nodo->setDato(valorSucesor);
        
        // Eliminar el nodo sucesor del subárbol derecho
        nodo->setDerecha(eliminarNodoAux(nodo->getDerecha(), valorSucesor));
    }
    
    return nodo;
}

// Encontrar el nodo con valor mínimo (más a la izquierda)
template<typename T>
Nodo<T>* ABB<T>::encontrarMinimo(Nodo<T>* nodo){
    if(nodo->getIzquierda() == nullptr){
        return nodo;
    }
    return encontrarMinimo(nodo->getIzquierda());
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