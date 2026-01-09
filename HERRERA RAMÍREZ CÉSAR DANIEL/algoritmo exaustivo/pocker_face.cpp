#include <iostream>
using namespace std;

int main() {
    int a, b, c;
    int mayor, medio, menor;

    cout << "Ingrese tres numeros distintos:\n";
    cin >> a >> b >> c;

    if (a > b && a > c) {
        mayor = a;
        if (b > c) {
            medio = b;
            menor = c;
        } else {
            medio = c;
            menor = b;
        }
    } 
    else if (b > a && b > c) {
        mayor = b;
        if (a > c) {
            medio = a;
            menor = c;
        } else {
            medio = c;
            menor = a;
        }
    } 
    else {
        mayor = c;
        if (a > b) {
            medio = a;
            menor = b;
        } else {
            medio = b;
            menor = a;
        }
    }

    cout << "Orden de mayor a menor:\n";
    cout << mayor << " " << medio << " " << menor << endl;

    return 0;
}
