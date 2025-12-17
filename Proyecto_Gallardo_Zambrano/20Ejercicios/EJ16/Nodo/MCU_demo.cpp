#include "MCU_Tree.cpp"
#include <iostream>

int main() {
    MCU_Tree arbol;

    // Insertar ejemplo de personajes (nombre, esHeroe)
    arbol.insertar("Thanos", false);
    arbol.insertar("Loki", false);
    arbol.insertar("Ultron", false);
    arbol.insertar("Crossbones", false);
    arbol.insertar("Corvus Glaive", false);

    arbol.insertar("Captain America", true);
    arbol.insertar("Captain Marvel", true);
    arbol.insertar("Hulk", true);
    arbol.insertar("Iron Man", true);
    arbol.insertar("Scarlet Witch", true);
    arbol.insertar("Coulson", true);

    std::cout << "Villanos ordenados alfabeticamente:\n";
    for (const auto &v : arbol.listarVillanos()) std::cout << " - " << v << "\n";

    std::cout << "\nHeroes que empiezan con 'C':\n";
    for (const auto &h : arbol.heroesEmpiezanCon('C')) std::cout << " - " << h << "\n";

    std::cout << "\nCantidad de heroes en el arbol: " << arbol.contarHeroes() << "\n";

    return 0;
}
