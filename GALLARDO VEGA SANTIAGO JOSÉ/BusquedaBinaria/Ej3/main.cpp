#include <iostream>
#include "busquedabinaria.hpp"
#include <string>
#include <chrono>
#include <thread>

using namespace std;

template<typename T>
T leerDato(string mensaje){
    T dato;
    cout << mensaje;
    cin >> dato;
    return dato;
}

int main(){
    int size = leerDato<int>("Ingrese cuantos datos ingresa: ");
    int* lista = new int[size];
    for (int i = 0; i < size; i++){
        lista[i] = leerDato<int>("Ingrese un numero: ");
    }
    int busqueda = leerDato<int>("Ingrese el numero a buscar: ");
    busquedaBinaria(lista, 0, size - 1, busqueda);
    busquedaBinariaRecursiva(lista, 0, size - 1, busqueda);
    int resultado = busquedaBinariaRecursiva(lista, 0, size - 1, busqueda);
    
    if (resultado != -1){
        cout << "El numero " << busqueda << " se encuentra en la posicion " << resultado << endl;
    }
    else{
        cout << "El numero " << busqueda << " no se encuentra en la lista" << endl;
    }
    delete[] lista;
    return 0;
}