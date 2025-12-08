#include <iostream>
#include <string>

using namespace std;

struct Pelicula {
    string titulo;
    int anio;
    double recaudacion; 
    int valoracion;     
};


int busquedaBinaria(Pelicula arr[], int n, string objetivo) {
    int izquierda = 0;         
    int derecha = n - 1;       
    
    while (izquierda <= derecha) {

        int medio = izquierda + (derecha - izquierda) / 2;

        string tituloActual = arr[medio].titulo;

        if (tituloActual == objetivo) {
            return medio; 
        }

        if (objetivo > tituloActual) {
            izquierda = medio + 1;
        }

        else {
            derecha = medio - 1;
        }
    }
    
    return -1;
}

void mostrarInfo(Pelicula p) {
    cout << "-----------------------------------" << endl;
    cout << "Titulo:      " << p.titulo << endl;
    cout << "Anio:        " << p.anio << endl;
    cout << "Recaudacion: $" << p.recaudacion << "M" << endl;
    cout << "Valoracion:  " << p.valoracion << "/5" << endl;
    cout << "-----------------------------------" << endl;
}

void mostrarListaPeliculas(Pelicula arr[], int n) {
    cout << "\n========== LISTA DE PELICULAS ==========" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i].titulo << " (" << arr[i].anio << ")" << endl;
    }
    cout << "========================================" << endl;
}

void mostrarMenu() {
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Buscar una pelicula" << endl;
    cout << "2. Ver todas las peliculas" << endl;
    cout << "3. Salir" << endl;
    cout << "=====================" << endl;
    cout << "Ingrese su opcion: ";
}

int main() {

    const int TAMANO = 5;
    Pelicula lista[TAMANO] = {
        {"Avatar", 2009, 2923.7, 4},
        {"Avengers: Infinity War", 2018, 2048.0, 5}, 
        {"Joker", 2019, 1074.0, 4},
        {"Star Wars: The Return of Jedi", 1983, 475.0, 5}, 
        {"Titanic", 1997, 2201.0, 5}
    };

    cout << "=== PROCESAMIENTO DE PELICULAS USANDO BUSQUEDA BINARIA ===" << endl;

    int opcion = 0;
    
    while (opcion != 3) {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                cout << "\nIngrese el titulo de la pelicula a buscar: ";
                string busqueda;
                getline(cin, busqueda);
                
                int indice = busquedaBinaria(lista, TAMANO, busqueda);
                
                if (indice != -1) {
                    cout << "\n[ENCONTRADA] La pelicula '" << busqueda << "' esta en la lista." << endl;
                    mostrarInfo(lista[indice]);
                } else {
                    cout << "\n[ERROR] La pelicula '" << busqueda << "' no se encuentra en la lista." << endl;
                }
                break;
            }
            
            case 2: {
                mostrarListaPeliculas(lista, TAMANO);
                break;
            }
            
            case 3: {
                cout << "\n¡Hasta luego!" << endl;
                break;
            }
            
            default: {
                cout << "\n[ERROR] Opcion invalida. Intente nuevamente." << endl;
            }
        }
    }

    return 0;
}