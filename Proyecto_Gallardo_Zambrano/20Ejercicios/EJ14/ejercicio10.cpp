/*Un entero de ocho dígitos se puede dividir en grupos de tres, tres y dos
dígitos, los grupos se suman juntos y se truncan si es necesario para que estén en el
rango adecuado de índices.*/

#include <iostream>
using namespace std;

int main() {
    long long dni;
    cout << "Ingrese un DNI de 8 digitos: ";
    cin >> dni;

    long long* p = &dni;

    long long temp = *p;
    long long* q = &temp;

    int g3 = (int)(*q % 100);
    *q /= 100;

    int g2 = (int)(*q % 1000);
    *q /= 1000;

    int g1 = (int)(*q);

    int suma = g1 + g2 + g3;

    int direccion = suma % 1000;

    cout << "Direccion: " << direccion << endl;

    return 0;
}
