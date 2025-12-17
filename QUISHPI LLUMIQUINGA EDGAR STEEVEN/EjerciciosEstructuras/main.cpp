#include <iostream>
#include "resolucionEjercicios.h"
#include <windows.h>

using namespace std;
int main() {
    resolucionEjercicios resolucion;
    int ejercicio;
    do{
    cout << "Escoja un ejercicio: \n 1. Ejercicio 1 \n 2. Ejercicio 2 \n 3. Ejercicio 3 \n 4. Ejercicio 4 \n 5. Ejercicio 5 \n 6. Ejercicio 6 \n 7. Ejercicio 7 \n 8. Ejercicio 8 \n 9. Ejercicio 9 \n 10. Ejercicio 10" << endl;
    cin >> ejercicio;
    switch (ejercicio) {
        case 0:
            cout << "Gracias por usar el programa" << endl;
            break;
        case 1:
            cout << "Ejercicio 1" << endl;
            resolucion.ejercicio1();
            system("pause");
            break;
        case 2:
            cout << "Ejercicio 2" << endl;
            resolucion.ejercicio2();
            system("pause");
            break;
        case 3:
            cout << "Ejercicio 3" << endl;
            resolucion.ejercicio3();
            system("pause");
            break;
        case 4:
            cout << "Ejercicio 4" << endl;
            resolucion.ejercicio4();
            system("pause");
            break;
        case 5:
            cout << "Ejercicio 5" << endl;
            resolucion.ejercicio5();
            system("pause");
            break;
        case 6:
            cout << "Ejercicio 6" << endl;
            resolucion.ejercicio6();
            system("pause");
            break;
        case 7:
            cout << "Ejercicio 7" << endl;
            resolucion.ejercicio7();
            system("pause");
            break;
        case 8:
            cout << "Ejercicio 8" << endl;
            resolucion.ejercicio8();
            system("pause");
            break;
        case 9:
            cout << "Ejercicio 9" << endl;
            resolucion.ejercicio9();
            system("pause");
            break;
        case 10:
            cout << "Ejercicio 10" << endl;
            resolucion.ejercicio10();
            system("pause");
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
    }
    system("cls");
    }while(ejercicio!=0);
    
    return 0;
}