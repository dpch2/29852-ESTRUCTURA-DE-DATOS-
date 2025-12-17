/*Diseñe una variación de Búsqueda Binaria (algoritmo 1.4) que efectúe sólo una
comparación binaria (es decir, la comparación devuelve un resultado booleano) de K con un
elemento del arreglo cada vez que se invoca la función. Pueden hacerse comparaciones
adicionales con variables de intervalo. Analice la corrección de su procedimiento. Sugerencia:
¿Cuándo deberá ser de igualdad (==) la única comparación que se hace?
*/
#include <iostream>
using namespace std;


int busquedaEspecial(int* E, int primero, int ultimo, int K) {

    if (ultimo < primero)
        return -1;

    int* pPrimero = E + primero;
    int* pUltimo  = E + ultimo;


    if (K < *pPrimero || K > *pUltimo)
        return -1;

    int medio = (primero + ultimo) / 2;
    int* pMedio = E + medio;

    if (K == *pMedio)
        return medio;

    if (K <= *pMedio)
        return busquedaEspecial(E, primero, medio - 1, K);
    else
        return busquedaEspecial(E, medio + 1, ultimo, K);
}

int main() {

    int E[] = {1, 7, 9, 14, 19, 24, 31, 42};
    int n = sizeof(E) / sizeof(E[0]);

    int K;
    cout << "Ingrese el valor a buscar: ";
    cin >> K;

    int indice = busquedaEspecial(E, 0, n - 1, K);

    if (indice == -1)
        cout << "No encontrado\n";
    else
        cout << "Encontrado en posicion: " << indice << "\n";

    return 0;
}
