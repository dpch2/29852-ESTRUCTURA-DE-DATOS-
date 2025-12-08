/*Buscar mediante busqueda binaria alumnos por legajo,
 la busqueda binaria se aplica sobre el indice,
  se asume que los indices estan ordenados*/
#include <iostream>
using namespace std;
void ingresarDatos(int array[], int &n)
{
    cout << "Ingrese la cantidad de elementos: ";
    cin >> n;
    cout << "Ingrese los elementos ordenados:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Elemento " << i + 1 << ": ";
        cin >> array[i];
    }
}

void Binaria(int array[], int n, int buscado)
{
    int inicio = 0;
    int final = n - 1;
    int medio;

    while (inicio <= final)
    {
        medio = (inicio + final) / 2;
        if (array[medio] == buscado)
        {
            cout << "Elemento encontrado en la posicion: " << medio + 1 << endl;
            return;
        }
        else if (array[medio] < buscado)
        {
            inicio = medio + 1;
        }
        else
        {
            final = medio - 1;
        }
    }
    cout << "Elemento no encontrado!" << endl;
}

int main()
{
    int array[100];
    int n;
    int buscado;

    ingresarDatos(array, n);
    cout << "Ingrese el elemento a buscar: ";
    cin >> buscado;
    Binaria(array, n, buscado);
    return 0;
}