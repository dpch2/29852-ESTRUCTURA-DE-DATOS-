#include "./Nodo/AVL.cpp"
#include <iostream>

int main (void){
    AVL<int> arbol;

    std::cout << "--- Demo Arbol AVL ---" << std::endl;

    int valores[] = {10, 20, 30, 40, 50, 25};

    for(int val : valores) {
        std::cout << "Insertando: " << val << std::endl;
        arbol.insertar(val);
    }

    std::cout << "\nRecorrido Inorden (verificacion de ordenamiento): ";
    arbol.inorden();

    return 0;
}