#include "AVL.hpp"
#include <iostream>
#include <algorithm>

// Constructor
template<typename T>
AVL<T>::AVL(){
    Raiz = nullptr;
}

// Destructor
template<typename T>
AVL<T>::~AVL(){
    eliminarAux(Raiz);
}

// Obtener altura de un nodo
template<typename T>
int AVL<T>::obtenerAltura(Nodo<T>* nodo){
    if(nodo == nullptr) return 0;
    
    int alturaIzq = obtenerAltura(nodo->getIzquierda());
    int alturaDer = obtenerAltura(nodo->getDerecha());
    
    return 1 + std::max(alturaIzq, alturaDer);
}

// Obtener factor de balance
template<typename T>
int AVL<T>::obtenerBalance(Nodo<T>* nodo){
    if(nodo == nullptr) return 0;
    
    return obtenerAltura(nodo->getIzquierda()) - obtenerAltura(nodo->getDerecha());
}

// Rotación simple a la derecha
template<typename T>
Nodo<T>* AVL<T>::rotarDerecha(Nodo<T>* nodo){
    Nodo<T>* temp = nodo->getIzquierda();
    nodo->setIzquierda(temp->getDerecha());
    temp->setDerecha(nodo);
    
    return temp;
}

// Rotación simple a la izquierda
template<typename T>
Nodo<T>* AVL<T>::rotarIzquierda(Nodo<T>* nodo){
    Nodo<T>* temp = nodo->getDerecha();
    nodo->setDerecha(temp->getIzquierda());
    temp->setIzquierda(nodo);
    
    return temp;
}

// Método público para insertar
template<typename T>
void AVL<T>::insertarNodo(T valorInsertar){
    Raiz = insertarAux(Raiz, valorInsertar);
}

// Método auxiliar recursivo para insertar con balanceo
template<typename T>
Nodo<T>* AVL<T>::insertarAux(Nodo<T>* nodo, T valor){
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
    else {
        return nodo;
    }
    
    // Obtener factor de balance
    int balance = obtenerBalance(nodo);
    
    // Caso Izquierda-Izquierda
    if(balance > 1 && valor < nodo->getIzquierda()->getDato()){
        return rotarDerecha(nodo);
    }
    
    // Caso Derecha-Derecha
    if(balance < -1 && valor > nodo->getDerecha()->getDato()){
        return rotarIzquierda(nodo);
    }
    
    // Caso Izquierda-Derecha
    if(balance > 1 && valor > nodo->getIzquierda()->getDato()){
        nodo->setIzquierda(rotarIzquierda(nodo->getIzquierda()));
        return rotarDerecha(nodo);
    }
    
    // Caso Derecha-Izquierda
    if(balance < -1 && valor < nodo->getDerecha()->getDato()){
        nodo->setDerecha(rotarDerecha(nodo->getDerecha()));
        return rotarIzquierda(nodo);
    }
    
    return nodo;
}

// Método público para buscar
template<typename T>
bool AVL<T>::buscar(T valorBuscar){
    return buscarAux(Raiz, valorBuscar) != nullptr;
}

// Método auxiliar recursivo para buscar
template<typename T>
Nodo<T>* AVL<T>::buscarAux(Nodo<T>* nodo, T valor){
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

// Método público para eliminar
template<typename T>
void AVL<T>::eliminarNodo(T valorEliminar){
    Raiz = eliminarNodoAux(Raiz, valorEliminar);
}

// Encontrar el nodo con valor mínimo (más a la izquierda)
template<typename T>
Nodo<T>* AVL<T>::encontrarMinimo(Nodo<T>* nodo){
    if(nodo->getIzquierda() == nullptr){
        return nodo;
    }
    return encontrarMinimo(nodo->getIzquierda());
}

// Método auxiliar recursivo para eliminar un nodo con balanceo
template<typename T>
Nodo<T>* AVL<T>::eliminarNodoAux(Nodo<T>* nodo, T valor){
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
    
    // Balancear el árbol después de la eliminación
    int balance = obtenerBalance(nodo);
    
    // Caso Izquierda-Izquierda
    if(balance > 1 && obtenerBalance(nodo->getIzquierda()) >= 0){
        return rotarDerecha(nodo);
    }
    
    // Caso Izquierda-Derecha
    if(balance > 1 && obtenerBalance(nodo->getIzquierda()) < 0){
        nodo->setIzquierda(rotarIzquierda(nodo->getIzquierda()));
        return rotarDerecha(nodo);
    }
    
    // Caso Derecha-Derecha
    if(balance < -1 && obtenerBalance(nodo->getDerecha()) <= 0){
        return rotarIzquierda(nodo);
    }
    
    // Caso Derecha-Izquierda
    if(balance < -1 && obtenerBalance(nodo->getDerecha()) > 0){
        nodo->setDerecha(rotarDerecha(nodo->getDerecha()));
        return rotarIzquierda(nodo);
    }
    
    return nodo;
}

// Método auxiliar para eliminar todo el árbol
template<typename T>
void AVL<T>::eliminarAux(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    eliminarAux(nodo->getIzquierda());
    eliminarAux(nodo->getDerecha());
    delete nodo;
}

// Recorrido en orden (izquierda, raíz, derecha)
template<typename T>
void AVL<T>::inorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    inorden(nodo->getIzquierda());
    std::cout << nodo->getDato() << " ";
    inorden(nodo->getDerecha());
}

// Recorrido en pre-orden (raíz, izquierda, derecha)
template<typename T>
void AVL<T>::preorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    std::cout << nodo->getDato() << " ";
    preorden(nodo->getIzquierda());
    preorden(nodo->getDerecha());
}

// Recorrido en post-orden (izquierda, derecha, raíz)
template<typename T>
void AVL<T>::postorden(Nodo<T>* nodo){
    if(nodo == nullptr) return;
    
    postorden(nodo->getIzquierda());
    postorden(nodo->getDerecha());
    std::cout << nodo->getDato() << " ";
}

// Getter para la raíz
template<typename T>
Nodo<T>* AVL<T>::getRaiz()const{
    return Raiz;
}

// Getter para la altura del árbol
template<typename T>
int AVL<T>::getAltura()const{
    return obtenerAltura(Raiz);
}