#include <iostream>
#include <cstring>
using namespace std;

/*
Ejercicio:
Se dispone de la lista de superhéroes y villanos de la saga de Marvel Cinematic Universe (MCU),
de los que contamos con la información de nombre del personaje y año de la primera película en la que apareció.
A partir de estos resolver las siguientes actividades:
- Indicar quién fue el primer personaje en aparecer en una película.
- Indicar quién fue el último personaje en aparecer en una película.
Sin realizar un recorrido completo de la lista (podrían ser más de uno tanto el primero como el último),
utilizando búsquedas binarias.
*/

struct Personaje {
    char nombre[40];
    int anio;
};

// Buscar el primer año con búsqueda binaria
int buscarPrimerAño(Personaje* lista, int n) {
    int inicio = 0, fin = n - 1;
    int indice = -1;
    int anioMin = (lista + 0)->anio;  // primer año

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if ((lista + medio)->anio == anioMin) {
            indice = medio;
            fin = medio - 1; // seguir buscando más a la izquierda
        } else if ((lista + medio)->anio > anioMin) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return indice;
}

// Buscar el último año con búsqueda binaria
int buscarUltimoAño(Personaje* lista, int n) {
    int inicio = 0, fin = n - 1;
    int indice = -1;
    int anioMax = (lista + (n - 1))->anio;  // último año

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        if ((lista + medio)->anio == anioMax) {
            indice = medio;
            inicio = medio + 1; // seguir buscando más a la derecha
        } else if ((lista + medio)->anio < anioMax) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return indice;
}

int main() {
    int n = 7;

    // Lista de personajes ordenada por año de aparición
    Personaje* lista = new Personaje[n]{
        {"Howard Stark", 1954},
        {"Nick Fury", 1963},
        {"Iron Man", 2008},
        {"Black Widow", 2010},
        {"Loki", 2011},
        {"Thor", 2011},
        {"Captain America", 2012}
    };

    int idxPrimero = buscarPrimerAño(lista, n);
    int idxUltimo = buscarUltimoAño(lista, n);

    cout << "Personajes que aparecieron PRIMERO:\n";
    int anioMin = (lista + idxPrimero)->anio;
    for (int i = idxPrimero; i < n && (lista + i)->anio == anioMin; i++) {
        cout << (lista + i)->nombre << " (" << (lista + i)->anio << ")\n";
    }

    cout << "\nPersonajes que aparecieron ULTIMO:\n";
    int anioMax = (lista + idxUltimo)->anio;
    for (int i = idxUltimo; i >= 0 && (lista + i)->anio == anioMax; i--) {
        cout << (lista + i)->nombre << " (" << (lista + i)->anio << ")\n";
    }

    delete[] lista;
    return 0;
}
