#include <iostream>
#include <vector>

// Función de Búsqueda Binaria Recursiva
/**
 * @brief Busca una clave en un sub-arreglo ordenado usando Búsqueda Binaria.
 * @param arr El vector de enteros donde buscar.
 * @param inicio El índice inicial del sub-arreglo (incluido).
 * @param fin El índice final del sub-arreglo (incluido).
 * @param clave El número que se está buscando.
 * @return int El índice de la clave si se encuentra, o -1 si no se encuentra.
 */
int busquedaBinaria(const std::vector<int>& arr, int inicio, int fin, int clave) {
    // 1. Paso Base: Si el segmento es inválido (la clave no está presente)
    if (inicio > fin) {
        return -1;
    }

    // 2. Calcular el índice del medio
    int medio = inicio + (fin - inicio) / 2;

    // 3. Caso 1: Elemento encontrado
    if (arr[medio] == clave) {
        return medio;
    } 
    // 4. Caso 2: La clave es menor, buscar en la mitad izquierda
    else if (clave < arr[medio]) {
        return busquedaBinaria(arr, inicio, medio - 1, clave);
    } 
    // 5. Caso 3: La clave es mayor, buscar en la mitad derecha
    else { // clave > arr[medio]
        return busquedaBinaria(arr, medio + 1, fin, clave);
    }
}

int main() {
    // --- 1. Definición del Arreglo Ordenado ---
    std::vector<int> datos = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int clave;
    
    // Mostrar el arreglo
    std::cout << "Arreglo de datos (ordenado): ";
    for (int n : datos) {
        std::cout << n << " ";
    }
    std::cout << "\n------------------------------------" << std::endl;

    // --- 2. Solicitar la Clave por Teclado ---
    std::cout << "Ingrese el numero entero que desea buscar (clave): ";
    
    // Leer el número del usuario
    if (!(std::cin >> clave)) {
        std::cerr << "Error: La entrada no es un numero entero valido." << std::endl;
        return 1;
    }

    std::cout << "Buscando la clave: " << clave << std::endl;

    // --- 3. Ejecutar la Búsqueda Binaria Recursiva ---
    int n = datos.size();
    int indice = busquedaBinaria(datos, 0, n - 1, clave);

    // --- 4. Mostrar el Resultado ---
    if (indice != -1) {
        std::cout << "\nClave encontrada El numero " << clave 
                  << " esta en el indice " << indice << "." << std::endl;
    } else {
        std::cout << "\nClave no encontrada. El numero " << clave 
                  << " no esta presente en el arreglo." << std::endl;
    }

    return 0;
}