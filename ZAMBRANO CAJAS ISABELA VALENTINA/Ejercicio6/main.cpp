/*Se cuenta con una lista de Pokémons, de cada uno de estos se sabe su nombre, número y tipo
(solo considerar uno el principal), con los cuales deberá resolver las siguientes tareas:
a. mostrar un listado de los Pokémons ordenados por números usando el método de ordenamiento por conteo;
b. realizar un listado ordenado por nombre utilizando el método de ordenamiento rápido;
c. mostrar toda la información de pokémon número 640;
d. listar todos los Pokémons que comienzan con la letra T;
e. determinar si existe el Pokémon Cobalion y mostrar toda su información;
f. realizar un listado de todos los Pokémon de tipo eléctrico y calcular cuántos son.*/
#include "Pokemons.hpp"
#include "IO.hpp"
#include "sort.hpp"
#include "busqueda.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main(void){
    int size = ingresarDatoTeclado<int>("Ingrese el tamanio de la lista: ");
    Pokemons* arrayPokemons = crearMatriz<Pokemons>(size);
    
    for(int i = 0; i < size; i++){
        cout << "\n--- Pokemon " << i+1 << " ---\n";
        string nombre = ingresarDatoTeclado<string>("Ingrese el nombre del pokemon: ");
        int numero = ingresarDatoTeclado<int>("Ingrese el numero del pokemon: ");
        string tipo = ingresarDatoTeclado<string>("Ingrese el tipo del pokemon: ");
        arrayPokemons[i] = Pokemons(nombre, numero, tipo);
    }
    
    cout << "\n=== ARREGLO ORIGINAL ===" << endl;
    for(int i = 0; i < size; i++){
        arrayPokemons[i].imprimirPokemons();
    }
    
    Pokemons** arrayReferencias = new Pokemons*[size];
    for(int i = 0; i < size; i++){
        arrayReferencias[i] = &arrayPokemons[i];
    }

    Sort::bubbleSort(arrayReferencias, size);

    cout << "\n=== ARREGLO ORDENADO ALFABETICAMENTE POR NOMBRE ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPokemons();
    }

    char opcion = ingresarDatoTeclado<char>("¿Desea mostrar vecinos de un pokemon? (s/n): ");
    if (opcion == 's' || opcion == 'S') {
        string nombreVecinos = ingresarDatoTeclado<string>("Ingrese el nombre del pokemon: ");
        Busqueda::mostrarVecinos(arrayReferencias, nombreVecinos, size);
    }

    opcion = ingresarDatoTeclado<char>("¿Desea listar pokemons por inicial? (s/n): ");
    if (opcion == 's' || opcion == 'S') {
        char letra = ingresarDatoTeclado<char>("Ingrese la letra inicial: ");
        Busqueda::listarPorInicial(arrayReferencias, letra, size);
    }

    opcion = ingresarDatoTeclado<char>("¿Desea buscar pokemon por numero? (s/n): ");
    if (opcion == 's' || opcion == 'S') {
        int numero = ingresarDatoTeclado<int>("Ingrese el numero del pokemon: ");
        int idx = Busqueda::busquedaNumero(arrayReferencias, numero, size);
        if(idx == -1){
            cout << "No se encontro pokemon con numero: " << numero << endl;
        } else {
            cout << "Pokemon encontrado:\n";
            arrayReferencias[idx]->imprimirPokemons();
        }
    }

    opcion = ingresarDatoTeclado<char>("¿Desea listar pokemons por tipo? (s/n): ");
    if (opcion == 's' || opcion == 'S') {
        string tipo = ingresarDatoTeclado<string>("Ingrese el tipo del pokemon: ");
        Busqueda::busquedaTipo(arrayReferencias, tipo, size);
    }

    delete[] arrayReferencias;
    delete[] arrayPokemons;

    return 0;
}