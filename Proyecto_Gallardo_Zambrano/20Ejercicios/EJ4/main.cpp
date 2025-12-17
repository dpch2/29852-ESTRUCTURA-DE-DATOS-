#include "RedBlack.cpp"
#include <iostream>
#include <vector>

int main() {
    RedBlackTree tree;
    std::vector<int> values = {35, 41,34,35, 10,19, 50, 33, 41, 24, 34, 13, 9, 1, 14};

    std::cout << "Insertando: ";
    for (int v : values) {
        std::cout << v << " ";
        tree.insert(v);
    }
    std::cout << "\n\nEstado del árbol después de inserciones:\n";
    tree.printTree();

    std::cout << "\nIngrese un valor a eliminar: ";
    int toDelete;
    if (!(std::cin >> toDelete)) return 0;

    bool removed = tree.remove(toDelete);
    if (removed) std::cout << "\nElemento " << toDelete << " eliminado.\n";
    else std::cout << "\nElemento " << toDelete << " no encontrado.\n";

    std::cout << "\nEstado del árbol después de eliminación:\n";
    tree.printTree();

    return 0;
}
