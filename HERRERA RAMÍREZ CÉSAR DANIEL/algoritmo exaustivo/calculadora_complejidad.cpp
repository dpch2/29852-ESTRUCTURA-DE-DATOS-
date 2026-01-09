#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream archivo("codigo.txt");

    if (!archivo)
    {
        cout << "No se pudo abrir el archivo.\n";
        return 1;
    }

    string linea;
    int bucles = 0;
    int recursividad = 0;
    int profundidad = 0;
    int max_profundidad = 0;

    while (getline(archivo, linea))
    {
        // Detectar bucles
        if (linea.find("for") != string::npos ||
            linea.find("while") != string::npos)
        {
            bucles++;
            profundidad++;
            if (profundidad > max_profundidad)
                max_profundidad = profundidad;
        }

        // Detectar cierre de bloque
        if (linea.find("}") != string::npos)
        {
            if (profundidad > 0)
                profundidad--;
        }

        // Detectar recursividad básica
        if (linea.find("funcion") != string::npos &&
            linea.find("(") != string::npos)
        {
            recursividad++;
        }
    }

    archivo.close();

    cout << "\n===== RESULTADO DEL ANALISIS =====\n";

    if (recursividad > 0 && max_profundidad > 0)
    {
        cout << "Complejidad estimada: O(2^n) o O(n!) (Busqueda Exhaustiva)\n";
    }
    else if (max_profundidad == 1)
    {
        cout << "Complejidad estimada: O(n)\n";
    }
    else if (max_profundidad == 2)
    {
        cout << "Complejidad estimada: O(n^2)\n";
    }
    else if (max_profundidad == 3)
    {
        cout << "Complejidad estimada: O(n^3)\n";
    }
    else
    {
        cout << "Complejidad estimada: O(1)\n";
    }

    cout << "Bucles detectados: " << bucles << endl;
    cout << "Profundidad maxima: " << max_profundidad << endl;

    return 0;
}
