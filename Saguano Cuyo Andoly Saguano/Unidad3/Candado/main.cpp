#include <iostream>
using namespace std;

class Candado {
private:
    int *clave;   // contraseña real (oculta)
    int *intento; // intento actual

public:
    // Constructor
    Candado() {
        clave = new int[4]{8, 5, 2, 2};   // contraseña volátil
        intento = new int[4]{0, 0, 0, 0};
    }

    

    // Evalúa cuántos dígitos están correctos
    int evaluar() {
        int aciertos = 0;
        for (int i = 0; i < 4; i++) {
            if (*(intento + i) == *(clave + i)) {
                aciertos++;
            }
        }
        return aciertos;
    }

    // Algoritmo voraz para abrir el candado
    void abrirCandado() {
        for (int i = 0; i < 4; i++) {
            int mejorDigito = *(intento + i);
            int mejorAciertos = evaluar();

            for (int d = 0; d <= 9; d++) {
                *(intento + i) = d;
                int aciertos = evaluar();

                if (aciertos > mejorAciertos) {
                    mejorAciertos = aciertos;
                    mejorDigito = d;
                }
            }

            *(intento + i) = mejorDigito;

            cout << "Paso " << i + 1 << " -> ";
            mostrarIntento();
            cout << " | Aciertos: " << evaluar() << endl;
        }
    }

    // Muestra el intento actual
    void mostrarIntento() {
        for (int i = 0; i < 4; i++) {
            cout << *(intento + i);
        }
    }
};

int main() {
    Candado c;

    cout << " Abriendo candado \n\n";
    c.abrirCandado();

    cout << "\nCandado abierto con la combinacion: ";
    c.mostrarIntento();
    cout << endl;

    return 0;
}
