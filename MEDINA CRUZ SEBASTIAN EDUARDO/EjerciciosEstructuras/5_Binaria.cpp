#include <iostream>
using namespace std;

int main()
{
    int arr[] = {3, 8, 12, 20, 25, 30};
    int n = 6;

    int buscado = 12;

    int inicio = 0;
    int fin = n - 1;

    while (inicio <= fin)
    {
        int medio = (inicio + fin) / 2;

        if (arr[medio] == buscado)
        {
            cout << "Encontrado en la posicion " << medio + 1 << endl;
            return 0;
        }
        else if (arr[medio] < buscado)
        {
            inicio = medio + 1;
        }
        else
        {
            fin = medio - 1;
        }
    }

    cout << "No encontrado" << endl;
    return 0;
}