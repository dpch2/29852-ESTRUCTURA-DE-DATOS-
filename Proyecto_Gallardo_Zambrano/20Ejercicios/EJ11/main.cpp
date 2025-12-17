/*Se dispone de las lista de superhéroes y villanos de la saga de Marvel Cinematic Universe
(MCU) de los que contamos con la información de nombre del personaje y año de la primera
película en la que apareció; a partir de estos resolver las siguientes actividades:
a. realizar un listado ascendente de los personajes ordenados por su nombre;
b. indicar quien fue el primer y el último personaje en aparecer en una película;
c. realizar un listado de los personajes ordenados de manera descendente por año de aparición;
d. calcular el rango de años entre el primer personaje en aparecer y el último;
e. determinar si los personajes Capitan America y Rocket Raccoon están en la lista y en qué
año aparecieron.*/
#include "Personajes.hpp"
#include "IO.hpp"
#include "sort.hpp"
#include "busqueda.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main(void){
    int size = ingresarDatoTeclado<int>("Ingrese la cantidad de personajes MCU: ");
    Personajes* arrayPersonajes = crearMatriz<Personajes>(size);
    
    for(int i = 0; i < size; i++){
        cout << "\n--- Personaje " << i+1 << " ---\n";
        string nombre = ingresarDatoTeclado<string>("Ingrese el nombre del personaje: ");
        int anio = ingresarDatoTeclado<int>("Ingrese el anio de aparicion: ");
        arrayPersonajes[i] = Personajes(nombre, anio);
    }
    
    cout << "\n=== ARREGLO ORIGINAL ===" << endl;
    for(int i = 0; i < size; i++){
        arrayPersonajes[i].imprimirPersonaje();
    }
    
    Personajes** arrayReferencias = new Personajes*[size];
    for(int i = 0; i < size; i++){
        arrayReferencias[i] = &arrayPersonajes[i];
    }

    // a. Listado ascendente por nombre
    Sort::bubbleSortNombre(arrayReferencias, size);
    cout << "\n=== a) PERSONAJES ORDENADOS ASCENDENTE POR NOMBRE ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPersonaje();
    }

    // b. Primer y último personaje
    cout << "\n=== b) PRIMER Y ULTIMO PERSONAJE EN APARECER ===" << endl;
    Busqueda::primerPersonaje(arrayReferencias, size);
    Busqueda::ultimoPersonaje(arrayReferencias, size);

    // c. Listado descendente por año
    Sort::bubbleSortAnioDesc(arrayReferencias, size);
    cout << "\n=== c) PERSONAJES ORDENADOS DESCENDENTE POR ANIO ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPersonaje();
    }

    // d. Rango de años
    cout << "\n=== d) RANGO DE AÑOS ===" << endl;
    Busqueda::rangoAnios(arrayReferencias, size);

    // e. Buscar personajes específicos
    cout << "\n=== e) BUSQUEDA DE PERSONAJES ESPECIFICOS ===" << endl;
    Busqueda::buscarPersonajeEspecifico(arrayReferencias, "Capitan America", size);
    Busqueda::buscarPersonajeEspecifico(arrayReferencias, "Rocket Raccoon", size);

    delete[] arrayReferencias;
    delete[] arrayPersonajes;

    return 0;
}