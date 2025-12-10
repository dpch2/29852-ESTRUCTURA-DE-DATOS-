#ifndef MENU_HPP
#define MENU_HPP
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "ABB/ABB.hpp"
#include "AVL/AVL.hpp"

class Menu {
private:
    ABB<int> arbolABB;
    AVL<int> arbolAVL;
    int tipoArbol; // 0 = sin seleccionar, 1 = ABB, 2 = AVL
    int opcionSeleccionada;
    
    // Funciones auxiliares
    void limpiarPantalla();
    void mostrarMenuPrincipal();
    void mostrarMenuArbol();
    void ejecutarOpcion(int opcion);
    void ingresarDatos();
    void buscarDato();
    void eliminarDato();
    void mostrarRecorridos();
    void mostrarRecorridoMenu();
    void mostrarArbol();
    void dibujarArbol(Nodo<int>* nodo, int espacio, int altura);
    int calcularAltura(Nodo<int>* nodo);
    void pausar();
    void seleccionarTipoArbol();
    
public:
    Menu();
    void iniciar();
};

#endif