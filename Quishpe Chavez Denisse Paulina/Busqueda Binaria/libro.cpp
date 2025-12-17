#include <iostream>

using namespace std;

long long* grosores;
int N, K;

// Verifica si los libros caben en K estantes con ancho W
bool puedeCaber(long long W) {
    int estantes = 1;
    long long actual = 0;
    
    for (int i = 0; i < N; i++) {
        if (grosores[i] > W) return false;
        
        if (actual + grosores[i] <= W) {
            actual += grosores[i];
        } else {
            estantes++;
            actual = grosores[i];
            if (estantes > K) return false;
        }
    }
    return true;
}

int main() {
    cout << "Libros: ";
    cin >> N;
    cout << "Estantes: ";
    cin >> K;
    
    grosores = new long long[N];
    long long suma = 0, maximo = 0;
    
    cout << "Grosores (cm): ";
    for (int i = 0; i < N; i++) {
        cin >> grosores[i];
        suma += grosores[i];
        if (grosores[i] > maximo) maximo = grosores[i];
    }
    
    // BÚSQUEDA BINARIA
    // Busca el ancho mínimo entre [maximo, suma]
    long long left = maximo;    // Mínimo: el libro más grueso
    long long right = suma;     // Máximo: todos los libros juntos
    long long respuesta = suma;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        if (puedeCaber(mid)) {
            respuesta = mid;
            right = mid - 1;  // Intentar con menos
        } else {
            left = mid + 1;   // Necesitamos más
        }
    }
    
    cout << "\nAncho minimo: " << respuesta << " cm\n";
    
    // Mostrar distribución
    cout << "\nDistribucion:\n";
    int est = 1;
    long long ancho = 0;
    cout << "Estante " << est << ": ";
    
    for (int i = 0; i < N; i++) {
        if (ancho + grosores[i] <= respuesta) {
            cout << grosores[i] << " ";
            ancho += grosores[i];
        } else {
            cout << "(" << ancho << "cm)\n";
            est++;
            cout << "Estante " << est << ": " << grosores[i] << " ";
            ancho = grosores[i];
        }
    }
    cout << "(" << ancho << "cm)\n";
    
    delete[] grosores;
    return 0;
}

// cd libroBiblioteca
// g++ -std=c++11 -o libro.exe libro.cpp
// ./libro.exe
