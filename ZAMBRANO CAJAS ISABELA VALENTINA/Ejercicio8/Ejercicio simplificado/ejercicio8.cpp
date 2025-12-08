#include <iostream>
#include <string>
using namespace std;

struct Pelicula {
    string titulo;
    int anio;
    double recaudacion;
    double valoracion;
};

// Función de búsqueda binaria por título
int busquedaBinaria(Pelicula* lista, int n, string objetivo) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (lista[mid].titulo == objetivo)
            return mid; // encontrado
        else if (lista[mid].titulo < objetivo)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1; // no encontrado
}

int main() {
    // Lista ordenada alfabéticamente por título
    Pelicula lista[] = {
        {"Avengers: Infinity War", 2018, 2048.4, 4.8},
        {"Iron Man", 2008, 585.2, 4.5},
        {"Star Wars: The Return of Jedi", 1983, 475.1, 4.7}
    };
    int n = sizeof(lista)/sizeof(lista[0]);

    // Para búsqueda binaria, debemos **ordenar la lista alfabéticamente**
    // (aquí ya está ordenada manualmente para el ejemplo)

    // 1️⃣ Buscar "Avengers: Infinity War"
    int posAvengers = busquedaBinaria(lista, n, "Avengers: Infinity War");
    if (posAvengers != -1) {
        cout << "Avengers: Infinity War encontrada:\n";
        cout << "Título: " << lista[posAvengers].titulo << "\n";
        cout << "Año: " << lista[posAvengers].anio << "\n";
        cout << "Recaudación: " << lista[posAvengers].recaudacion << "\n";
        cout << "Valoración: " << lista[posAvengers].valoracion << "\n";
    } else {
        cout << "Avengers: Infinity War no encontrada.\n";
    }

    // 2️⃣ Buscar "Star Wars: The Return of Jedi"
    int posStarWars = busquedaBinaria(lista, n, "Star Wars: The Return of Jedi");
    if (posStarWars != -1) {
        cout << "\nStar Wars: The Return of Jedi está en la posición: " << posStarWars + 1 << "\n";
    } else {
        cout << "Star Wars: The Return of Jedi no encontrada.\n";
    }

    return 0;
}
