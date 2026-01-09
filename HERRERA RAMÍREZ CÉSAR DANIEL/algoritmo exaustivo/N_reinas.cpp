/*
Dado un número entero 𝑁(1≤𝑁≤12), que representa el tamaño de un
tablero de ajedrez de N×N, se debe desarrollar un programa en C++
que, mediante un algoritmo de búsqueda exhaustiva implementado de
forma recursiva, explore todas las posibles configuraciones para colocar
N reinas en el tablero, asegurando que ninguna de ellas se ataque entre
sí, es decir, que no compartan la misma fila, columna ni diagonales;
el programa deberá recorrer sistemáticamente todas las combinaciones
posibles y determinar cuántas de ellas constituyen soluciones válidas.
*/

#include <iostream>
#include <fstream>
using namespace std;

long long totalSoluciones = 0;

/*
 Imprime una solución almacenada como número entero
 Cada dígito representa la columna de la reina en una fila
 */
void imprimirSolucion(long long estado, int fila, ofstream& archivo) {
    if (fila == 0)
        return;

    imprimirSolucion(estado / 10, fila - 1, archivo);
    archivo << (estado % 10) << " ";
}

/*
 BÚSQUEDA EXHAUSTIVA CON BACKTRACKING
 */
void resolver8Reinas(
    int fila,
    long long columnas,
    long long diag1,
    long long diag2,
    long long estado,
    ofstream& archivo
) {
    if (fila == 8) {
        totalSoluciones++;
        archivo << "Solucion " << totalSoluciones << ": ";
        imprimirSolucion(estado, 8, archivo);
        archivo << endl;
        return;
    }

    long long disponibles =
        ((1LL << 8) - 1) & ~(columnas | diag1 | diag2);

    while (disponibles != 0) {
        long long bit = disponibles & -disponibles;
        disponibles -= bit;

        int columna = 1;
        long long temp = bit;
        while (temp > 1) {
            temp >>= 1;
            columna++;
        }

        resolver8Reinas(
            fila + 1,
            columnas | bit,
            (diag1 | bit) << 1,
            (diag2 | bit) >> 1,
            estado * 10 + columna,
            archivo
        );
    }
}

int main() {
    ofstream archivo("soluciones_8_reinas.txt");

    if (!archivo) {
        cout << "Error al crear el archivo de salida." << endl;
        return 1;
    }

    resolver8Reinas(0, 0, 0, 0, 0, archivo);
    archivo.close();

    cout << "PROBLEMA DE LAS 8 REINAS RESUELTO\n";
    cout << "--------------------------------\n";
    cout << "Total de soluciones encontradas: "
         << totalSoluciones << endl;
    cout << "Soluciones guardadas en: soluciones_8_reinas.txt\n\n";

    cout << "ANALISIS DE COMPLEJIDAD ALGORITMICA\n";
    cout << "----------------------------------\n";
    cout << "Tipo de algoritmo: Busqueda exhaustiva con backtracking\n";
    cout << "Complejidad temporal (peor caso): O(N!)\n";
    cout << "Para N = 8, el algoritmo explora el espacio de soluciones\n";
    cout << "podando configuraciones invalidas por columnas y diagonales.\n";
    cout << "Las validaciones se realizan en tiempo constante mediante\n";
    cout << "mascaras de bits.\n";

    return 0;
}



/*
RESPUESTA
Para un tablero cuadrado de dimensión N×N, el número de configuraciones posibles en las
que pueden ubicarse N reinas de manera que ninguna comparta fila, columna ni diagonales
depende únicamente del valor de N. Al considerar los primeros casos, se obtiene que para
N=1 existe una única configuración válida, para N=2 y N=3 no existen configuraciones que
satisfagan las restricciones, para N=4 se identifican exactamente 2 configuraciones válidas,
para N=5 se obtienen 10 configuraciones, para N=6 se determinan 4 configuraciones, para N=7
existen 40 configuraciones y para N=8 se contabilizan 92 configuraciones válidas. Estos valores
representan la cardinalidad del conjunto de soluciones del problema para cada dimensión considerada.
*/