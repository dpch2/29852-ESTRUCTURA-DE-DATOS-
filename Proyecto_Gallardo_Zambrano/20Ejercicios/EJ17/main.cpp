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

    std::cout << "\n\n--- Estadisticas del Arbol ---" << std::endl;
    std::cout << "Cantidad total de nodos: " << arbol.contarNodos() << std::endl;
    std::cout << "Cantidad de hojas: " << arbol.contarHojas() << std::endl;
    std::cout << "Altura del arbol: " << arbol.obtenerAltura() << std::endl;

    std::cout << "Valores de las hojas: ";
    arbol.imprimirHojas(); // Este metodo ya imprime un salto de linea al final

    // Prueba de obtenerPadre usando el nodo mayor como referencia
    Nodo<int>* nodoMayor = arbol.buscarMayor();
    if (nodoMayor != nullptr) {
        Nodo<int>* padre = arbol.obtenerPadre(nodoMayor);
        if (padre != nullptr) std::cout << "El padre del nodo mayor (" << nodoMayor->getDato() << ") es: " << padre->getDato() << std::endl;
        else std::cout << "El nodo mayor (" << nodoMayor->getDato() << ") es la raiz y no tiene padre." << std::endl;
    }
}