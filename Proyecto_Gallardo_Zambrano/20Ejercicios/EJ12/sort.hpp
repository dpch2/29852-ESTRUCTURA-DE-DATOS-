#ifndef SORT_HPP
#define SORT_HPP
#include "Peliculas.hpp"

class Sort{
    public:
    // Ordenar por título ascendente
    static void bubbleSortTitulo(Peliculas** array, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j]->getTitulo() > array[j + 1]->getTitulo()) {
                    Peliculas* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    // Ordenar por año ascendente
    static void bubbleSortAnio(Peliculas** array, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j]->getAnio() > array[j + 1]->getAnio()) {
                    Peliculas* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    // Ordenar por recaudación descendente
    static void bubbleSortRecaudacionDesc(Peliculas** array, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j]->getRecaudacion() < array[j + 1]->getRecaudacion()) {
                    Peliculas* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
};
#endif