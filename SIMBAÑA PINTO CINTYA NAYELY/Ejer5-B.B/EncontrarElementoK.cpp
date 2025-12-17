#include <iostream>

using namespace std;

int main() {

    int X[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    
    int N = sizeof(X) / sizeof(X[0]); 
    
    int K; 
    
    cout << "Lista ordenada: ";
    for(int i = 0; i < N; i++) cout << X[i] << " ";
    cout << "\n\nIngrese el valor K a buscar: ";
    cin >> K;

    int BAJO = 0;
    int ALTO = N - 1;
    
    int CENTRAL = (BAJO + ALTO) / 2;

    while (BAJO <= ALTO && X[CENTRAL] != K) {
        
        if (K < X[CENTRAL]) {

            ALTO = CENTRAL - 1;
        } else {

            BAJO = CENTRAL + 1;
        }
        
        CENTRAL = (BAJO + ALTO) / 2;
    }

    if (BAJO <= ALTO && X[CENTRAL] == K) {
        cout << "Valor encontrado en el indice: " << CENTRAL << endl;
        cout << "(Posicion " << CENTRAL + 1 << " en lenguaje natural)" << endl;
    } else {
        cout << "Valor no encontrado." << endl;
    }

    return 0;
}