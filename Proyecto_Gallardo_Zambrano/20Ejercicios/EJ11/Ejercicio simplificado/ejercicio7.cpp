#include <iostream>
#include <cstring>
using namespace std;

class Personaje {
private:
    char nombre[50];
    int anio;

public:
    Personaje() {
        nombre[0] = '\0';
        anio = 0;
    }

    void ingresar() {
        cout << "Nombre del personaje: ";
        cin >> nombre;
        cout << "Año de primera aparición: ";
        cin >> anio;
    }

    int getAnio() { return anio; }
    const char* getNombre() { return nombre; }
};

class MCU {
private:
    Personaje lista[100];
    char primeros[100][50];
    char ultimos[100][50];
    int n, cantPrimeros, cantUltimos;
    int anioMin, anioMax;

public:
    MCU() {
        n = 0;
        cantPrimeros = 0;
        cantUltimos = 0;
        anioMin = 9999;
        anioMax = -1;
    }

    void ingresarPersonajes(int cantidad) {
        n = cantidad;

        for (int i = 0; i < n; i++) {
            cout << "\nPersonaje #" << (i + 1) << "\n";
            lista[i].ingresar();

            int anio = lista[i].getAnio();
            const char* nombre = lista[i].getNombre();

            // Actualizar primeros
            if (anio < anioMin) {
                anioMin = anio;
                cantPrimeros = 0;
                strcpy(primeros[cantPrimeros++], nombre);
            } else if (anio == anioMin) {
                strcpy(primeros[cantPrimeros++], nombre);
            }

            // Actualizar últimos
            if (anio > anioMax) {
                anioMax = anio;
                cantUltimos = 0;
                strcpy(ultimos[cantUltimos++], nombre);
            } else if (anio == anioMax) {
                strcpy(ultimos[cantUltimos++], nombre);
            }
        }
    }

    void mostrarResultados() {
        cout << "\n===== Primeros personajes del MCU =====\n";
        for (int i = 0; i < cantPrimeros; i++)
            cout << primeros[i] << " (Año " << anioMin << ")\n";

        cout << "\n===== Últimos personajes del MCU =====\n";
        for (int i = 0; i < cantUltimos; i++)
            cout << ultimos[i] << " (Año " << anioMax << ")\n";
    }
};

int main() {
    MCU universo;
    int n;

    cout << "¿Cuántos personajes desea ingresar? ";
    cin >> n;

    universo.ingresarPersonajes(n);
    universo.mostrarResultados();

    return 0;
}
