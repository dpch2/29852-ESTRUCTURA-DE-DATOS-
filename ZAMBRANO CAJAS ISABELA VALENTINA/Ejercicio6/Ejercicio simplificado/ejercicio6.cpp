#include <iostream>
#include <cstring>
using namespace std;

class Pokemon {
private:
    char nombre[50];
    int numero;
    char tipo[30];

public:
    Pokemon() {
        nombre[0] = '\0';
        tipo[0] = '\0';
        numero = 0;
    }

    void ingresar() {
        cout << "Nombre: ";
        cin >> nombre;
        cout << "Numero: ";
        cin >> numero;
        cout << "Tipo: ";
        cin >> tipo;
    }

    const char* getNombre() { return nombre; }
    int getNumero() { return numero; }
    const char* getTipo() { return tipo; }

    void mostrar() {
        cout << "----------------------------------\n";
        cout << "Nombre : " << nombre << "\n";
        cout << "Numero : " << numero << "\n";
        cout << "Tipo   : " << tipo << "\n";
        cout << "----------------------------------\n";
    }
};

class ListaPokemons {
private:
    Pokemon lista[100];
    int tam;

    // Ordenar alfabéticamente por nombre (burbuja simple)
    void ordenar() {
        for (int i = 0; i < tam - 1; i++) {
            for (int j = i + 1; j < tam; j++) {
                if (strcmp(lista[i].getNombre(), lista[j].getNombre()) > 0) {
                    Pokemon temp = lista[i];
                    lista[i] = lista[j];
                    lista[j] = temp;
                }
            }
        }
    }

public:
    ListaPokemons() { tam = 0; }

    void ingresarPokemons(int n) {
        for (int i = 0; i < n; i++) {
            cout << "\nIngresando Pokemon #" << (i + 1) << "\n";
            lista[i].ingresar();
        }
        tam = n;
        ordenar(); // Ordenar después de ingresar
    }

    // Búsqueda binaria por nombre
    int buscarCobalion() {
        int low = 0;
        int high = tam - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int cmp = strcmp(lista[mid].getNombre(), "Cobalion");
            if (cmp == 0)
                return mid; // encontrado
            else if (cmp < 0)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return -1; // no encontrado
    }

    void mostrarCobalion() {
        int pos = buscarCobalion();
        if (pos != -1) {
            cout << "\n*** Cobalion ENCONTRADO ***\n";
            lista[pos].mostrar();
        } else {
            cout << "\nCobalion NO se encuentra en la lista.\n";
        }
    }
};

int main() {
    ListaPokemons pokedex;

    int n;
    cout << "Cuantos Pokemons desea ingresar? ";
    cin >> n;

    pokedex.ingresarPokemons(n);
    pokedex.mostrarCobalion();

    return 0;
}
