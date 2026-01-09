#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include <cstdlib>

using namespace std;

bool esSeguro(int* tablero, int col, int fila) {
    for (int prevCol = 0; prevCol < col; prevCol++) {
        int prevFila = tablero[prevCol];
        if (prevFila == fila || abs(prevFila - fila) == abs(prevCol - col)) {
            return false;
        }
    }
    return true;
}

bool resolverNReinas(int* tablero, int col, int N) {
    if (col >= N) {
        return true; 
    }

    for (int i = 0; i < N; i++) {
        if (esSeguro(tablero, col, i)) {
            tablero[col] = i;
            if (resolverNReinas(tablero, col + 1, N)) {
                return true;
            }
        }
    }
    return false;
}

void guardarYMostrarTablero(int* tablero, int N) {
    ofstream archivo("solucion_reinas.txt");
    
    cout << "\n--- SOLUCION GRAFICA (" << N << "x" << N << ") ---\n";
    if (archivo.is_open()) archivo << "Solucion para " << N << " reinas:\n";

    string lineaH = " ";
    for(int k=0; k<N; k++) lineaH += "+---";
    lineaH += "+";

    cout << lineaH << endl;
    if (archivo.is_open()) archivo << lineaH << endl;

    for (int i = 0; i < N; i++) {
        cout << " |";
        if (archivo.is_open()) archivo << " |";
        
        for (int j = 0; j < N; j++) {
            if (tablero[j] == i) {
                cout << " Q |";
                if (archivo.is_open()) archivo << " Q |";
            } else {
                cout << "   |";
                if (archivo.is_open()) archivo << "   |";
            }
        }
        cout << endl << lineaH << endl;
        if (archivo.is_open()) {
            archivo << endl << lineaH << endl;
        }
    }
    
    cout << "\n[INFO] Solucion guardada en 'solucion_reinas.txt'\n";
    if (archivo.is_open()) archivo.close();
}

void generarScriptMatlab() {
    ofstream script("graficar_complejidad.m");
    if (script.is_open()) {
        script << "% Script generado por C++\n";
        script << "if exist('datos_complejidad.txt', 'file')\n";
        script << "    data = load('datos_complejidad.txt');\n";
        script << "    N = data(:,1);\n";
        script << "    Tiempo = data(:,2);\n";
        script << "    figure('Name', 'Complejidad N-Reinas');\n";
        script << "    plot(N, Tiempo, '-s', 'LineWidth', 2, 'MarkerFaceColor', 'r');\n";
        script << "    title('Analisis de Tiempos: Primera Solucion');\n";
        script << "    xlabel('N (Numero de Reinas)');\n";
        script << "    ylabel('Tiempo (Microsegundos)');\n";
        script << "    grid on;\n";
        script << "else\n";
        script << "    disp('No se encontro el archivo datos_complejidad.txt');\n";
        script << "end\n";
        script.close();
    }
}

int main() {
    int N;
    cout << "Ingrese el numero de Reinas: ";
    cin >> N;

    int* tablero = new int[N];

    auto start = chrono::high_resolution_clock::now();
    
    if (resolverNReinas(tablero, 0, N)) {
        guardarYMostrarTablero(tablero, N);
    } else {
        cout << "No existe solucion para " << N << " reinas." << endl;
    }
    
    auto end = chrono::high_resolution_clock::now();
    double tiempoUsuario = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Tiempo de ejecucion: " << tiempoUsuario << " us.\n";

    delete[] tablero;

    cout << "\n--- GENERANDO DATOS DE COMPLEJIDAD ---\n";
    ofstream datos("datos_complejidad.txt");
    
    for (int k = 4; k <= 20; k++) {
        int* tBenchmark = new int[k];
        
        auto t1 = chrono::high_resolution_clock::now();
        resolverNReinas(tBenchmark, 0, k);
        auto t2 = chrono::high_resolution_clock::now();
        
        long long duracion = chrono::duration_cast<chrono::microseconds>(t2 - t1).count();
        datos << k << " " << duracion << endl;

        delete[] tBenchmark;
    }
    datos.close();
    cout << "Datos generados.\n";

    generarScriptMatlab();
    
    cout << "Intentando abrir Matlab...\n";
    #ifdef _WIN32
        system("start matlab -nosplash -nodesktop -r \"run('graficar_complejidad.m');\"");
    #else
        system("matlab -nosplash -nodesktop -r \"run('graficar_complejidad.m');\" &");
    #endif

    return 0;
}
