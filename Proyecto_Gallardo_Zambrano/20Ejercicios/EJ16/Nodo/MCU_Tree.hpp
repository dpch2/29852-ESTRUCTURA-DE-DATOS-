#ifndef MCU_TREE_HPP
#define MCU_TREE_HPP

#include <string>
#include <vector>

struct MCUNode {
    std::string nombre;
    bool esHeroe; // true = héroe, false = villano
    MCUNode* izq;
    MCUNode* der;
    MCUNode(const std::string& n, bool h) : nombre(n), esHeroe(h), izq(nullptr), der(nullptr) {}
};

class MCU_Tree {
public:
    MCU_Tree();
    ~MCU_Tree();

    // Inserta por orden lexicográfico del nombre
    void insertar(const std::string& nombre, bool esHeroe);

    // Lista los villanos ordenados alfabéticamente
    std::vector<std::string> listarVillanos() const;

    // Muestra todos los superhéroes que empiezan con la letra dada (case-insensitive)
    std::vector<std::string> heroesEmpiezanCon(char letra) const;

    // Cuenta cuántos superhéroes hay en el árbol
    int contarHeroes() const;

private:
    MCUNode* raiz;

    void destruir(MCUNode* nodo);
    MCUNode* insertarRec(MCUNode* nodo, const std::string& nombre, bool esHeroe);
    void inorderCollectVillains(MCUNode* nodo, std::vector<std::string>& out) const;
    void inorderCollectHeroesPrefix(MCUNode* nodo, char letra, std::vector<std::string>& out) const;
    int countHeroesRec(MCUNode* nodo) const;
};

#endif
