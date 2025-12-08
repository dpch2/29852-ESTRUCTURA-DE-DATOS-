#include "resolucionEjercicios.h"
#include <iostream>
#include <string>
#include <cctype> // Para la funcion toupper
#include <climits> // Necesario para INT_MIN y INT_MAX
#include <algorithm> // Necesario para max
using namespace std;
//EJERCICIO 1=====================================================
bool comparacionBinaria(int k, int *arreglo, int n);
void resolucionEjercicios::ejercicio1() {
    cout << "Disene una variacion de Busqueda Binaria (algoritmo 1.4) que efectue solo una comparacion binaria (es decir, la comparacion devuelve un resultado booleano)\n de K con un elemento del arreglo cada vez que se invoca la funcion. Pueden hacerse comparaciones adicionales con variables de intervalo.\n Analice la correccion de su procedimiento. Sugerencia: Cuando debera ser de igualdad (==) la unica comparacion que se hace?\n";
    int k;
    int *arreglo;
    int n;
    cout << "Ingrese el valor de K: ";
    cin >> k;
    do{
    cout << "Ingrese el tamaño del arreglo: ";
    cin >> n;
    }while(n<1);
    arreglo=new int[n];
    for(int i=0; i<n; i++) {
        cout << "Ingrese los valores del arreglo en la posicion " << i << ": ";
        cin >> *(arreglo+i);
    }
    bool resultado=comparacionBinaria(k, arreglo, n);
    cout << "El resultado es: " << (resultado ? "Verdadero" : "Falso") << endl;
    delete []arreglo;
}
bool comparacionBinaria(int k, int *arreglo, int n) {
    int izq=0;
    int der=n-1;
    while(izq<der) {
        int medio=(izq+der+1)/2;
        if(k<*(arreglo+medio)) {
            der=medio-1;
        }
        else {
            izq=medio;
        }
    }
    return (izq<n && *(arreglo+izq)==k);
}
//EJERCICIO 2=====================================================
int busquedaEnArregloInfinito(int x, int *E, int maxint);
int busquedaBinariaEnRango(int x, int *E, int izq, int der, int maxint);
void resolucionEjercicios::ejercicio2() {
cout << "Las primeras n celdas del arreglo E contienen enteros en orden creciente. El resto de las celdas contiene un entero muy grande que podriamos considerar como \ninfinito (llamemoslo maxint). El arreglo podria ser arbitrariamente grande (podemos pensar que es infinito), y no conocemos n. Escriba un \n algoritmo para hallar la posicion de un entero dado x (x < maxint) en el arreglo en un tiempo O(log n)\n";
int *E;
int cantidadReales;
int maxint=999999;
do{
cout << "Ingrese la cantidad de reales: ";
cin >> cantidadReales;
}while(cantidadReales<1);
E=new int[cantidadReales+100];
for(int i=0; i<cantidadReales; i++) {
    cout << "Ingrese los valores del arreglo en la posicion " << i << ": ";
    cin >> *(E+i);
}
for(int i=cantidadReales; i<cantidadReales+100; i++) {
    *(E+i)=maxint;
}
cout <<"Arreglo: [";
for(int i = 0; i < min(cantidadReales + 3, 10); i++) {
        if(E[i] == maxint) {
            cout << "infinito";
        } else {
            cout << E[i];
        }
        if(i < min(cantidadReales + 2, 9)) cout << ", ";
    }
    cout << ", ...]\n" << endl;
    int x;
    cout << "Ingrese el valor de x: ";
    cin >> x;
    int resultado=busquedaEnArregloInfinito(x, E, maxint);
    if (resultado==-1) {
        cout << "El valor no se encuentra en el arreglo" << endl;
    }
    else {
        cout << "El indice del valor es: " << resultado << endl;
    }
    delete []E;
}
int busquedaEnArregloInfinito(int x, int *E, int maxint) {
    int i=1;
    while(*(E+i)<x && *(E+i)!=maxint) {
        i=i*2;
    }
    int izq=i/2;
    int der=i;
    return busquedaBinariaEnRango(x, E, izq, der, maxint);
}

int busquedaBinariaEnRango(int x, int *E, int izq, int der, int maxint) {
    while(izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (*(E+medio) == maxint) {
            der = medio - 1;
        } else if (*(E+medio) == x) {
            return medio;
        } else if (*(E+medio) < x) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    return -1;
}
//EJERCICIO 3=====================================================
int busquedaBinariaModificada(int k, int *arreglo, int n);
void resolucionEjercicios::ejercicio3() {
    cout << "Como podria modificar Busqueda Binaria (algoritmo 1.4) para eliminar trabajo innecesario si se tiene la certeza de que K esta en el arreglo? Dibuje un \narbol de decision para el algoritmo modificado con n = 7. Efectue analisis de comportamiento promedio y de peor caso. (Para el promedio, puede\nsuponerse que n = 2^k - 1 para alguna k.\n)" << endl;
    int k;
    int *arreglo;
    int n;
    cout << "Ingrese el valor de K: ";
    cin >> k;
    do{
        cout << "Ingrese el tamano del arreglo: ";
        cin >> n;
    }while(n<1);
    arreglo=new int[n];
    for(int i=0; i<n; i++) {
        cout << "Ingrese los valores del arreglo en la posicion " << i << ": ";
        cin >> *(arreglo+i);
    }
    cout<<"El valor "<<k<<" se encuentra en la posicion "<<busquedaBinariaModificada(k, arreglo, n)<<endl;
    delete []arreglo;
}
int busquedaBinariaModificada(int k, int *arreglo, int n) {
    int izq=0;
    int der=n-1;
    while(izq<der) {
        int medio=(izq+der+1)/2;
        if(k<*(arreglo+medio)) {
            der=medio-1;
        }
        else {
            izq=medio;
        }
    }
    return izq;
}
//EJERCICIO 4=====================================================
int busquedaBinariaRecursiva(int clave, int *arreglo, int izq, int der);
void resolucionEjercicios::ejercicio4() {
    cout << "Localice un entero en un arreglo usando una version recursiva del algoritmo de busqueda binaria. El numero que se debe buscar (clave) se debe ingresar\n como argumento. El arreglo de datos debe estar previamente ordenado (requisito de la busqueda binaria).\n" << endl;
    int clave;
    int *arreglo;
    int n;
    cout << "Ingrese el valor de la clave: ";
    cin >> clave;
    do{
        cout << "Ingrese el tamano del arreglo: ";
        cin >> n;
    }while(n<1);
    arreglo=new int[n];
    for(int i=0; i<n; i++) {
        cout << "Ingrese los valores del arreglo en la posicion " << i << ": ";
        cin >> *(arreglo+i);
    }
    cout<<"El valor "<<clave<<" se encuentra en la posicion "<<busquedaBinariaRecursiva(clave, arreglo, 0, n-1)<<endl;
    delete []arreglo;
}
int busquedaBinariaRecursiva(int clave, int *arreglo, int izq, int der) {
    if (izq > der) {
        return -1;//EVITAR ERROR 
    }
    int medio = izq + (der - izq) / 2;
    if (arreglo[medio] == clave) {
        return medio;
    } else if (arreglo[medio] < clave) {
        return busquedaBinariaRecursiva(clave, arreglo, medio + 1, der);
    } else {
        return busquedaBinariaRecursiva(clave, arreglo, izq, medio - 1);
    }
}
//EJERCICIO 5=====================================================
int nEsimaClaveMasPequena(int *E1, int *E2, int n);
void resolucionEjercicios::ejercicio5() {
    cout << "Se dan dos arreglos ordenados, E1 y E2, cada uno con n claves en orden ascendente. Disene un algoritmo para hallar la n-esima clave mas pequena de las \n2n claves en un tiempo O(logn).\n" << endl;
    int *E1;
    int *E2;
    int n;
    do{
        cout << "Ingrese el tamano de los arreglos: ";
        cin >> n;
    }while(n<1);
    E1=new int[n];
    E2=new int[n];
    for(int i=0; i<n; i++) {
        cout << "Ingrese los valores del arreglo E1 en la posicion " << i << ": ";
        cin >> *(E1+i);
    }
    for(int i=0; i<n; i++) {
        cout << "Ingrese los valores del arreglo E2 en la posicion " << i << ": ";
        cin >> *(E2+i);
    }
    if(nEsimaClaveMasPequena(E1, E2, n)==-1) {
        cout<<"No se encontro la n-esima clave mas pequena de las 2n claves"<<endl;
    }
    else {
        cout<<"La n-esima clave mas pequena de las 2n claves es: "<<nEsimaClaveMasPequena(E1, E2, n)<<endl;
    }
    delete []E1;
    delete []E2;
}
int nEsimaClaveMasPequena(int *E1, int *E2, int n) {
    int izq=0;
    int der=n;
    while(izq<=der) {
        int medio1=izq+(der-izq)/2;
        int medio2=n-medio1;
        int L1, R1, L2, R2;
        // --- Definir L1 ---
        if (medio1 == 0) { 
            L1 = INT_MIN; // Si no hay nada a la izquierda en E1, usamos -infinito
        } else {
            L1 = *(E1 + medio1 - 1); // Usamos aritmetica de punteros
        }
        // --- Definir R1 ---
        if (medio1 == n) { 
            R1 = INT_MAX; // Si no hay nada a la derecha en E1, usamos +infinito
        } else {
            R1 = *(E1 + medio1); // Usamos aritmetica de punteros
        }
        // --- Definir L2 ---
        if (medio2 == 0) { 
            L2 = INT_MIN; // Si no hay nada a la izquierda en E2, usamos -infinito
        } else {
            L2 = *(E2 + medio2 - 1); // Usamos aritmetica de punteros
        }
        // --- Definir R2 ---
        if (medio2 == n) { 
            R2 = INT_MAX; // Si no hay nada a la derecha en E2, usamos +infinito
        } else {
            R2 = *(E2 + medio2); // Usamos aritmetica de punteros
        }   
        if (L1 <= R2 && L2 <= R1) { 
            return max(L1, L2); // Devolvemos el maximo de los minimos
        } else if (L1 > R2) { 
            der = medio1-1; // Movemos el limite derecho
        } else { 
            izq = medio1+1; // Movemos el limite izquierdo
        }
    }
    return -1;
}
//EJERCICIO 6=====================================================
int busquedaBinariaMatriz(int **M, int n, int x);
void resolucionEjercicios::ejercicio6() {
    cout << "M es una matriz de NxN enteros en la que los elementos de cada fila estan en orden creciente (leyendo de izquierda a derecha) y los elementos de cada columna estan en orden creciente (leyendo de arriba hacia abajo). Escriba un algoritmo eficiente para hallar la posicion de un entero x en M, o determinar que x no esta ahi. Indique cuantas comparaciones de x con elementos de la matriz efectua su algoritmo en el peor caso." << endl;
    int **M;
    int n;
    do{
        cout << "Ingrese el tamano de la matriz cuadrada: ";
        cin >> n;
    }while(n<1);
    M=new int*[n];
    for(int i=0; i<n; i++) {
        *(M+i)=new int[n];
    }
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << "Ingrese los valores de la matriz en la posicion " << i << ", " << j << ": ";
            cin >> *(*(M+i)+j);
        }
    }
    int x;
    cout << "Ingrese el valor de x: ";
    cin >> x;
    if(busquedaBinariaMatriz(M, n, x)==-1) {
        cout<<"El valor "<<x<<" no se encuentra en la matriz"<<endl;
    }
    else {
        cout<<"El valor "<<x<<" se encuentra en la posicion "<<busquedaBinariaMatriz(M, n, x)<<endl;
    }
    for(int i=0; i<n; i++) {
        delete [] *(M+i);
    }
    delete []M;
}
int busquedaBinariaMatriz(int **M, int n, int x) {
    int izq=0;
    int der=n*n-1;
    while(izq<=der) {
        int medio=izq+(der-izq)/2;
        // medio / n nos da la fila: al dividir por n (columnas), obtenemos cuantos bloques completos de filas caben.
        // medio % n nos da la columna: el residuo es la posicion dentro de esa fila.
        
        if(*(*(M + medio/n) + medio%n )==x) {
            return medio;
        }
        else if(*(*(M + medio/n) + medio%n )<x) {
            izq=medio+1;
        }
        else {
            der=medio-1;
        }
    }
    return -1;
}
//EJERCICIO 7=====================================================
int busquedaBinariaUnimodal(int *E, int n);
void resolucionEjercicios::ejercicio7() {
    cout << "Sea E un arreglo de n+1 elementos (indices 0 a n) que se sabe que es unimodal: E[i] crece estrictamente hasta un indice maximo M y decrece estrictamente para los indices i>M.\nEscriba un algoritmo en C++ para hallar el indice M (la posicion del elemento maximo) comparando las claves del arreglo. El algoritmo debe ejecutarse en un tiempo de O(logn)." << endl;
    int *E;
    int n;
    do{
        cout << "Ingrese el tamano del arreglo: ";
        cin >> n;
    }while(n<1);
    E=new int[n+1];
    for(int i=0; i<n+1; i++) {
        cout << "Ingrese los valores del arreglo en la posicion " << i << ": ";
        cin >> *(E+i);
    }
    int M=busquedaBinariaUnimodal(E, n);
    cout<<"El indice M es: "<<M<<", el valor es: "<<*(E+M)<<endl;
    delete []E;

}
int busquedaBinariaUnimodal(int *E, int n) {
    int izq=0;
    int der=n;//Porque desde un inicio indicamos que el arreglo sera de n+1 elementos
    while(izq<der) {
        int medio=izq+(der-izq)/2;
        if(*(E+medio)<*(E+medio+1)) {
            izq=medio+1;
        }
        else {
            der=medio;
        }
    }
    return izq;
}
//EJERCICIO 8=====================================================
void resolucionEjercicios::ejercicio8() {
    cout << "Un entero de ocho digitos se puede dividir en grupos de tres, tres y dos digitos, los grupos se suman juntos y se truncan si es necesario para que esten en el rango adecuado de indices.\n\nPor consiguiente, si la clave es: 62538194\n\ny el numero de direcciones es 100, la funcion de conversion sera: 625 + 381 + 94 = 1100\n\nque se truncara a 100 y que sera la direccion deseada." << endl;
    int clave;
    do{
        cout << "Ingrese la clave: ";
        cin >> clave;
    }while(clave<10000000 || clave>99999999);
    int p1=clave/100000;
    int p2=(clave/100)%1000;
    int p3=clave%100;
    cout<<"Los grupos son: "<<p1<<", "<<p2<<", "<<p3<<endl;
    int direccion=p1+p2+p3;
    direccion=direccion%100;
    cout<<"La direccion es: "<<direccion<<endl;
}
//EJERCICIO 9=====================================================
void resolucionEjercicios::ejercicio9() {
    cout << "Un vector T tiene cien posiciones, 0..100. Supongamos que las claves de busqueda de los elementos de la tabla son enteros positivos (por ejemplo, numero del DNI).Una funcion de conversion h debe tomar un numero arbitrario entero positivo x y convertirlo en un entero en el rango 0..100, esto es, h es una funcion tal que para un entero positivo x:h(x) = n, donde n es entero en el rango 0..100El metodo del modulo, tomando 101, sera:h(x) = x mod 101Si se tiene el DNI numero 234661234, por ejemplo, se tendra la posicion 56:234661234 mod 101 = 56." << endl;
    int clave;
    do{
        cout << "Ingrese la clave (Enteros positivos): ";
        cin >> clave;
    }while(clave<0);
    int direccion=clave%101;
    cout<<"La direccion es: "<<direccion<<endl;
}
//EJERCICIO 10=====================================================
void resolucionEjercicios::ejercicio10() {
    cout << "La clave de busqueda es una cadena de caracteres -tal como un nombre-. Obtener las direcciones de conversion.\n\nEl metodo mas simple es asignar a cada caracter de la cadena un valor entero (por ejemplo, A = 1, B = 2, ...) y sumar los valores de los caracteres en la cadena. Al resultado se le aplica entonces el modulo 101, por ejemplo.\n\nSi el nombre fuese JONAS, esta clave se convertiria en el entero: 10 + 15 + 14 + 1 + 19 = 63\n\n63 mod 101 = 63." << endl;
    string nombre;
    cout << "Ingrese el nombre: ";
    cin >> nombre;
    int direccion=0;
    for(int i=0; i<nombre.length(); i++) {
        direccion+=nombre[i]-64;
    }
    
    direccion=direccion%101;
    cout<<"La direccion es: "<<direccion<<endl;
}
