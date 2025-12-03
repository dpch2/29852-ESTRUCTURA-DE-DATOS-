#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Función que verifica si es posible pintar todas las tablas
// usando K pintores donde ninguno trabaje más de maxTime horas
bool canPaintWithMaxTime(vector<long long>& boards, int K, long long maxTime) {
    int paintersUsed = 1;  // Empezamos con el primer pintor
    long long currentPainterTime = 0;
    
    for (int i = 0; i < boards.size(); i++) {
        // Si una sola tabla excede maxTime, es imposible
        if (boards[i] > maxTime) {
            return false;
        }
        
        // Si agregar esta tabla al pintor actual excede maxTime
        if (currentPainterTime + boards[i] > maxTime) {
            // Necesitamos un nuevo pintor
            paintersUsed++;
            currentPainterTime = boards[i];  // El nuevo pintor empieza con esta tabla
            
            // Si necesitamos más pintores de los disponibles
            if (paintersUsed > K) {
                return false;
            }
        } else {
            // El pintor actual puede tomar esta tabla
            currentPainterTime += boards[i];
        }
    }
    
    return true;
}

int main() {
    cout << "=== PROBLEMA: PAINTER'S PROBLEM ===" << endl << endl;
    
    int N, K;
    cout << "Ingrese el numero de tablas (N): ";
    cin >> N;
    
    cout << "Ingrese el numero de pintores (K): ";
    cin >> K;
    
    vector<long long> boards(N);
    cout << "\nIngrese la longitud de cada tabla en metros (separadas por espacio):" << endl;
    
    for (int i = 0; i < N; i++) {
        cin >> boards[i];
    }
    
    cout << "\n--- Datos del problema ---" << endl;
    cout << "Tablas (metros): ";
    for (int i = 0; i < N; i++) {
        cout << boards[i];
        if (i < N - 1) cout << " ";
    }
    cout << endl;
    cout << "Pintores disponibles: " << K << endl;
    
    // Búsqueda binaria sobre el tiempo máximo
    long long left = *max_element(boards.begin(), boards.end());  // Al menos la tabla más larga
    long long right = accumulate(boards.begin(), boards.end(), 0LL);  // Máximo: un pintor hace todo
    long long answer = right;
    
    cout << "\n--- Busqueda Binaria sobre el Tiempo Maximo ---" << endl;
    cout << "Rango inicial: [" << left << ", " << right << "]" << endl << endl;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        cout << "Probando maxTime = " << mid << " horas... ";
        
        if (canPaintWithMaxTime(boards, K, mid)) {
            // Es posible con este tiempo, intentar con menos
            answer = mid;
            right = mid - 1;
            cout << "POSIBLE (buscando menor)" << endl;
        } else {
            // No es posible, necesitamos más tiempo
            left = mid + 1;
            cout << "IMPOSIBLE (necesita mas tiempo)" << endl;
        }
    }
    
    cout << "\n=== RESULTADO ===" << endl;
    cout << "Tiempo minimo maximo: " << answer << " horas" << endl;
    
    // Mostrar una distribución válida
    cout << "\n--- Ejemplo de distribucion ---" << endl;
    
    int painterNum = 1;
    long long currentTime = 0;
    
    cout << "Pintor " << painterNum << ": ";
    
    for (int i = 0; i < N; i++) {
        if (currentTime + boards[i] > answer && currentTime > 0) {
            cout << "-> Total: " << currentTime << " horas" << endl;
            painterNum++;
            cout << "Pintor " << painterNum << ": ";
            currentTime = 0;
        }
        
        cout << boards[i];
        if (i < N - 1 && currentTime + boards[i] + boards[i+1] <= answer) {
            cout << " + ";
        }
        currentTime += boards[i];
    }
    
    cout << "-> Total: " << currentTime << " horas" << endl;
    cout << "\nTiempo maximo entre todos los pintores: " << answer << " horas" << endl;
    
    return 0;
}