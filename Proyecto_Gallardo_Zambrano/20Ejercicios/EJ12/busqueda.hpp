#ifndef BUSQUEDA_HPP
#define BUSQUEDA_HPP
#include "Peliculas.hpp"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Busqueda{
    public:
    // b. Película que más recaudó
    static void peliculaMasRecaudada(Peliculas** lista, int size) {
        if (size == 0) {
            cout << "Lista vacia.\n";
            return;
        }
        int idx = 0;
        long long maxRecaudacion = lista[0]->getRecaudacion();
        for (int i = 1; i < size; i++) {
            if (lista[i]->getRecaudacion() > maxRecaudacion) {
                maxRecaudacion = lista[i]->getRecaudacion();
                idx = i;
            }
        }
        cout << "\n=== b) PELICULA QUE MAS RECAUDO ===" << endl;
        lista[idx]->imprimirPelicula();
    }

    // c. Películas con valoración 5
    static void peliculasValoracion5(Peliculas** lista, int size) {
        cout << "\n=== c) PELICULAS CON VALORACION 5 ===" << endl;
        int encontradas = 0;
        for (int i = 0; i < size; i++) {
            if (lista[i]->getValoracion() == 5) {
                lista[i]->imprimirPelicula();
                encontradas++;
            }
        }
        if (encontradas == 0) cout << "No hay peliculas con valoracion 5.\n";
    }

    // d. Buscar película específica por título
    static void buscarPeliculaPorTitulo(Peliculas** lista, string titulo, int size) {
        for (int i = 0; i < size; i++) {
            if (lista[i]->getTitulo() == titulo) {
                cout << "\n=== d) PELICULA ENCONTRADA ===" << endl;
                lista[i]->imprimirPelicula();
                return;
            }
        }
        cout << "\n" << titulo << " no se encontro en la lista.\n";
    }

    // e. Posición de película específica
    static void posicionPelicula(Peliculas** lista, string titulo, int size) {
        for (int i = 0; i < size; i++) {
            if (lista[i]->getTitulo() == titulo) {
                cout << "\n=== e) POSICION DE " << titulo << " ===" << endl;
                cout << "Se encuentra en posicion: " << i + 1 << endl;
                return;
            }
        }
        cout << "\n" << titulo << " no se encontro en la lista.\n";
    }

    // f. Total recaudado por películas con "Avengers" en el título
    static void totalRecaudadoAvengers(Peliculas** lista, int size) {
        long long total = 0;
        int encontradas = 0;
        for (int i = 0; i < size; i++) {
            string titulo = lista[i]->getTitulo();
            if (titulo.find("Avengers") != string::npos) {
                total += lista[i]->getRecaudacion();
                encontradas++;
            }
        }
        cout << "\n=== f) TOTAL RECAUDADO POR PELICULAS 'AVENGERS' ===" << endl;
        cout << "Peliculas encontradas: " << encontradas << endl;
        cout << "Total recaudado: $" << total << endl;
    }

    // g. Películas estrenadas en año específico
    static void peliculasPorAnio(Peliculas** lista, int anio, int size) {
        cout << "\n=== g) PELICULAS ESTRENADAS EN " << anio << " ===" << endl;
        int encontradas = 0;
        for (int i = 0; i < size; i++) {
            if (lista[i]->getAnio() == anio) {
                lista[i]->imprimirPelicula();
                encontradas++;
            }
        }
        if (encontradas == 0) cout << "No hay peliculas estrenadas en " << anio << ".\n";
    }

    // h. Películas que comienzan con palabra específica
    static void peliculasPorPalabra(Peliculas** lista, string palabra, int size) {
        cout << "\n=== h) PELICULAS QUE COMIENZAN CON '" << palabra << "' ===" << endl;
        int encontradas = 0;
        for (int i = 0; i < size; i++) {
            string titulo = lista[i]->getTitulo();
            if (titulo.find(palabra) == 0) {
                lista[i]->imprimirPelicula();
                encontradas++;
            }
        }
        if (encontradas == 0) cout << "No hay peliculas que comiencen con '" << palabra << "'.\n";
    }
};
#endif