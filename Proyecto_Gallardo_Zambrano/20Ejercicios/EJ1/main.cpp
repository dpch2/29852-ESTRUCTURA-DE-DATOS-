#include "./Nodo/Nodo.cpp"
#include "./Nodo/ABB.cpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(void){
    // Inicializar la semilla aleatoria
    std::srand(std::time(nullptr));

    ABB<int> arbol;

    std::cout << "Generando e insertando 20 numeros aleatorios: " << std::endl;
    for(int i = 0; i < 20; i++){
        int numero = std::rand() % 100 + 1; // Genera números entre 1 y 100
        std::cout << numero << " ";
        arbol.insertarNodo(numero);
    }
    std::cout << "\n\nRecorrido Inorden (verificacion de ordenamiento): ";
    arbol.inorden(arbol.getRaiz());
    std::cout << std::endl;

    // Demo de buscarMayor y buscarMenor
    std::cout << "\n--- Demo Busqueda Mayor y Menor ---" << std::endl;
    
    Nodo<int>* menor = arbol.buscarMenor();
    if(menor != nullptr)
        std::cout << "El valor menor del arbol es: " << menor->getDato() << std::endl;
    else
        std::cout << "El arbol esta vacio." << std::endl;

    Nodo<int>* mayor = arbol.buscarMayor();
    if(mayor != nullptr)
        std::cout << "El valor mayor del arbol es: " << mayor->getDato() << std::endl;
    else
        std::cout << "El arbol esta vacio." << std::endl;
}
