#ifndef PERSONAJES_HPP
#define PERSONAJES_HPP
#include <string>
#include <iostream>
using namespace std;

class Personajes{
    private:
        string nombre;
        int anio;

    public:
        Personajes(string Nombre, int Anio){
            nombre = Nombre;
            anio = Anio;
        }

        Personajes(){
            nombre = "";
            anio = 0;
        }
        
        void setNombre(string Nombre){ nombre = Nombre; }
        void setAnio(int Anio){ anio = Anio; }

        string getNombre() const { return nombre; }
        int getAnio() const { return anio; }

        void imprimirPersonaje() const {
            cout << "Nombre: " << nombre << " | Anio: " << anio << endl;
        }
};
#endif