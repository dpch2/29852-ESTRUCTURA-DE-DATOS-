#include "MCU_Tree.hpp"
#include <algorithm>

MCU_Tree::MCU_Tree() : raiz(nullptr) {}

MCU_Tree::~MCU_Tree() { destruir(raiz); }

void MCU_Tree::destruir(MCUNode* nodo) {
    if (!nodo) return;
    destruir(nodo->izq);
    destruir(nodo->der);
    delete nodo;
}

MCUNode* MCU_Tree::insertarRec(MCUNode* nodo, const std::string& nombre, bool esHeroe) {
    if (!nodo) return new MCUNode(nombre, esHeroe);
    if (nombre < nodo->nombre) nodo->izq = insertarRec(nodo->izq, nombre, esHeroe);
    else nodo->der = insertarRec(nodo->der, nombre, esHeroe);
    return nodo;
}

void MCU_Tree::insertar(const std::string& nombre, bool esHeroe) {
    raiz = insertarRec(raiz, nombre, esHeroe);
}

void MCU_Tree::inorderCollectVillains(MCUNode* nodo, std::vector<std::string>& out) const {
    if (!nodo) return;
    inorderCollectVillains(nodo->izq, out);
    if (!nodo->esHeroe) out.push_back(nodo->nombre);
    inorderCollectVillains(nodo->der, out);
}

std::vector<std::string> MCU_Tree::listarVillanos() const {
    std::vector<std::string> out;
    inorderCollectVillains(raiz, out);
    return out;
}

void MCU_Tree::inorderCollectHeroesPrefix(MCUNode* nodo, char letra, std::vector<std::string>& out) const {
    if (!nodo) return;
    inorderCollectHeroesPrefix(nodo->izq, letra, out);
    if (nodo->esHeroe) {
        if (!nodo->nombre.empty()) {
            char primer = nodo->nombre[0];
            if (std::tolower(primer) == std::tolower(letra)) out.push_back(nodo->nombre);
        }
    }
    inorderCollectHeroesPrefix(nodo->der, letra, out);
}

std::vector<std::string> MCU_Tree::heroesEmpiezanCon(char letra) const {
    std::vector<std::string> out;
    inorderCollectHeroesPrefix(raiz, letra, out);
    return out;
}

int MCU_Tree::countHeroesRec(MCUNode* nodo) const {
    if (!nodo) return 0;
    int sum = nodo->esHeroe ? 1 : 0;
    sum += countHeroesRec(nodo->izq);
    sum += countHeroesRec(nodo->der);
    return sum;
}

int MCU_Tree::contarHeroes() const {
    return countHeroesRec(raiz);
}
