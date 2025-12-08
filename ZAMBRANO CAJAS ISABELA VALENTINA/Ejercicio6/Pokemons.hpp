#ifndef POKEMONS_HPP
#define POKEMONS_HPP
#include <string>
#include <iostream>
using namespace std;

class Pokemons{
    private:
        string nombre;
        int numero;
        string tipo;

    public:
        Pokemons(string Nombre, int Numero, string Tipo){
            nombre = Nombre;
            numero = Numero;
            tipo = Tipo;
        }

        Pokemons(){
            nombre = "";
            numero = 0;
            tipo = "";
        }
        
        void setNombre(string Nombre){ nombre = Nombre; }
        void setNumero(int Numero){ numero = Numero; }
        void setTipo(string Tipo){ tipo = Tipo; }

        string getNombre() const { return nombre; }
        int getNumero() const { return numero; }
        string getTipo() const { return tipo; }

        void imprimirPokemons() const {
            cout << "Nombre: " << nombre << " | Numero: " << numero << " | Tipo: " << tipo << endl;
        }
};
#endif