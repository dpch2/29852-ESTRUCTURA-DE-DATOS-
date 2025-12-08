#include <iostream>
#include <string>

using namespace std;

struct Personaje {
    string nombre;
    int anio;
};

void swap(Personaje &a, Personaje &b) {
    Personaje temp = a;
    a = b;
    b = temp;
}

int partition(Personaje arr[], int low, int high) {
    int pivot = arr[high].anio;
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].anio <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(Personaje arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int encontrarFinDelMinimo(Personaje arr[], int n, int anioMin) {
    int inicio = 0;
    int fin = n - 1;
    int resultado = -1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        if (arr[medio].anio == anioMin) {
            resultado = medio; 
            inicio = medio + 1; 
        } else if (arr[medio].anio > anioMin) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return resultado;
}

int encontrarInicioDelMaximo(Personaje arr[], int n, int anioMax) {
    int inicio = 0;
    int fin = n - 1;
    int resultado = -1;

    while (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;

        if (arr[medio].anio == anioMax) {
            resultado = medio; 
            fin = medio - 1;   
        } else if (arr[medio].anio < anioMax) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return resultado;
}

int main() {

    int n = 9;

    Personaje* mcu = new Personaje[n];

    mcu[0] = {"Thor", 2011};
    mcu[1] = {"Iron Man", 2008};
    mcu[2] = {"Spider-Man", 2016};
    mcu[3] = {"The Hulk", 2008}; 
    mcu[4] = {"Captain America", 2011};
    mcu[5] = {"Doctor Strange", 2016};
    mcu[6] = {"Photon", 2023};
    mcu[7] = {"Ms. Marvel", 2023}; 
    mcu[8] = {"Black Widow", 2010};

    cout << "Ordenando la lista por anio..." << endl;
    quickSort(mcu, 0, n - 1);

    int anioMin = mcu[0].anio;
    int anioMax = mcu[n - 1].anio;

    int indiceFinMin = encontrarFinDelMinimo(mcu, n, anioMin);

    int indiceInicioMax = encontrarInicioDelMaximo(mcu, n, anioMax);

    cout << "------------------------------------------------" << endl;
    cout << "PRIMEROS PERSONAJES (Anio " << anioMin << "):" << endl;

    for (int i = 0; i <= indiceFinMin; i++) {
        cout << " - " << mcu[i].nombre << endl;
    }

    cout << "------------------------------------------------" << endl;
    cout << "ULTIMOS PERSONAJES (Anio " << anioMax << "):" << endl;

    for (int i = indiceInicioMax; i < n; i++) {
        cout << " - " << mcu[i].nombre << endl;
    }
    cout << "------------------------------------------------" << endl;

    delete[] mcu;

    return 0;
}