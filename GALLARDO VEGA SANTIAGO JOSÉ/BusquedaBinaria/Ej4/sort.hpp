#ifndef SORT_HPP
#define SORT_HPP
#include "Personajes.hpp"

class Sort{
public:
    static void bubbleSort(Personaje** array, int size) {
        for (int i = 0; i < size - 1; i++) {
        
            for (int j = 0; j < size - i - 1; j++) {
                
                if (array[j]->getNombre() > array[j + 1]->getNombre()) {
                    
                    Personaje* temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }
};
#endif