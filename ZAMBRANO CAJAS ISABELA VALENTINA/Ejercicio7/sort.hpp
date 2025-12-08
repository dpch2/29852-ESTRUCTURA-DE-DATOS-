#ifndef SORT_HPP
#define SORT_HPP
#include "Personajes.hpp"

class Sort{
    public:
    // Ordenar por nombre ascendente
    static void bubbleSortNombre(Personajes** array, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j]->getNombre() > array[j + 1]->getNombre()) {
                    Personajes* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    // Ordenar por año descendente
    static void bubbleSortAnioDesc(Personajes** array, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j]->getAnio() < array[j + 1]->getAnio()) {
                    Personajes* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
};
#endif