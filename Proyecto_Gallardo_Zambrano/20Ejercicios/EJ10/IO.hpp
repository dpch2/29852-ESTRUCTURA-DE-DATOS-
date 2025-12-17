#ifndef IO_HPP
#define IO_HPP
#include <string>
#include <iostream>
#include <limits>
using namespace std;

template<typename T>
T ingresarDatoTeclado(string mensaje){
    cout << mensaje << endl;
    T dato;
    while(!(cin >> dato)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada no valida. " << mensaje << endl;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return dato;
}

template<typename T>
T* crearMatriz(int size){
    T* matriz = new T[size]();
    return matriz;
}

template<typename T>
T* asignarMatriz(int size){
    T* matriz = new T[size];
    for(int i = 0; i < size; i++){
        matriz[i] = ingresarDatoTeclado<T>("Ingrese un dato: ");
    }
    return matriz;
}
#endif