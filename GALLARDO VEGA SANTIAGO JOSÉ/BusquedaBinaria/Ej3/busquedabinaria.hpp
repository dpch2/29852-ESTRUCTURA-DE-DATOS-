#pragma once

int busquedaBinariaRecursiva(int* lista, int izq, int der, int size){
    int medio = (izq + der) / 2;
    if (lista[medio] == size){
        return medio;
    }
    else if (lista[medio] > size){
        return busquedaBinariaRecursiva(lista, izq, medio - 1, size);
    }
    else{
        return busquedaBinariaRecursiva(lista, medio + 1, der, size);
    }
}

int busquedaBinaria(int* lista, int izq, int der, int size){
    int medio = (izq + der) / 2;
    while (izq <= der){
        if (lista[medio] == size){
            return medio;
        }
        else if (lista[medio] > size){
            der = medio - 1;
        }
        else{
            izq = medio + 1;
        }
        medio = (izq + der) / 2;
    }
    return -1;
}