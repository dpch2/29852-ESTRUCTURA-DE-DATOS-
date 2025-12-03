#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Función que verifica si existe una ventana de K libros
// donde el máximo es <= maxPages y la suma total es <= T
bool canReadWithMaxPages(vector<long long>& pages, int K, long long T, long long maxPages) {
    int N = pages.size();
    
    // Probar todas las ventanas de K libros consecutivos
    for (int i = 0; i <= N - K; i++) {
        long long sum = 0;
        long long currentMax = 0;
        bool valid = true;
        
        // Calcular suma y máximo de esta ventana
        for (int j = i; j < i + K; j++) {
            // Si algún libro en la ventana excede maxPages, esta ventana no sirve
            if (pages[j] > maxPages) {
                valid = false;
                break;
            }
            sum += pages[j];
            currentMax = max(currentMax, pages[j]);
        }
        
        // Si encontramos una ventana válida que cumple ambas condiciones
        if (valid && sum <= T && currentMax <= maxPages) {
            return true;
        }
    }
    
    return false;
}

int main() {
    cout << "=== PROBLEMA: BOOK READING MARATHON ===" << endl << endl;
    
    int N, K;
    long long T;
    
    cout << "Ingrese el numero de libros (N): ";
    cin >> N;
    
    cout << "Ingrese el numero de miembros del club (K): ";
    cin >> K;
    
    cout << "Ingrese el limite de tiempo en horas (T): ";
    cin >> T;
    
    vector<long long> pages(N);
    cout << "\nIngrese el numero de paginas de cada libro (separadas por espacio):" << endl;
    
    for (int i = 0; i < N; i++) {
        cin >> pages[i];
    }
    
    cout << "\n--- Datos del problema ---" << endl;
    cout << "Libros: ";
    for (int i = 0; i < N; i++) {
        cout << pages[i];
        if (i < N - 1) cout << " ";
    }
    cout << endl;
    cout << "Miembros: " << K << endl;
    cout << "Limite de tiempo: " << T << " horas" << endl;
    
    // Búsqueda binaria sobre el máximo número de páginas
    long long left = 1;
    long long right = *max_element(pages.begin(), pages.end());
    long long answer = -1;
    
    cout << "\n--- Busqueda Binaria sobre el Maximo de Paginas ---" << endl;
    
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        
        cout << "Probando maxPages = " << mid << "... ";
        
        if (canReadWithMaxPages(pages, K, T, mid)) {
            // Es posible con este máximo, intentar con uno menor
            answer = mid;
            right = mid - 1;
            cout << "POSIBLE (buscando menor)" << endl;
        } else {
            // No es posible, necesitamos un máximo mayor
            left = mid + 1;
            cout << "IMPOSIBLE (buscando mayor)" << endl;
        }
    }
    
    cout << "\n=== RESULTADO ===" << endl;
    
    if (answer == -1) {
        cout << "No existe ninguna seleccion valida de libros." << endl;
        cout << "El limite de tiempo es demasiado restrictivo." << endl;
    } else {
        cout << "Minimo numero de paginas del libro mas largo: " << answer << endl;
        
        // Mostrar una solución válida
        cout << "\n--- Resultado del ejercicio ---" << endl;
        
        for (int i = 0; i <= N - K; i++) {
            long long sum = 0;
            long long maxInWindow = 0;
            bool valid = true;
            
            vector<long long> window;
            
            for (int j = i; j < i + K; j++) {
                if (pages[j] > answer) {
                    valid = false;
                    break;
                }
                window.push_back(pages[j]);
                sum += pages[j];
                maxInWindow = max(maxInWindow, pages[j]);
            }
            
            if (valid && sum <= T && maxInWindow == answer) {
                cout << "Libros seleccionados: ";
                for (int j = 0; j < window.size(); j++) {
                    cout << window[j];
                    if (j < window.size() - 1) cout << ", ";
                }
                cout << endl;
                cout << "Suma total: " << sum << " horas (limite: " << T << ")" << endl;
                cout << "Libro mas largo: " << maxInWindow << " paginas" << endl;
                break;
            }
        }
    }
    
    return 0;
}
