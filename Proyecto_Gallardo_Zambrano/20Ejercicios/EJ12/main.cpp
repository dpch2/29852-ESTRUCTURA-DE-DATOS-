/*Se dispone de una lista de películas con la siguiente información: título, año de estreno, recaudación y valoración del público (de 1 a 5), los cuales debemos procesar contemplando las
siguiente tareas:
a. realizar un listado ordenado por título, año de lanzamiento y por recaudación este ultimo
de manera descendente;
b. mostrar toda la información de la película que mas recaudo;
c. listar todas las películas que tenga valoración 5;
d. determinar si la película "Avengers: Infinity War" está en la lista y mostrar
toda su información;
e. indicar en qué posición se encuentra la película "Star Wars: The Return of Jedi";
f. calcular el total recaudado por las películas que en su título incluyen la palabra "Avengers";
g. mostrar todas las películas que se estrenaron en el año 2017;
h. listar todas las películas que comienzan con la palabra "Iron".*/
#include "Peliculas.hpp"
#include "IO.hpp"
#include "sort.hpp"
#include "busqueda.hpp"
#include <iostream>
#include <limits>

using namespace std;

int main(void){
    int size = ingresarDatoTeclado<int>("Ingrese la cantidad de peliculas: ");
    Peliculas* arrayPeliculas = crearMatriz<Peliculas>(size);
    
    for(int i = 0; i < size; i++){
        cout << "\n--- Pelicula " << i+1 << " ---\n";
        string titulo = ingresarDatoTeclado<string>("Ingrese el titulo de la pelicula: ");
        int anio = ingresarDatoTeclado<int>("Ingrese el anio de estreno: ");
        long long recaudacion = ingresarDatoTeclado<long long>("Ingrese la recaudacion en dolares: ");
        int valoracion = ingresarDatoTeclado<int>("Ingrese la valoracion (1-5): ");
        arrayPeliculas[i] = Peliculas(titulo, anio, recaudacion, valoracion);
    }
    
    cout << "\n=== ARREGLO ORIGINAL ===" << endl;
    for(int i = 0; i < size; i++){
        arrayPeliculas[i].imprimirPelicula();
    }
    
    Peliculas** arrayReferencias = new Peliculas*[size];
    for(int i = 0; i < size; i++){
        arrayReferencias[i] = &arrayPeliculas[i];
    }

    // a. Ordenar por título, año y recaudación
    Sort::bubbleSortTitulo(arrayReferencias, size);
    cout << "\n=== a) PELICULAS ORDENADAS POR TITULO ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPelicula();
    }

    Sort::bubbleSortAnio(arrayReferencias, size);
    cout << "\n=== a) PELICULAS ORDENADAS POR ANIO ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPelicula();
    }

    Sort::bubbleSortRecaudacionDesc(arrayReferencias, size);
    cout << "\n=== a) PELICULAS ORDENADAS POR RECAUDACION (DESC) ===" << endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPelicula();
    }

    // b. Película que más recaudó
    Busqueda::peliculaMasRecaudada(arrayReferencias, size);

    // c. Películas con valoración 5
    Busqueda::peliculasValoracion5(arrayReferencias, size);

    // d. Buscar película específica
    Busqueda::buscarPeliculaPorTitulo(arrayReferencias, "Avengers: Infinity War", size);

    // e. Posición de película
    Busqueda::posicionPelicula(arrayReferencias, "Star Wars: The Return of Jedi", size);

    // f. Total recaudado por "Avengers"
    Busqueda::totalRecaudadoAvengers(arrayReferencias, size);

    // g. Películas estrenadas en 2017
    Busqueda::peliculasPorAnio(arrayReferencias, 2017, size);

    // h. Películas que comienzan con "Iron"
    Busqueda::peliculasPorPalabra(arrayReferencias, "Iron", size);

    delete[] arrayReferencias;
    delete[] arrayPeliculas;

    return 0;
}