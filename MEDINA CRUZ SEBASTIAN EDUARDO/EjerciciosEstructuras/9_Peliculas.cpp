#include <iostream>
using namespace std;

// Búsqueda binaria por título
int busquedaBinaria(string titulos[], int n, string buscado)
{
    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;

        if (titulos[medio] == buscado)
            return medio;

        if (titulos[medio] < buscado)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }

    return -1;
}

void ordenar(string titulos[], int anio[], long long recaudacion[], int valoracion[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {

            if (titulos[j] > titulos[j + 1])
            {

                string tempT = titulos[j];
                titulos[j] = titulos[j + 1];
                titulos[j + 1] = tempT;

                int tempA = anio[j];
                anio[j] = anio[j + 1];
                anio[j + 1] = tempA;

                long tempR = recaudacion[j];
                recaudacion[j] = recaudacion[j + 1];
                recaudacion[j + 1] = tempR;

                int tempV = valoracion[j];
                valoracion[j] = valoracion[j + 1];
                valoracion[j + 1] = tempV;
            }
        }
    }
}

int main()
{

    string titulos[] = {
        "Avengers: Infinity War",
        "Star Wars: The Return of Jedi",
        "Avatar",
        "Iron Man",
        "Spider-Man: No Way Home"};

    int anio[] = {2018, 1983, 2009, 2008, 2021};
    long long recaudacion[] = {2048000000, 475000000, 2847000000, 585000000, 1900000000};
    int valoracion[] = {5, 4, 5, 4, 5};

    int n = sizeof(titulos) / sizeof(titulos[0]);

    ordenar(titulos, anio, recaudacion, valoracion, n);

    int posInfinity = busquedaBinaria(titulos, n, "Avengers: Infinity War");
    int posStarWars = busquedaBinaria(titulos, n, "Star Wars: The Return of Jedi");

    if (posInfinity != -1)
    {
        cout << "Informacion de \"Avengers: Infinity War\":\n";
        cout << "Anio: " << anio[posInfinity] << endl;
        cout << "Recaudacion: $" << recaudacion[posInfinity] << endl;
        cout << "Valoracion: " << valoracion[posInfinity] << "/5\n";
    }
    else
    {
        cout << "\"Avengers: Infinity War\" NO esta en la lista.\n";
    }

    cout << "\n";

    if (posStarWars != -1)
    {
        cout << "\"Star Wars: The Return of Jedi\" esta en la posicion ordenada: "
             << posStarWars << endl;
    }
    else
    {
        cout << "\"Star Wars: The Return of Jedi\" NO esta en la lista.\n";
    }

    return 0;
}