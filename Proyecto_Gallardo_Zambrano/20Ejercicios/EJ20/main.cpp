#include "RedBlack.cpp"
#include <iostream>
#include <vector>

int main() {
    RedBlackTree tree;
    std::vector<int> values = {8, 4, 12, 2, 11, 16, 7, 8, 16, 5,14,4,8,4,11};

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
