#include <iostream>
#include <string>

using namespace std;

struct Pokemon {
    string nombre;
    int numero;
    string tipo;
};

int buscarPokemon(Pokemon arr[], int n, string objetivo) {
    int izquierda = 0;       
    int derecha = n - 1;     

    while (izquierda <= derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio].nombre == objetivo) {
            return medio; 
        }

        if (arr[medio].nombre < objetivo) {
            izquierda = medio + 1;
        }

        else {
            derecha = medio - 1;
        }
    }

    return -1; 
}

int main() {

    Pokemon pokedex[8] = {
        {"Arcanine", 59, "Fuego"},
        {"Bulbasaur", 1, "Planta"},
        {"Charizard", 6, "Fuego"},
        {"Cobalion", 638, "Acero/Lucha"}, 
        {"Eevee", 133, "Normal"},
        {"Lucario", 448, "Lucha/Acero"},
        {"Pikachu", 25, "Electrico"},
        {"Zoroark", 571, "Siniestro"}
    };

    int totalPokemons = 8;
    string objetivo;

    cout << "--- SISTEMA DE BUSQUEDA POKEDEX ---" << endl;
    cout << "Ingrese el nombre del Pokemon que desea buscar: ";
    getline(cin, objetivo);
    cout << "\nBuscando a: " << objetivo << "..." << endl;
    cout << "Metodo aplicado: Busqueda Binaria (O(log n))" << endl;
    cout << "---------------------------------------" << endl;

    int indiceEncontrado = buscarPokemon(pokedex, totalPokemons, objetivo);

    if (indiceEncontrado != -1) {
        cout << "POKEMON ENCONTRADO CON EXITO" << endl;
        cout << "Nombre: " << pokedex[indiceEncontrado].nombre << endl;
        cout << "Numero Pokedex: " << pokedex[indiceEncontrado].numero << endl;
        cout << "Tipo Principal: " << pokedex[indiceEncontrado].tipo << endl;

        cout << "\n(Nota tecnica: Se encontro en el indice " << indiceEncontrado << " del arreglo)" << endl;
    } else {
        cout << "El Pokemon " << objetivo << " no se encuentra en la lista." << endl;
    }

    return 0;
}