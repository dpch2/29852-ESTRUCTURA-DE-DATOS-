#ifndef PELICULAS_HPP
#define PELICULAS_HPP
#include <string>
#include <iostream>
using namespace std;

class Peliculas{
    private:
        string titulo;
        int anio;
        long long recaudacion;
        int valoracion;

    public:
        Peliculas(string Titulo, int Anio, long long Recaudacion, int Valoracion){
            titulo = Titulo;
            anio = Anio;
            recaudacion = Recaudacion;
            valoracion = Valoracion;
        }

        Peliculas(){
            titulo = "";
            anio = 0;
            recaudacion = 0;
            valoracion = 0;
        }
        
        void setTitulo(string Titulo){ titulo = Titulo; }
        void setAnio(int Anio){ anio = Anio; }
        void setRecaudacion(long long Recaudacion){ recaudacion = Recaudacion; }
        void setValoracion(int Valoracion){ valoracion = Valoracion; }

        string getTitulo() const { return titulo; }
        int getAnio() const { return anio; }
        long long getRecaudacion() const { return recaudacion; }
        int getValoracion() const { return valoracion; }

        void imprimirPelicula() const {
            cout << "Titulo: " << titulo << " | Anio: " << anio 
                 << " | Recaudacion: $" << recaudacion << " | Valoracion: " << valoracion << "/5" << endl;
        }
};
#endif