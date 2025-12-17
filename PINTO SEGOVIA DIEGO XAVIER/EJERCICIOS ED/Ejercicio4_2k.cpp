#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Función de Búsqueda Binaria Recursiva Modificada
/**
 * @brief Busca una clave K en un sub-arreglo ordenado. 
 * Asume que K SIEMPRE está en el arreglo, eliminando el caso base de falla.
 * * @param arr El vector de enteros donde buscar.
 * @param inicio El índice inicial del sub-arreglo (incluido).
 * @param fin El índice final del sub-arreglo (incluido).
 * @param clave La clave (K) que se está buscando.
 * @return int El índice de la clave K.
 */
int busquedaBinariaModificada(const std::vector<int>& arr, int inicio, int fin, int clave) {
    // Si la función llega a este punto, significa que el elemento DEBE ser encontrado.
    // El caso base de falla (inicio > fin) se omite intencionalmente.

    // Calculamos el índice del medio
    // Utilizamos (fin - inicio) / 2 para prevenir desbordamiento de enteros.
    int medio = inicio + (fin - inicio) / 2;

    // 1. Caso Base de Éxito: Elemento encontrado
    if (arr[medio] == clave) {
        return medio;
    } 
    // 2. Paso Recursivo: La clave es menor, buscar en la mitad izquierda
    else if (clave < arr[medio]) {
        return busquedaBinariaModificada(arr, inicio, medio - 1, clave);
    } 
    // 3. Paso Recursivo: La clave es mayor, buscar en la mitad derecha
    else { // clave > arr[medio]
        return busquedaBinariaModificada(arr, medio + 1, fin, clave);
    }
}

int main() {
    // Definimos un arreglo ordenado (n=7 para coincidir con el análisis del problema)
    std::vector<int> datos = {5, 10, 15, 20, 25, 30, 35}; 
    int clave;
    int n = datos.size();
    
    std::cout << "--- Busqueda Binaria Modificada (N=" << n << ") ---\n";
    std::cout << "Arreglo: [";
    for (size_t i = 0; i < datos.size(); ++i) {
        std::cout << datos[i] << (i < datos.size() - 1 ? ", " : "");
    }
    std::cout << "]\n";

    // Solicitar la Clave por Teclado
    std::cout << "Ingrese la clave (K) a buscar (Se ASUME que el numero esta en el arreglo): ";
    if (!(std::cin >> clave)) {
        std::cerr << "Error: La entrada no es un numero entero valido." << std::endl;
        return 1;
    }

    // Comprobación de seguridad (solo para demostrar el concepto, ya que la premisa es que SIEMPRE está)
    // En un caso real, un desarrollador podría querer verificar si la premisa se cumple.
    bool estaPresente = false;
    for (int val : datos) {
        if (val == clave) {
            estaPresente = true;
            break;
        }
    }

    if (!estaPresente) {
        std::cout << "\nAdvertencia: Ha ingresado un numero que NO esta en el arreglo (" << clave << ").\n";
        std::cout << "El algoritmo modificado entrara en un bucle infinito (Stack Overflow)\n";
        std::cout << "porque se le instruyo a NO chequear el caso de falla.\n";
        std::cout << "Por favor, ejecute de nuevo e ingrese uno de los numeros: 5, 10, 15, 20, 25, 30, 35.\n";
        return 0; // Salimos de forma segura
    }


    // Ejecutar la Búsqueda
    std::cout << "\nBuscando K = " << clave << "...\n";
    int indice = busquedaBinariaModificada(datos, 0, n - 1, clave);

    // Mostrar el Resultado
    std::cout << "Clave encontrada El numero " << clave 
              << " esta en el indice " << indice << "." << std::endl;

    return 0;
}