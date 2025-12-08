#ifndef BUSQUEDA_HPP
#define BUSQUEDA_HPP
#include "Personajes.hpp"
#include <string>

using namespace std;

class Busqueda{

    public:
    static int busquedaNombre(Personaje** listaBuscar, string nombreBusqueda, int size){
        int izq=0;
        int der=size-1;

            while(izq<=der){

                int mitad=izq+(der-izq)/2;

                if(nombreBusqueda==listaBuscar[mitad]->getNombre()){
                return mitad;
                }
                if(nombreBusqueda<listaBuscar[mitad]->getNombre()){
                    der=mitad-1;
                }
                else if(nombreBusqueda>listaBuscar[mitad]->getNombre()){
                    izq=mitad+1;
                }
        }
        return -1; // Retorna -1 si no se encuentra el elemento
    }
};

#endif