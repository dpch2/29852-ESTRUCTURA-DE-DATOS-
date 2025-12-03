#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int inputNum(string Mensaje, bool negativos){
    if(negativos){
        cout << Mensaje;
        int input = 0;
        cin >> input;
        return input;
    }
    bool validInput = false;
    int input = 0;
    do{
        cout << Mensaje;
        cin >> input;
        if(input <= 0){ 
            cout << "Entrada Invalida, debe ser mayor a cero\n";
        }
        else {
            validInput = true;
        }
    } while(!validInput);
    return input;
}

int* inputIntVector(int size, string msg, bool negatives){
    int* vector = new int[size];
    for(int i = 0; i < size; i++){
        *(vector+i) = inputNum(msg, negatives);
    }
    return vector;
}

long long* inputLongVector(int size, string msg){
    long long* vector = new long long[size];
    for(int i = 0; i < size; i++){
        cout << msg;
        cin >> *(vector+i);
    }
    return vector;
}

// BUBBLE SORT para L y R juntos
void bubbleSortIntervals(long long* L, long long* R, int size){
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (*(L + j) > *(L + (j + 1))) {

                long long tmpL = *(L + j);
                *(L + j) = *(L + (j + 1));
                *(L + (j + 1)) = tmpL;

                long long tmpR = *(R + j);
                *(R + j) = *(R + (j + 1));
                *(R + (j + 1)) = tmpR;
            }
        }
    }
}

// ----------------------
// FUNCIÓN CAN(D)
// ----------------------
// Verifica si podemos poner N vacas a distancia >= D
bool canPlace(long long* L, long long* R, int M, long long N, long long D){
    long long cows = 0;
    long long pos = -9000000000000000000LL; // -∞ manual

    for (int i = 0; i < M; i++) {

        long long a = *(L + i);
        long long b = *(R + i);

        // Elegir el primer lugar válido dentro del intervalo
        if (pos + D <= a)
            pos = a;
        else
            pos = pos + D;

        // Colocar vacas dentro del intervalo mientras sea posible
        while (pos <= b) {
            cows++;
            if (cows >= N) return true;
            pos = pos + D;
        }
    }
    return false;
}

// ----------------------
// EJERCICIO DISTANCING
// ----------------------
int ejercicioDistancing(){
    long long N = inputNum("Ingrese cuantas vacas habran: ", false);
    int M = inputNum("Ingrese cuantos intervalos existen: ", false);

    cout << "\n--- Intervalos ---\n";
    long long* L = new long long[M];
    long long* R = new long long[M];

    for (int i = 0; i < M; i++){
        cout << "Ingrese inicio del intervalo " << i+1 << ": ";
        cin >> *(L + i);
        cout << "Ingrese fin del intervalo " << i+1 << ": ";
        cin >> *(R + i);
    }

    // Ordenar intervalos por L
    bubbleSortIntervals(L, R, M);

    long long low = 1;
    long long high = 1000000000000000000LL;
    long long ans = 1;

    // BÚSQUEDA BINARIA REAL SOBRE D
    while(low <= high){
        long long mid = (low + high) / 2;

        if (canPlace(L, R, M, N, mid)){
            ans = mid;       // funciona → intento más grande
            low = mid + 1;
        }
        else {
            high = mid - 1;  // no funciona → achico
        }
    }

    cout << "La maxima distancia D es: " << ans << "\n";

    delete[] L;
    delete[] R;
    return 0;
}

// ----------------------
// MAIN
// ----------------------
int main(){

    cout << "\n--- EJERCICIO DISTANCING (PROBLEMA D) ---\n";
    ejercicioDistancing();

    return 0;
}
