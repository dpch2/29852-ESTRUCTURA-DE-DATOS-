/*
Ejercicio:
Se cuenta con una lista de Pokémons, de cada uno de estos se sabe su nombre,
número y tipo (solo considerar uno el principal). Con los cuales deberá resolver
las siguientes tareas: determinar si existe el Pokémon "Cobalion" y mostrar toda
su información.
*/
#include <iostream>
#include <cstring>
using namespace std;

struct Pokemon {
    int numero;
    char nombre[30];
    char tipo[20];
};

Pokemon* busquedaBinaria(Pokemon* lista, int inicio, int fin, int clave) {
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if (lista[medio].numero == clave) {
            return &lista[medio];
        }
        else if (clave < lista[medio].numero) {
            fin = medio - 1;
        }
        else {
            inicio = medio + 1;
        }
    }
    return nullptr;
}

int main() {
    int n = 5;

    // Arreglo ORDENADO por número
    Pokemon* lista = new Pokemon[n]{
        {144, "Articuno",  "Hielo"},
        {145, "Zapdos",    "Electrico"},
        {146, "Moltres",   "Fuego"},
        {638, "Cobalion",  "Acero"},
        {639, "Terrakion", "Roca"}
    };

    int clave = 638;  // numero de Cobalion

    Pokemon* p = busquedaBinaria(lista, 0, n - 1, clave);

    if (p != nullptr) {
        cout << "POKEMON ENCONTRADO\n";
        cout << "Nombre: " << p->nombre << endl;
        cout << "Numero: " << p->numero << endl;
        cout << "Tipo: "   << p->tipo   << endl;
    } else {
        cout << "Cobalion NO esta en la lista\n";
    }

    delete[] lista;
    return 0;
}
