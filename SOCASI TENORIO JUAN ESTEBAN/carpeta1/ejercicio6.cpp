#include <iostream>
#include <cstdlib> // Para usar la función std::atoi

/**
 * @brief Implementa la búsqueda binaria de forma recursiva.
 *
 * @param arr El arreglo de enteros ordenado donde buscar.
 * @param clave El valor a buscar (la clave).
 * @param bajo El índice inferior del sub-arreglo actual.
 * @param alto El índice superior del sub-arreglo actual.
 * @return El índice de la clave en el arreglo si se encuentra; de lo contrario, -1.
 */
int busquedaBinariaRecursiva(const int arr[], int clave, int bajo, int alto) {
    // 1. Caso Base: Si el índice 'bajo' es mayor que 'alto', el sub-arreglo está vacío.
    if (bajo > alto) {
        return -1; // Clave no encontrada
    }

    // Calcular el índice medio
    // Usar bajo + (alto - bajo) / 2 previene desbordamiento
    int medio = bajo + (alto - bajo) / 2;

    // 2. Si la clave es igual al elemento central:
    if (arr[medio] == clave) {
        return medio; // Clave encontrada
    }
    // 3. Si la clave es menor que el elemento central: buscar en la mitad izquierda.
    else if (clave < arr[medio]) {
        return busquedaBinariaRecursiva(arr, clave, bajo, medio - 1);
    }
    // 4. Si la clave es mayor que el elemento central: buscar en la mitad derecha.
    else { // clave > arr[medio]
        return busquedaBinariaRecursiva(arr, clave, medio + 1, alto);
    }
}

int main(int argc, char* argv[]) {
    // 1. Verificar si se proporcionó la clave como argumento.
    // 'argc' es el contador de argumentos. Debe ser 2 (nombre del programa + clave).
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <clave_a_buscar>" << std::endl;
        return 1; // Código de error
    }

    // Convertir el argumento de línea de comandos (string) a entero.
    // std::atoi convierte el string C a int.
    int clave = std::atoi(argv[1]);

    // 2. Arreglo de datos (DEBE ESTAR ORDENADO)
    // El tamaño del arreglo se calcula automáticamente.
    int datos[] = {10, 25, 30, 44, 55, 62, 78, 81, 93, 105};
    // Calcular el número de elementos.
    const int N = sizeof(datos) / sizeof(datos[0]);

    std::cout << "--- Búsqueda Binaria Recursiva ---" << std::endl;
    std::cout << "Arreglo de datos: {";
    for (int i = 0; i < N; ++i) {
        std::cout << datos[i] << (i < N - 1 ? ", " : "");
    }
    std::cout << "}" << std::endl;
    std::cout << "Clave a buscar: " << clave << std::endl;

    // 3. Llamar a la función recursiva.
    // Se pasa el arreglo, la clave, el índice inicial (0) y el índice final (N - 1).
    int indice = busquedaBinariaRecursiva(datos, clave, 0, N - 1);

    // 4. Mostrar el resultado.
    if (indice != -1) {
        std::cout << "\n✅ Clave encontrada en el índice: " << indice << std::endl;
        std::cout << "El valor en datos[" << indice << "] es: " << datos[indice] << std::endl;
    } else {
        std::cout << "\n❌ Clave " << clave << " no encontrada en el arreglo." << std::endl;
    }

    return 0; // Ejecución exitosa
}