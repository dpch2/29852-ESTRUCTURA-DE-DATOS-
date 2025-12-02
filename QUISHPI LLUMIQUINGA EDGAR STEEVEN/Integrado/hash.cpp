#include "hash.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

TablaHash::TablaHash() {
    tabla = new NodoHash*[TAMANIO];
    for (int i = 0; i < TAMANIO; i++) {
        tabla[i] = nullptr;
    }
}

TablaHash::~TablaHash() {
    for (int i = 0; i < TAMANIO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            NodoHash* temp = actual;
            actual = actual->siguiente;
            delete[] temp->clave;
            delete temp;
        }
    }
    delete[] tabla;
}

int TablaHash::funcionHash(const char* clave) {
    int hash = 0;
    for (int i = 0; clave[i] != '\0'; i++) {
        hash = (hash * 31 + clave[i]) % TAMANIO;
    }
    return abs(hash) % TAMANIO;
}

void TablaHash::insertar(const char* clave, int valor) {
    int indice = funcionHash(clave);
    
    // Buscar si ya existe
    NodoHash* actual = tabla[indice];
    while (actual != nullptr) {
        if (strcmp(actual->clave, clave) == 0) {
            actual->valor = valor;
            return;
        }
        actual = actual->siguiente;
    }
    
    // Insertar nuevo nodo
    NodoHash* nuevoNodo = new NodoHash();
    nuevoNodo->clave = new char[strlen(clave) + 1];
    strcpy(nuevoNodo->clave, clave);
    nuevoNodo->valor = valor;
    nuevoNodo->siguiente = tabla[indice];
    tabla[indice] = nuevoNodo;
}

int TablaHash::buscar(const char* clave) {
    int indice = funcionHash(clave);
    
    NodoHash* actual = tabla[indice];
    while (actual != nullptr) {
        if (strcmp(actual->clave, clave) == 0) {
            return actual->valor;
        }
        actual = actual->siguiente;
    }
    
    return -1; // No encontrado
}

void TablaHash::eliminar(const char* clave) {
    int indice = funcionHash(clave);
    
    NodoHash* actual = tabla[indice];
    NodoHash* anterior = nullptr;
    
    while (actual != nullptr) {
        if (strcmp(actual->clave, clave) == 0) {
            if (anterior == nullptr) {
                tabla[indice] = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }
            delete[] actual->clave;
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}

int TablaHash::contarPalabras(const char* texto, char separador) {
    int cantidad = 0;
    if (strlen(texto) == 0) return 0;
    
    cantidad = 1;
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == separador) {
            cantidad++;
        }
    }
    return cantidad;
}

/*
 * ========== EJERCICIO: ANALISIS DE FRECUENCIA DE PALABRAS ==========
 * PROBLEMA:
 * Se tiene un texto con palabras separadas por espacios y comas.
 * Se debe contar la frecuencia de cada palabra (ignorando mayusculas/minusculas)
 * y almacenarla en una tabla hash con encadenamiento. Luego, realizar busquedas
 * y mostrar las palabras mas frecuentes. El desafio es manejar colisiones
 * correctamente y normalizar las palabras.
 * 
 * Complejidad promedio: O(n) para insercion y busqueda en tabla hash
 * Espacio: O(n) donde n es la cantidad de palabras unicas
 */
void TablaHash::ejercicio_AnalisisFrecuencia() {
    cout << "\n========== EJERCICIO: ANALISIS DE FRECUENCIA DE PALABRAS ==========" << endl;
    cout << "PROBLEMA: Contar la frecuencia de palabras en un texto usando tabla hash" << endl;
    cout << "con encadenamiento. Manejar mayusculas, puntuacion y encontrar las palabras" << endl;
    cout << "mas frecuentes. Resolver colisiones de hash correctamente." << endl;
    cout << "===================================================================" << endl;
    
    // Texto para analizar
    const char* texto = "programacion programacion es dificil pero programacion es importante, "
                       "c++ c++ es potente, programacion requiere practica y dedicacion.";
    
    cout << "\nTexto a analizar:" << endl;
    cout << texto << endl;
    cout << "\n" << string(70, '=') << endl;
    
    // Crear una copia mutable del texto
    char* textoCopia = new char[strlen(texto) + 1];
    strcpy(textoCopia, texto);
    
    // Procesar palabras
    char separadores[] = " ,.;:!?";
    char* palabra = new char[100];
    int pos = 0;
    int posicionPalabra = 0;
    
    cout << "\nProcesando palabras..." << endl;
    
    for (int i = 0; i <= strlen(textoCopia); i++) {
        bool esSeparador = false;
        
        for (int j = 0; separadores[j] != '\0'; j++) {
            if (textoCopia[i] == separadores[j] || textoCopia[i] == '\0') {
                esSeparador = true;
                break;
            }
        }
        
        if (esSeparador && posicionPalabra > 0) {
            palabra[posicionPalabra] = '\0';
            
            // Convertir a minúsculas
            for (int j = 0; palabra[j] != '\0'; j++) {
                palabra[j] = tolower(palabra[j]);
            }
            
            // Buscar y actualizar frecuencia
            int frecActual = buscar(palabra);
            if (frecActual == -1) {
                insertar(palabra, 1);
            } else {
                insertar(palabra, frecActual + 1);
            }
            
            posicionPalabra = 0;
        } else if (!esSeparador) {
            palabra[posicionPalabra++] = textoCopia[i];
        }
    }
    
    // Mostrar estadisticas de la tabla hash
    cout << "\nEstadisticas de la Tabla Hash:" << endl;
    cout << "Tamanio de tabla: " << TAMANIO << endl;
    
    int nodosUsados = 0;
    int nodosTotal = 0;
    int colisiones = 0;
    
    for (int i = 0; i < TAMANIO; i++) {
        NodoHash* actual = tabla[i];
        if (actual != nullptr) {
            nodosUsados++;
            int contador = 0;
            while (actual != nullptr) {
                nodosTotal++;
                contador++;
                actual = actual->siguiente;
            }
            if (contador > 1) {
                colisiones += (contador - 1);
            }
        }
    }
    
    cout << "Posiciones usadas: " << nodosUsados << endl;
    cout << "Total de palabras unicas: " << nodosTotal << endl;
    cout << "Colisiones detectadas: " << colisiones << endl;
    cout << "Factor de carga: " << (float)nodosTotal / TAMANIO << endl;
    
    // Mostrar todas las palabras y sus frecuencias
    cout << "\n" << string(70, '=') << endl;
    cout << "FRECUENCIA DE PALABRAS:" << endl;
    cout << string(70, '=') << endl;
    
    cout << left;
    cout.width(20);
    cout << "Palabra" << " | ";
    cout.width(10);
    cout << "Frecuencia" << " | ";
    cout << "Hash Index" << endl;
    cout << string(70, '-') << endl;
    
    for (int i = 0; i < TAMANIO; i++) {
        NodoHash* actual = tabla[i];
        while (actual != nullptr) {
            cout.width(20);
            cout << actual->clave << " | ";
            cout.width(10);
            cout << actual->valor << " | ";
            cout << i << endl;
            actual = actual->siguiente;
        }
    }
    
    // Busquedas especificas
    cout << "\n" << string(70, '=') << endl;
    cout << "BUSQUEDAS ESPECIFICAS:" << endl;
    cout << string(70, '=') << endl;
    
    const char* palabrasBuscadas[] = {"programacion", "c++", "dedicacion", "python"};
    
    for (int i = 0; i < 4; i++) {
        int frecuencia = buscar(palabrasBuscadas[i]);
        cout << "Palabra: \"" << palabrasBuscadas[i] << "\" -> ";
        
        if (frecuencia == -1) {
            cout << "NO ENCONTRADA" << endl;
        } else {
            cout << "Frecuencia: " << frecuencia << endl;
        }
    }
    
    // Pasos clave y explicacion
    cout << "\nPasos clave:\n - Se tokeniza el texto por separadores y se normalizan las palabras a minusculas." << endl;
    cout << " - Para cada palabra se busca su entrada en la tabla hash; si no existe se inserta con valor 1," << endl;
    cout << "   si ya existe se actualiza la frecuencia (encadenamiento maneja colisiones)." << endl;
    cout << "Por que pasa esto:\n - La tabla hash reduce el tiempo de busqueda e insercion promedio a O(1)," << endl;
    cout << "   por eso es adecuada para conteo de frecuencias; el encadenamiento permite" << endl;
    cout << "   resolver colisiones sin perder informacion de palabras unicas." << endl;

    // Liberar memoria
    delete[] textoCopia;
    delete[] palabra;
}
