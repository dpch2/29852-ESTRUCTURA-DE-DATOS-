#include <iostream>
#include "busquedaBinaria.h"
#include "hash.h"
using namespace std;

int main(){
    cout << "=====================================================================" << endl;
    cout << "    PROGRAMA DE EJERCICIOS: BUSQUEDA BINARIA Y TABLA HASH" << endl;
    cout << "=====================================================================" << endl;
    cout << "Todos los ejercicios utilizan punteros y resolver problemas complejos" << endl;
    cout << "=====================================================================" << endl;
    
    // Crear objeto de búsqueda binaria
    BusquedaBinaria bb;
    
    // Ejecutar los 4 ejercicios de búsqueda binaria
    bb.ejercicio1_MatrizRotada();
    system("pause");
    bb.ejercicio2_BuscarConFrecuencia();
    system("pause");
    bb.ejercicio3_EncontrarPico();
    system("pause");
    bb.ejercicio4_CambiosSentido();
    system("pause");
    
    // Crear objeto de tabla hash y ejecutar ejercicio
    TablaHash th;
    th.ejercicio_AnalisisFrecuencia();
    system("pause");
    cout << "\n=====================================================================" << endl;
    cout << "    FIN DEL PROGRAMA" << endl;
    cout << "=====================================================================" << endl;
    
    return 0;
}
//codigo ejecutar: g++ *.cpp -o main 