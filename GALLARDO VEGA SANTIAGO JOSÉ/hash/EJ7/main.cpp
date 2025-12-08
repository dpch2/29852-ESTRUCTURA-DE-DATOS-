#include <iostream>
using namespace std;

int hashModulo(int x) {
    return x % 101; // Rango 0 a 100
}

int main() {
    int dni = 234661234;
    int posicion = hashModulo(dni);

    cout << "La posicion en la tabla es: " << posicion << endl;
    return 0;
}