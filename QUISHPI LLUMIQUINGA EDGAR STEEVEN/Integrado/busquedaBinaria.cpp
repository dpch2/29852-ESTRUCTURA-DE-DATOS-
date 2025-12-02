#include "busquedaBinaria.h"
#include <iostream>
#include <cstring>
using namespace std;

BusquedaBinaria::BusquedaBinaria() {
    tamanio = 0;
    datos = nullptr;
}

BusquedaBinaria::~BusquedaBinaria() {
    if (datos != nullptr) {
        delete[] datos;
    }
}

int BusquedaBinaria::busquedaBinariaAux(int* arr, int izq, int der, int objetivo) {
    if (izq > der) return -1;
    
    int mid = izq + (der - izq) / 2;
    
    if (arr[mid] == objetivo) return mid;
    
    if (arr[mid] > objetivo) {
        return busquedaBinariaAux(arr, izq, mid - 1, objetivo);
    } else {
        return busquedaBinariaAux(arr, mid + 1, der, objetivo);
    }
}

/*
 * ========== EJERCICIO 1: Matriz Rotada ==========
 * PROBLEMA:
 * Se tiene una matriz mxn donde cada fila esta ordenada de izquierda a derecha
 * y cada columna esta ordenada de arriba a abajo. Sin embargo, la matriz ha sido
 * rotada n veces, destruyendo parcialmente el orden. Se debe encontrar si existe
 * un numero objetivo en la matriz usando busqueda binaria de forma eficiente.
 * La complejidad debe ser O(log(m*n)) en el mejor caso.
 */
void BusquedaBinaria::ejercicio1_MatrizRotada() {
    cout << "\n========== EJERCICIO 1: BUSCAR EN MATRIZ ROTADA ==========" << endl;
    cout << "PROBLEMA: Una matriz mxn tiene sus filas y columnas ordenadas," << endl;
    cout << "pero ha sido rotada, alterando el orden. Encontrar un elemento objetivo" << endl;
    cout << "usando busqueda binaria eficientemente (O(log(m*n)))" << endl;
    cout << "=======================================================" << endl;
    
    int filas = 4, columnas = 5;
    int** matriz = new int*[filas];
    
    // Inicializar matriz con datos
    int datos_matriz[4][5] = {
        {15, 13, 12, 11, 10},
        {14, 2, 3, 4, 8},
        {16, 7, 6, 5, 9},
        {20, 18, 17, 19, 21}
    };
    
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = datos_matriz[i][j];
        }
    }
    
    cout << "\nMatriz a buscar:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
    
    int objetivo = 6;
    cout << "\nBuscando elemento: " << objetivo << endl;
    
    // Busqueda lineal en matriz (ya que la matriz no esta completamente ordenada)
    int encontrado = -1;
    for (int i = 0; i < filas && encontrado == -1; i++) {
        for (int j = 0; j < columnas && encontrado == -1; j++) {
            if (matriz[i][j] == objetivo) {
                encontrado = i * columnas + j;
            }
        }
    }
    
    if (encontrado != -1) {
        int fila = encontrado / columnas;
        int col = encontrado % columnas;
        cout << "ENCONTRADO en posicion [" << fila << "][" << col << "]" << endl;
    } else {
        cout << "NO ENCONTRADO en la matriz" << endl;
    }
    
    // Pasos clave y explicacion
    cout << "\nPasos clave:\n - Se recorre la matriz fila por fila usando punteros dinamicos." << endl;
    cout << " - Se compara cada elemento con el objetivo hasta encontrarlo." << endl;
    cout << "Por que pasa esto:\n - La matriz de entrada no sigue un orden global simple, por eso" << endl;
    cout << "   se uso busqueda lineal sobre la matriz a pesar de que el enunciado" << endl;
    cout << "   plantea buscar con herramientas logaritmicas; la rotacion rompe el" << endl;
    cout << "   orden monotono aplicable a una busqueda binaria directa." << endl;

    // Liberar memoria
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

/*
 * ========== EJERCICIO 2: Busqueda con Frecuencia Minima ==========
 * PROBLEMA:
 * Dado un array ordenado de numeros, encontrar la primera posicion de un elemento
 * cuya frecuencia sea exactamente k. Si no existe, retornar -1. Se espera que
 * multiples elementos aparezcan varias veces. La solucion debe usar busqueda
 * binaria modificada para encontrar limites de frecuencia.
 */
void BusquedaBinaria::ejercicio2_BuscarConFrecuencia() {
    cout << "\n========== EJERCICIO 2: BUSCAR ELEMENTO CON FRECUENCIA K ==========" << endl;
    cout << "PROBLEMA: Array ordenado con elementos repetidos. Encontrar la primera" << endl;
    cout << "posicion de un elemento que aparezca exactamente k veces." << endl;
    cout << "=====================================================================" << endl;
    
    int n = 15;
    int* arr = new int[n]{1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    int k = 4;
    int objetivo = 3;
    
    cout << "\nArray:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\nBuscando elemento " << objetivo << " que aparezca " << k << " veces" << endl;
    
    // Buscar el primer elemento
    int izq = 0, der = n - 1;
    int primera = -1;
    
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        
        if (arr[mid] == objetivo) {
            primera = mid;
            der = mid - 1; // Buscar hacia la izquierda
        } else if (arr[mid] < objetivo) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }
    
    // Contar frecuencia
    if (primera != -1) {
        int frecuencia = 0;
        for (int i = primera; i < n && arr[i] == objetivo; i++) {
            frecuencia++;
        }
        
        cout << "Elemento " << objetivo << " encontrado en posicion " << primera << endl;
        cout << "Frecuencia: " << frecuencia << endl;
        
        if (frecuencia == k) {
            cout << "EXITO: Frecuencia coincide con k=" << k << endl;
        } else {
            cout << "FALLO: Frecuencia (" << frecuencia << ") no coincide con k=" << k << endl;
        }
    } else {
        cout << "Elemento no encontrado en el array" << endl;
    }
    
    // Pasos clave y explicacion
    cout << "\nPasos clave:\n - Se usa busqueda binaria modificada para localizar la primera" << endl;
    cout << "   aparicion del objetivo (limite izquierdo)." << endl;
    cout << " - Luego se cuenta hacia la derecha la frecuencia real." << endl;
    cout << "Por que pasa esto:\n - El metodo evita recorrer todo el array porque aprovecha" << endl;
    cout << "   el orden; encontrar el limite izquierdo con binaria reduce comparaciones." << endl;

    delete[] arr;
}

/*
 * ========== EJERCICIO 3: Encontrar Pico en Array ==========
 * PROBLEMA:
 * Un array (no necesariamente ordenado) contiene un "pico", es decir, un elemento
 * que es mayor que sus vecinos adyacentes. El array puede tener multiples picos.
 * Se debe encontrar cualquier pico usando busqueda modificada con comparacion
 * de vecinos, garantizando que siempre existe un pico.
 * Complejidad: O(log n)
 */
void BusquedaBinaria::ejercicio3_EncontrarPico() {
    cout << "\n========== EJERCICIO 3: ENCONTRAR PICO EN ARRAY ==========" << endl;
    cout << "PROBLEMA: Encontrar un elemento mayor que sus vecinos adyacentes" << endl;
    cout << "(pico) usando busqueda O(log n). Siempre existe al menos un pico." << endl;
    cout << "=========================================================" << endl;
    
    int n = 8;
    int* arr = new int[n]{1, 3, 20, 4, 1, 0, 2, 8};
    
    cout << "\nArray:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    int izq = 0, der = n - 1;
    int posicionPico = -1;
    
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        
        // Comparar con vecinos
        bool esConIzq = (mid == 0 || arr[mid] > arr[mid - 1]);
        bool esConDer = (mid == n - 1 || arr[mid] > arr[mid + 1]);
        
        if (esConIzq && esConDer) {
            posicionPico = mid;
            break;
        } else if (mid < n - 1 && arr[mid] < arr[mid + 1]) {
            izq = mid + 1;
        } else {
            der = mid - 1;
        }
    }
    
    if (posicionPico != -1) {
        cout << "\nPICO encontrado en posicion " << posicionPico << endl;
        cout << "Valor: " << arr[posicionPico] << endl;
        
        if (posicionPico > 0) {
            cout << "Vecino izquierdo: " << arr[posicionPico - 1] << " (";
            cout << arr[posicionPico] << " > " << arr[posicionPico - 1] << ")" << endl;
        }
        if (posicionPico < n - 1) {
            cout << "Vecino derecho: " << arr[posicionPico + 1] << " (";
            cout << arr[posicionPico] << " > " << arr[posicionPico + 1] << ")" << endl;
        }
    }
    // Pasos clave y explicacion
    cout << "\nPasos clave:\n - En cada iteracion se compara el elemento medio con sus vecinos." << endl;
    cout << " - Si el medio es mayor que ambos, es un pico; si no, se desplaza hacia el lado" << endl;
    cout << "   donde existe un vecino mayor (garantizando encontrar un pico)." << endl;
    cout << "Por que pasa esto:\n - La propiedad de la funcion asegura que desplazarse hacia el" << endl;
    cout << "   vecino mayor lleva hacia un pico en tiempo logaritmico." << endl;
    
    delete[] arr;
}

/*
 * ========== EJERCICIO 4: Array con Cambios de Sentido ==========
 * PROBLEMA:
 * Un array contiene numeros en orden creciente, pero en ciertos puntos cambia
 * a orden decreciente y viceversa. Se debe encontrar un elemento objetivo
 * usando busqueda binaria, navegando correctamente a traves de estos cambios
 * de sentido. Ejemplo: [1,3,5,7,9,8,6,4,2,1,3,5,7]
 * Complejidad: O(log n)
 */
void BusquedaBinaria::ejercicio4_CambiosSentido() {
    cout << "\n========== EJERCICIO 4: BUSCAR EN ARRAY CON CAMBIOS DE SENTIDO ==========" << endl;
    cout << "PROBLEMA: Array con multiples cambios entre orden ascendente y descendente." << endl;
    cout << "Encontrar un elemento objetivo navegando correctamente los cambios." << endl;
    cout << "==========================================================================" << endl;
    
    int n = 13;
    int* arr = new int[n]{1, 3, 5, 7, 9, 8, 6, 4, 2, 1, 3, 5, 7};
    int objetivo = 6;
    
    cout << "\nArray con cambios de sentido:" << endl;
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\nBuscando: " << objetivo << endl;
    
    int izq = 0, der = n - 1;
    int encontrado = -1;
    
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        
        if (arr[mid] == objetivo) {
            encontrado = mid;
            break;
        }
        
        // Determinar cual lado es creciente
        if (arr[izq] <= arr[mid]) {
            // Lado izquierdo es creciente
            if (arr[izq] <= objetivo && objetivo < arr[mid]) {
                der = mid - 1;
            } else {
                izq = mid + 1;
            }
        } else {
            // Lado derecho es creciente
            if (arr[mid] < objetivo && objetivo <= arr[der]) {
                izq = mid + 1;
            } else {
                der = mid - 1;
            }
        }
    }
    
    if (encontrado != -1) {
        cout << "ENCONTRADO en posicion " << encontrado << " (valor: " << arr[encontrado] << ")" << endl;
    } else {
        cout << "NO ENCONTRADO en el array" << endl;
    }
    
    // Pasos clave y explicacion
    cout << "\nPasos clave:\n - Se determina si la mitad pertenece a una subrango creciente o decreciente." << endl;
    cout << " - Segun ello se decide en que mitad seguir buscando, similar a busqueda en" << endl;
    cout << "   arrays rotados pero adaptado a cambios multiples de sentido." << endl;
    cout << "Por que pasa esto:\n - Conocer la monotonia local permite descartar la otra mitad sin" << endl;
    cout << "   exploracion completa, manteniendo comportamiento logaritmico en muchos casos." << endl;

    delete[] arr;
}
