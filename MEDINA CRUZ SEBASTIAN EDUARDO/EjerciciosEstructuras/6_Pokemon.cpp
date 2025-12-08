#include <iostream>
using namespace std;

int Binaria(int array[], int n, int buscado)
{
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;
        if (array[medio] == buscado)
        {
            return medio;
        }
        else if (array[medio] < buscado)
        {
            inicio = medio + 1;
        }
        else
        {
            fin = medio - 1;
        }
    }
    return -1;
}

int main()
{
    int numeros[] = {1, 4, 7, 10, 25, 39, 52};
    string nombres[] = {"Bulbasaur", "Charmander", "Squirtle", "Caterpie", "Pikachu", "Jigglypuff", "Meowth"};
    string tipos[] = {"Planta", "Fuego", "Agua", "Bicho", "Eléctrico", "Normal", "Normal"};

    int buscado = 7;
    int n = sizeof(numeros) / sizeof(numeros[0]);

    int pos = Binaria(numeros, n, buscado);

    if (pos != -1)
    {
        cout << "Pokemon encontrado:\n";
        cout << "Numero en la pokedex: " << numeros[pos] << endl;
        cout << "Nombre: " << nombres[pos] << endl;
        cout << "Tipo: " << tipos[pos] << endl;
    }
    else
    {
        cout << "El Pokémon Nº 007 NO está en la lista.\n";
    }

    return 0;
}