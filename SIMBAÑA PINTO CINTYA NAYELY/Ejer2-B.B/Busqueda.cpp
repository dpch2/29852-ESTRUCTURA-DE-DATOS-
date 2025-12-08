#include <iostream>
#include <cstdlib> 

using namespace std;

int busquedaBinariaRecursiva(int arr[], int izquierda, int derecha, int objetivo) {
    
    // CASO BASE DE PARADA (Fallo)
    // Matemáticamente: Si el intervalo es vacío (L > R), el elemento no existe.
    if (izquierda > derecha) {
        return -1;
    }

    // CÁLCULO DEL PUNTO MEDIO (Pivote)
    // Se utiliza la forma algebraica segura para evitar Overflow.
    int medio = izquierda + (derecha - izquierda) / 2;

    // CASO BASE DE ÉXITO
    if (arr[medio] == objetivo) {
        return medio;
    }

    // PASO RECURSIVO (Divide et Impera)
    
    // Caso 1: El objetivo es menor que el pivote.
    // Descartamos la mitad derecha. Nuevo intervalo: [izquierda, medio - 1]
    if (objetivo < arr[medio]) {
        return busquedaBinariaRecursiva(arr, izquierda, medio - 1, objetivo);
    }
    
    // Caso 2: El objetivo es mayor que el pivote.
    // Descartamos la mitad izquierda. Nuevo intervalo: [medio + 1, derecha]
    return busquedaBinariaRecursiva(arr, medio + 1, derecha, objetivo);
}

int main(int argc, char* argv[]) {
    // 1. Validación de Argumentos
    if (argc < 2) {
        cout << "Error: Faltan argumentos." << endl;
        cout << "Uso: " << argv[0] << " <numero_a_buscar>" << endl;
        return 1;
    }

    // 2. Extracción y Conversión de Datos
    int clave = atoi(argv[1]);

    // 3. Definición del Espacio de Búsqueda (Arreglo Ordenado)
    int arreglo[] = {3, 7, 10, 15, 22, 35, 48, 55, 67, 89, 94};
    
    // Cálculo dinámico del tamaño del arreglo en tiempo de compilación
    int n = sizeof(arreglo) / sizeof(arreglo[0]);

    cout << "Iniciando busqueda binaria recursiva para la clave: " << clave << endl;
    cout << "Tamano del espacio de busqueda: " << n << " elementos." << endl;

    // 4. Ejecución del Algoritmo
    int resultado = busquedaBinariaRecursiva(arreglo, 0, n - 1, clave);

    // 5. Presentación de Resultados
    if (resultado != -1) {
        cout << "EXITO: El numero se encuentra en el indice " << resultado << "." << endl;
    } else {
        cout << "FALLO: El numero no existe en el arreglo." << endl;
    }

    return 0;
}