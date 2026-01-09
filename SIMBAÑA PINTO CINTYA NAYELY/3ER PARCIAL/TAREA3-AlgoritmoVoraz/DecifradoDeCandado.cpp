#include <iostream>
#include <fstream>
#include <cstdlib> // rand, srand, malloc
#include <ctime>   // time

using namespace std;

// --- Estructura para Lista Vinculada Manual ---
struct Nodo {
    int dato;
    Nodo* siguiente;
};

struct Lista {
    Nodo* cabeza;
};

// Crear una lista vacía
void crearLista(Lista& lista) {
    lista.cabeza = NULL;
}

// Agregar un elemento al final de la lista
void agregarAlFinal(Lista& lista, int valor) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = valor;
    nuevoNodo->siguiente = NULL;

    if (lista.cabeza == NULL) {
        lista.cabeza = nuevoNodo;
    } else {
        Nodo* actual = lista.cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

// --- Función Auxiliar Manual ---

// Función para verificar si un número ya existe en un arreglo pequeño (para el generador aleatorio)
bool existeEnArreglo(int arreglo[], int tamano, int valor) {
    for(int i = 0; i < tamano; i++) {
        if(arreglo[i] == valor) {
            return true;
        }
    }
    return false;
}

// Función para generar una contraseña secreta VÁLIDA (sin digitos repetidos)
// Ejemplo: 1234 es válido, 1123 no lo es.
int generarSecretoPermutacion() {
    int digitos[4];
    int contador = 0;

    // Llenamos un arreglo de 4 posiciones con números únicos del 1 al 4
    while(contador < 4) {
        int num = (rand() % 4) + 1; 
        if (!existeEnArreglo(digitos, contador, num)) {
            digitos[contador] = num;
            contador++;
        }
    }

    // Convertimos el arreglo [1, 4, 2, 3] al entero 1423
    int secreto = (digitos[0] * 1000) + (digitos[1] * 100) + (digitos[2] * 10) + digitos[3];
    return secreto;
}

// Generar las 24 permutaciones posibles y guardarlas en archivo y lista
void generarPermutaciones(Lista& listaCombinaciones) {
    ofstream archivo;
    archivo.open("permutaciones_candado.txt");

    if (!archivo.is_open()) {
        cout << "Error al crear el archivo." << endl;
        return;
    }

    // Algoritmo para generar permutaciones sin funciones complejas:
    // 4 bucles anidados + validación de unicidad
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if (j == i) continue; // Si j es igual a i, saltamos (no repetir)

            for (int k = 1; k <= 4; k++) {
                if (k == i || k == j) continue; // Si k ya se usó, saltamos

                for (int l = 1; l <= 4; l++) {
                    if (l == i || l == j || l == k) continue; // Si l ya se usó, saltamos

                    // Si llegamos aquí, i, j, k, l son todos distintos
                    int combinacion = (i * 1000) + (j * 100) + (k * 10) + l;

                    // Guardar en archivo
                    archivo << combinacion << endl;

                    // Guardar en lista
                    agregarAlFinal(listaCombinaciones, combinacion);
                }
            }
        }
    }

    archivo.close();
    cout << "Archivo 'permutaciones_candado.txt' generado con las 24 combinaciones." << endl;
}

// Algoritmo Voraz (Greedy)
void algoritmoVoraz(Lista& lista, int objetivo) {
    cout << "\n--- Iniciando Comparacion Voraz ---" << endl;
    
    int intentos = 0;
    bool encontrado = false;
    
    // Recorrer la lista vinculada manualmente
    Nodo* actual = lista.cabeza;
    while (actual != NULL) {
        intentos++;
        int valor = actual->dato;

        // Comparación directa (Voraz: tomar, probar, descartar o aceptar)
        if (valor == objetivo) {
            cout << ">>> EXITO: Contrasena encontrada: " << valor << endl;
            cout << ">>> Intentos necesarios: " << intentos << " de 24." << endl;
            encontrado = true;
            break; // Rompemos el ciclo inmediatamente al encontrarla
        } 
        // Si no es igual, continuamos al siguiente nodo
        actual = actual->siguiente;
    }

    if (!encontrado) {
        cout << "Error: La contrasena generada no es una permutacion valida del 1 al 4." << endl;
    }
}

int main() {
    srand(time(0));

    // 1. Generar secreto aleatorio válido (sin repetir dígitos)
    int secreto = generarSecretoPermutacion();
    
    cout << "Generando contrasena volatil..." << endl;
    // cout << "(DEBUG: Secreto = " << secreto << ")" << endl; // Descomentar para probar

    // 2. Lista para el algoritmo
    Lista listaAtaque;
    crearLista(listaAtaque);

    // 3. Generar las 24 permutaciones
    generarPermutaciones(listaAtaque);

    // 4. Atacar
    algoritmoVoraz(listaAtaque, secreto);

    return 0;
}