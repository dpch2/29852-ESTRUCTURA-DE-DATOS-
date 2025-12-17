#include "RedBlack.cpp"
#include <vector>
#include <iostream>

int main() {
    RedBlackTree tree;
    std::vector<int> inserts = {35, 41, 34, 35, 10, 19, 50, 33, 41, 24, 34, 13, 9, 1, 14};
    std::cout << "--- Inserciones paso a paso ---\n";
    for (size_t i = 0; i < inserts.size(); ++i) {
        std::cout << "Insertar: " << inserts[i] << "\n";
        tree.insert(inserts[i]);
        tree.printTree();
        std::cout << "-----------------------------\n";
    }

    std::vector<int> deletes = {9, 34, 13};
    std::cout << "--- Eliminaciones paso a paso ---\n";
    for (int k : deletes) {
        std::cout << "Eliminar: " << k << "\n";
        bool ok = tree.remove(k);
        if (ok) std::cout << " -> Eliminado\n";
        else std::cout << " -> No encontrado\n";
        tree.printTree();
        std::cout << "-----------------------------\n";
    }
    return 0;
}
