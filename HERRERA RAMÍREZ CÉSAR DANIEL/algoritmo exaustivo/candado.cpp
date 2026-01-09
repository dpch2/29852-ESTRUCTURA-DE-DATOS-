#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream archivo("combinaciones_candado.txt");

    if (!archivo) {
        cout << "Error al crear el archivo." << endl;
        return 1;
    }

    for (int i = 0; i <= 9999; i++) {
        if (i < 10)
            archivo << "000" << i << endl;
        else if (i < 100)
            archivo << "00" << i << endl;
        else if (i < 1000)
            archivo << "0" << i << endl;
        else
            archivo << i << endl;
    }

    archivo.close();

    cout << "Archivo generado correctamente." << endl;
    cout << "Total de combinaciones: 10,000" << endl;

    return 0;
}
