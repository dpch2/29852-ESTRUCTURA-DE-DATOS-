#ifndef IO_HPP
#define IO_HPP

#include <string>
#include <iostream>

using namespace std;
template<typename T>
T ingresarDatoTeclado(string mensaje){
    cout<<mensaje<<endl;
    T dato;
    cin>>dato;
    return dato;
}

template<typename T> //solo asignar memoria
T* crearMatriz(int size){
    T* matriz= new T[size]();
    return matriz;
}

template<typename T>
T* asignarMatriz(int size){
    T* matriz = new T[size];

    for(int i = 0;i<size;i++){
        matriz[i]=ingresarDatoTeclado<T>("Ingrese dato: ");
    }

    return matriz;
}



#endif