#include <iostream>
#include <fstream>
#include <cstdlib>   // system()
using namespace std;

long long contador;

// Algoritmo O(n^2)
void algoritmo(int n) {
    contador = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            contador++;
        }
    }
}

int main() {
    ofstream archivo("datos.txt");
    archivo << "n ops\n";

    for (int n = 10; n <= 500; n += 10) {
        algoritmo(n);
        archivo << n << " " << contador << endl;
    }

    archivo.close();

    cout << "Datos generados.\n";

    //  ABRIR MATLAB AUTOMÁTICAMENTE
    system("matlab -r grafica");


    return 0;
}
