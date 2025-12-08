#ifndef PERSONAJES_HPP
#define PERSONAJES_HPP
#include <string>
#include <iostream>
using namespace std;
class Personaje{

    private:

    string Nombre;
    int Posicion;
    
    public:

    Personaje(string Nombre, int Posicion){
        this->Nombre=Nombre;
        this->Posicion=Posicion;
    }
    Personaje(){}

    void setNombre(string Nombre){
        this->Nombre=Nombre;
    }
    void setPosicion(int Posicion){
        this->Posicion=Posicion;
    }

    void imprimirPersonaje(){
        cout<<"Nombre del personaje: "<<Nombre<<endl;
        cout<<"Posicion: "<<Posicion<<endl;
    }


    string getNombre(){
        return Nombre;
    }
    int getPosicion(){
        return Posicion;
    }

};

#endif