#include <iostream>
#include <algorithm> 
using namespace std;

// Función Hash simple para números 
long long hashPIN(int pin) {
    long long h = pin;
    h = (h * 2654435761) % 4294967296; 
    return h;
}

// Búsqueda binaria clásica en arreglo
int busquedaBinaria(long long arr[], int n, long long objetivo) {
    int izq = 0, der = n - 1;
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        if (arr[mid] == objetivo) return mid;
        if (arr[mid] < objetivo) izq = mid + 1;
        else der = mid - 1;
    }
    return -1;
}

int main() {
    // Base de datos de hashes permitidos (Los PINs originales son secretos)
    int capacidad = 5;
    long long hashesPermitidos[5] = {
        hashPIN(1234), 
        hashPIN(9999), 
        hashPIN(5678), 
        hashPIN(0000), 
        hashPIN(2025)
    };

    // 1. Ordenar (Obligatorio para búsqueda binaria)
    sort(hashesPermitidos, hashesPermitidos + capacidad);

    cout << "=== SISTEMA DE SEGURIDAD ===" << endl;
    cout << "Base de datos cargada con " << capacidad << " usuarios." << endl;

    while (true) {
        int entrada;
        cout << "\nIngrese su PIN de 4 digitos (-1 para salir): ";
        cin >> entrada;

        if (entrada == -1) break;

        // 2. Hashear la entrada del usuario
        long long hashUsuario = hashPIN(entrada);

        // 3. Buscar el hash
        if (busquedaBinaria(hashesPermitidos, capacidad, hashUsuario) != -1) {
            cout << "[ACCESO CONCEDIDO] Hash encontrado: " << hashUsuario << endl;
        } else {
            cout << "[ACCESO DENEGADO] PIN invalido." << endl;
        }
    }
    return 0;
}