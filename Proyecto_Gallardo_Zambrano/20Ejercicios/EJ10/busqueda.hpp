#ifndef BUSQUEDA_HPP
#define BUSQUEDA_HPP
#include "Pokemons.hpp"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

class Busqueda{
    public:
    static int busquedaNombre(Pokemons** lista, string nombreBuscar, int size){
        int izq = 0, der = size - 1;
        while(izq <= der){
            int mid = izq + (der - izq) / 2;
            if(nombreBuscar == lista[mid]->getNombre()) return mid;
            if(nombreBuscar < lista[mid]->getNombre()) der = mid - 1;
            else izq = mid + 1;
        }
        return -1; 
    }

    static int busquedaNumero(Pokemons** lista, int numeroBuscar, int size){
        for(int i = 0; i < size; i++){
            if(numeroBuscar == lista[i]->getNumero()) return i;
        }
        return -1;
    }

    static void busquedaTipo(Pokemons** lista, string tipoBuscar, int size){
        int encontrados = 0;
        cout << "\nPokemons de tipo '" << tipoBuscar << "':\n";
        for(int i = 0; i < size; i++){
            if(tipoBuscar == lista[i]->getTipo()){
                lista[i]->imprimirPokemons();
                encontrados++;
            }
        }
        if(encontrados == 0){
            cout << "No se encontraron pokemons de tipo '" << tipoBuscar << "'.\n";
        } else {
            cout << "Total encontrados: " << encontrados << '\n';
        }
    }

    static void mostrarVecinos(Pokemons** lista, const string& nombreBuscar, int size) {
        int idx = busquedaNombre(lista, nombreBuscar, size);
        if (idx == -1) {
            cout << "No se encontro el pokemon: " << nombreBuscar << endl;
            return;
        }

        cout << "\nPokemon encontrado:\n";
        lista[idx]->imprimirPokemons();

        if (idx > 0) {
            cout << "Anterior:\n";
            lista[idx - 1]->imprimirPokemons();
        } else {
            cout << "No hay pokemon anterior.\n";
        }

        if (idx + 1 < size) {
            cout << "Siguiente:\n";
            lista[idx + 1]->imprimirPokemons();
        } else {
            cout << "No hay pokemon siguiente.\n";
        }
    }

    static void listarPorInicial(Pokemons** lista, char letra, int size) {
        char objetivo = tolower(letra);
        int encontrados = 0;
        cout << "\nPokemons que comienzan con '" << letra << "':\n";
        for (int i = 0; i < size; ++i) {
            string nom = lista[i]->getNombre();
            if (!nom.empty() && tolower(nom[0]) == objetivo) {
                lista[i]->imprimirPokemons();
                ++encontrados;
            }
        }
        if (encontrados == 0) {
            cout << "No se encontraron pokemons que comiencen con '" << letra << "'.\n";
        } else {
            cout << "Total encontrados: " << encontrados << '\n';
        }
    }
};
#endif