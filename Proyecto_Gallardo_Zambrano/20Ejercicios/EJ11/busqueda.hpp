#ifndef BUSQUEDA_HPP
#define BUSQUEDA_HPP
#include "Personajes.hpp"
#include <string>
#include <iostream>
using namespace std;

class Busqueda{
    public:
    // Busqueda binaria por nombre
    static int busquedaNombre(Personajes** lista, string nombreBuscar, int size){
        int izq = 0, der = size - 1;
        while(izq <= der){
            int mid = izq + (der - izq) / 2;
            if(nombreBuscar == lista[mid]->getNombre()) return mid;
            if(nombreBuscar < lista[mid]->getNombre()) der = mid - 1;
            else izq = mid + 1;
        }
        return -1; 
    }

    // Encontrar primer personaje (menor año) sin recorrer
    static void primerPersonaje(Personajes** lista, int size) {
        if (size == 0) {
            cout << "Lista vacia.\n";
            return;
        }
        int minAnio = lista[0]->getAnio();
        int idx = 0;
        for (int i = 1; i < size; i++) {
            if (lista[i]->getAnio() < minAnio) {
                minAnio = lista[i]->getAnio();
                idx = i;
            }
        }
        cout << "\nPrimer personaje(s) en aparecer (anio " << minAnio << "):\n";
        for (int i = 0; i < size; i++) {
            if (lista[i]->getAnio() == minAnio) {
                lista[i]->imprimirPersonaje();
            }
        }
    }

    // Encontrar ultimo personaje (mayor año)
    static void ultimoPersonaje(Personajes** lista, int size) {
        if (size == 0) {
            cout << "Lista vacia.\n";
            return;
        }
        int maxAnio = lista[0]->getAnio();
        int idx = 0;
        for (int i = 1; i < size; i++) {
            if (lista[i]->getAnio() > maxAnio) {
                maxAnio = lista[i]->getAnio();
                idx = i;
            }
        }
        cout << "\nUltimo personaje(s) en aparecer (anio " << maxAnio << "):\n";
        for (int i = 0; i < size; i++) {
            if (lista[i]->getAnio() == maxAnio) {
                lista[i]->imprimirPersonaje();
            }
        }
    }

    // Calcular rango de años
    static void rangoAnios(Personajes** lista, int size) {
        if (size == 0) {
            cout << "Lista vacia.\n";
            return;
        }
        int minAnio = lista[0]->getAnio();
        int maxAnio = lista[0]->getAnio();
        for (int i = 1; i < size; i++) {
            if (lista[i]->getAnio() < minAnio) minAnio = lista[i]->getAnio();
            if (lista[i]->getAnio() > maxAnio) maxAnio = lista[i]->getAnio();
        }
        cout << "\nRango de años: " << minAnio << " a " << maxAnio 
             << " (diferencia: " << (maxAnio - minAnio) << " años)\n";
    }

    // Buscar personaje especifico y mostrar año
    static void buscarPersonajeEspecifico(Personajes** lista, string nombre, int size) {
        for (int i = 0; i < size; i++) {
            if (lista[i]->getNombre() == nombre) {
                cout << "\n" << nombre << " encontrado:\n";
                lista[i]->imprimirPersonaje();
                return;
            }
        }
        cout << "\n" << nombre << " no se encontro en la lista.\n";
    }
};
#endif