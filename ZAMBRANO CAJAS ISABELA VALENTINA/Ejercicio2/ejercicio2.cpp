/*Localice un entero en un arreglo usando una versión recursiva del algoritmo de
búsqueda binaria. El número que se debe buscar (clave) se debe ingresar como argumento
por línea de comandos. El arreglo de datos debe estar previamente ordenado (requisito de la
búsqueda binaria).
Comparar esta versión recursiva de la búsqueda binaria con la versión iterativa dada en el
capítulo 5.*/

#include <iostream>
#include <cstdlib>      // Para atoi
using namespace std;

// --------------------------
// BÚSQUEDA BINARIA RECURSIVA
// --------------------------
int busquedaBinariaRec(int* inicio, int* fin, int clave) {

    if (inicio > fin)
        return -1;

    int* medio = inicio + (fin - inicio) / 2;

    if (*medio == clave)
        return medio - inicio;   

    if (*medio > clave)
        return busquedaBinariaRec(inicio, medio - 1, clave);

    return busquedaBinariaRec(medio + 1, fin, clave);
}

// --------------------------
// BÚSQUEDA BINARIA ITERATIVA
// --------------------------
int busquedaBinariaIter(int* inicio, int* fin, int clave) {

    int* lo = inicio;
    int* hi = fin;

    while (lo <= hi) {

        int* mid = lo + (hi - lo) / 2;

        if (*mid == clave)
            return mid - inicio;

        if (*mid < clave)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        cout << "Uso: programa <clave_a_buscar>\n";
        return 1;
    }

    int clave = atoi(argv[1]);

    // Arreglo ORDENADO
    int datos[] = {1, 5, 10, 14, 26, 35, 45, 69, 71, 89};
    int n = sizeof(datos) / sizeof(int);

    int* inicio = datos;
    int* fin = datos + (n - 1);

    // ------------------
    // Búsqueda recursiva
    // ------------------
    int posRec = busquedaBinariaRec(inicio, fin, clave);

    // -------------------
    // Búsqueda iterativa
    // -------------------
    int posIter = busquedaBinariaIter(inicio, fin, clave);

    cout << "\nClave buscada: " << clave << "\n";

    if (posRec != -1)
        cout << "Recursiva: encontrado en la posicion " << posRec << "\n";
    else
        cout << "Recursiva: no encontrado.\n";

    if (posIter != -1)
        cout << "Iterativa: encontrado en la posicion " << posIter << "\n";
    else
        cout << "Iterativa: no encontrado.\n";

    return 0;
}
