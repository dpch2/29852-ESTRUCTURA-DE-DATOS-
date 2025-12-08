/*Localice un entero en un arreglo usando busqueda binaria recursiva, el elemento a buscar
se debe ingresar por linea de comando, el arreglo debe estar previamente ordenado*/
#include <iostream>
using namespace std;

int binaria(int array[], int inicio, int fin, int buscado)
{

    if (inicio > fin)
    {
        return -1;
    }
    int medio = (inicio + fin) / 2;
    if (array[medio] == buscado)
    {
        return medio;
    }
    if (array[medio] < buscado)
    {
        return binaria(array, medio + 1, fin, buscado);
    }

    return binaria(array, inicio, medio - 1, buscado);
}

int main()
{
    int arr[] = {2, 5, 7, 12, 20, 31, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    int buscado = 12;

    int resultado = binaria(arr, 0, n - 1, buscado);

    if (resultado != -1)
        cout << "Elemento encontrado en el índice: " << resultado + 1 << endl;
    else
        cout << "Elemento NO encontrado." << endl;

    return 0;
}