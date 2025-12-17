#include <iostream>
#include <vector>
#include "Nodo/ArbolBMas.hpp"
#include "Nodo/ArbolBMas.cpp" // implementación de plantillas

int main() {
    ArbolBMas<int> arbol(4); // orden (grado) = 4

    std::vector<int> inserciones = {35,35,41,34,10,39,8,42,27,14,19,50,33,41,24,34,13,9,1,14};
    std::cout << "--- Inserciones paso a paso ---\n";
    for (size_t i = 0; i < inserciones.size(); ++i) {
        int k = inserciones[i];
        std::cout << "Insertando: " << k << "\n";
        arbol.insertar(k);
        arbol.imprimir();
        std::cout << "-----------------------------\n";
    }

    std::vector<int> eliminaciones = {9,34,13,14,35,41};
    std::cout << "--- Eliminaciones paso a paso ---\n";
    for (int k : eliminaciones) {
        std::cout << "Eliminando: " << k << "\n";
        arbol.eliminar(k);
        arbol.imprimir();
        std::cout << "-----------------------------\n";
    }

    // Función interactiva para que el usuario elimine valores adicionales si lo desea
    std::cout << "Ingrese valores para eliminar (separados por espacio), o fin para terminar:\n";
    std::string token;
    while (std::cin >> token) {
        if (token == "fin" || token == "FIN" || token == "q") break;
        try {
            int v = std::stoi(token);
            std::cout << "Eliminando: " << v << "\n";
            arbol.eliminar(v);
            arbol.imprimir();
        } catch(...) {
            std::cout << "Entrada no valida. Use numeros o 'fin' para salir.\n";
        }
    }

    return 0;
}
