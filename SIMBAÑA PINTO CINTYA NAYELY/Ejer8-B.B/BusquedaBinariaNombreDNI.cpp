#include <iostream>
#include <string>
#include <algorithm> // Necesario solo para std::sort

using namespace std;

int busquedaBinariaDNI(int arr[], int n, int objetivo) {
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio] == objetivo) {
            return medio;
        }

        if (arr[medio] < objetivo) {
            izquierda = medio + 1;
        }

        else {
            derecha = medio - 1;
        }
    }

    return -1;
}

int busquedaBinariaNombre(string arr[], int n, string objetivo) {
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio] == objetivo) {
            return medio;
        }
        if (arr[medio] < objetivo) {
            izquierda = medio + 1;
        }
        else {
            derecha = medio - 1;
        }
    }
    return -1;
}

int main() {
    int opcion;
    
    do {
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "1. Buscar DNI" << endl;
        cout << "2. Buscar Nombre" << endl;
        cout << "3. Salir" << endl;
        cout << "====================================" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        cout << endl;

        if (opcion == 1) {
            cout << "=== BUSQUEDA DE DNI ===" << endl;

            int listaDNI[] = {
                100000000, 
                150000000, 
                234661234, 
                300000000, 
                450000000, 
                999999999
            };

            int tamanoDNI = sizeof(listaDNI) / sizeof(listaDNI[0]);
            
            cout << "DNIs disponibles en la lista: ";
            for (int i = 0; i < tamanoDNI; i++) {
                cout << listaDNI[i];
                if (i < tamanoDNI - 1) cout << ", ";
            }
            cout << endl << endl;

            int objetivoDNI;
            cout << "Ingrese el DNI a buscar: ";
            cin >> objetivoDNI;
            
            int resultadoDNI = busquedaBinariaDNI(listaDNI, tamanoDNI, objetivoDNI);

            if (resultadoDNI != -1) {
                cout << "DNI encontrado en el indice: " << resultadoDNI << endl;
                cout << "Matematicamente: listaDNI[" << resultadoDNI << "] == " << objetivoDNI << endl;
            } else {
                cout << "DNI no encontrado." << endl;
            }
            cout << "------------------------------------" << endl;

        } else if (opcion == 2) {
            cout << "=== BUSQUEDA DE NOMBRE ===" << endl;

            string listaNombres[] = {
                "ANA",
                "CARLOS",
                "ESTEBAN",
                "JONAS",   
                "MARIA",
                "ZACK"
            };

            int tamanoNombres = sizeof(listaNombres) / sizeof(listaNombres[0]);
            
            cout << "Nombres disponibles en la lista: ";
            for (int i = 0; i < tamanoNombres; i++) {
                cout << listaNombres[i];
                if (i < tamanoNombres - 1) cout << ", ";
            }
            cout << endl << endl;

            string objetivoNombre;
            cout << "Ingrese el nombre a buscar (en mayusculas): ";
            cin >> objetivoNombre;
            
            // Convertir a mayusculas
            for (char &c : objetivoNombre) {
                c = toupper(c);
            }

            int resultadoNombre = busquedaBinariaNombre(listaNombres, tamanoNombres, objetivoNombre);

            if (resultadoNombre != -1) {
                cout << "Nombre encontrado en el indice: " << resultadoNombre << endl;
                cout << "Matematicamente: listaNombres[" << resultadoNombre << "] == " << objetivoNombre << endl;
            } else {
                cout << "Nombre no encontrado." << endl;
            }
            cout << "------------------------------------" << endl;

        } else if (opcion == 3) {
            cout << "Gracias por usar el programa. Adios!" << endl;
        } else {
            cout << "Opcion invalida. Intente nuevamente." << endl;
        }

    } while (opcion != 3);

    return 0;
}