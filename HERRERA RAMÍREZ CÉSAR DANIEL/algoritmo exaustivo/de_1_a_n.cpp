/*
calcular la suma de todos los números naturales comprendidos entre 1 y un valor entero 
n. Para ello, se define el problema de manera recursiva considerando que la suma hasta 
n se obtiene evaluando explícitamente cada valor desde 1 hasta 
n, acumulando los resultados parciales. El proceso comienza en el valor máximo 
n y se reduce progresivamente hasta alcanzar el caso base, que ocurre cuando 
n=0, donde la suma es cero. De esta forma, el algoritmo analiza exhaustivamente
cada elemento de la secuencia, asegurando que todos los valores intermedios sean
considerados individualmente. Para el caso n=99, el resultado final obtenido es 4950.
*/

#include <iostream>
using namespace std;

int sumaExhaustiva(int n) {
    if (n == 0) {
        return 0; // caso base
    }
    return n + sumaExhaustiva(n - 1); // evaluación exhaustiva
}

int main() {
    int n = 99;
    int resultado = sumaExhaustiva(n);

    cout << "La suma de 1 hasta " << n << " es: " << resultado << endl;
    return 0;
}


/*
RESPUESTA
Sea n un número natural. Se desea calcular la suma de los números naturales consecutivos
desde 1 hasta n, es decir, S = 1 + 2 + 3 + … + n. Esta suma corresponde a una progresión
aritmética cuyo primer término es 1, cuyo último término es n y cuya cantidad de términos
es n. La suma de una progresión aritmética se obtiene mediante la expresión S = n(1 + n) / 2.
Para el caso particular n = 99, se tiene S = 99(1 + 99) / 2 = 99 · 100 / 2 = 4950. Por lo tanto,
la suma de los números naturales del 1 al 99 es 4950.
*/