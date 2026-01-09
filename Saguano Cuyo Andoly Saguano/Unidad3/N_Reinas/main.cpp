#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class NReinas {
private:
    int n;                 // Tamaño del tablero
    int *reinas;           // Puntero dinámico
    int soluciones;
    long combinaciones;
    ofstream archivo;

public:
    // Constructor
    NReinas(int tam) {
        n = tam;
        soluciones = 0;
        combinaciones = 0;

        reinas = new int[n];

        // Inicializamos el arreglo con -1
        for (int i = 0; i < n; i++) {
            *(reinas + i) = -1;
        }

        archivo.open("soluciones_n_reinas.txt");
        archivo << "PROBLEMA DE LAS " << n << " REINAS\n\n";
    }

    // Verifica si la reina en la fila actual es válida
    bool esValida(int fila) {
        for (int i = 0; i < fila; i++) {
            // Misma columna o misma diagonal
            if ( *(reinas + i) == *(reinas + fila) ||
                 abs(fila - i) == abs(*(reinas + fila) - *(reinas + i)) ) {
                return false;
            }
        }
        return true;
    }

    // Muestra el tablero en consola y en el archivo
    void mostrarTablero() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (*(reinas + i) == j) {
                    cout << " Q ";
                    archivo << " Q ";
                } else {
                    cout << " . ";
                    archivo << " . ";
                }
            }
            cout << endl;
            archivo << endl;
        }
        cout << endl;
        archivo << endl;
    }

    // Algoritmo de backtracking (búsqueda exhaustiva con poda)
    void resolver(int fila) {
        // Caso base: todas las reinas colocadas
        if (fila == n) {
            soluciones++;
            cout << "Solucion #" << soluciones << endl;
            archivo << "Solucion #" << soluciones << endl;
            mostrarTablero();
            return;
        }

        // Probamos cada columna en la fila actual
        for (int col = 0; col < n; col++) {
            *(reinas + fila) = col;
            combinaciones++;

            archivo << "Combinacion " << combinaciones << ": ";
            for (int i = 0; i <= fila; i++) {
                archivo << *(reinas + i) << " ";
            }
            archivo << " -> ";

            if (esValida(fila)) {
                archivo << "VALIDA\n";
                resolver(fila + 1);
            } else {
                archivo << "NO VALIDA\n";
            }
        }
    }

    // Método principal
    void ejecutar() {
        resolver(0);

        cout << "Total combinaciones probadas: " << combinaciones << endl;
        cout << "Total soluciones encontradas: " << soluciones << endl;

        archivo << "\n---------------------------------\n";
        archivo << "Total combinaciones probadas: " << combinaciones << endl;
        archivo << "Total soluciones encontradas: " << soluciones << endl;
    }
};

int main() {
    int n;
    cout << "Ingrese el numero de reinas: ";
    cin >> n;

    NReinas problema(n);
    problema.ejecutar();

    return 0;
}
