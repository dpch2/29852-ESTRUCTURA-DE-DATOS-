/*Un vector T tiene cien posiciones, 0.100. Supongamos que las claves de búsqueda de los elementos de la tabla son enteros positivos (por ejemplo, número del DNI). 

Una función de conversión h debe tomar un número arbitrario entero positivo x y convertirlo en un entero en el rango 0.100, esto es, h es una función tal que para un entero positivo x.

h(x)= n, donde n es entero en el rango 0.100
 El método del módulo, tomando 101, será 
h(x) = x mod 101 
Si se tiene el DNI número 234661234, por ejemplo, se tendrá la posición 56: 
234661234 mod 101 = 56

*/
#include <iostream>
using namespace std;

int main() {
    long long dni;  
    long long posicion;

    cout << "Ingrese un DNI (entero positivo): ";
    cin >> dni;

    if (dni < 0) {
        cout << "El DNI debe ser un entero positivo." << endl;
        return 0;
    }

    posicion = dni % 101;

    cout << "La posicion hash para el DNI es: " << posicion << endl;

    return 0;
}
