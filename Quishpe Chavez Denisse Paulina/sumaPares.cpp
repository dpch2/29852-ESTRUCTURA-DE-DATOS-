#include <iostream>
using namespace std;

// TABLA HASH SIMPLE con memoria dinámica
const int HASH_SIZE = 100003;  // Número primo
long long* hashTabla;          // Valores almacenados (memoria dinámica)
bool* hashOcupado;             // Indica si posición está ocupada (memoria dinámica)

long long* numeros;            // Array de números (memoria dinámica)
int N;
long long S;

// Función hash simple
int funcionHash(long long valor) {
    long long hash = valor % HASH_SIZE;
    if (hash < 0) hash += HASH_SIZE;
    return (int)hash;
}

// Insertar en tabla hash con linear probing
void insertarHash(long long valor) {
    int pos = funcionHash(valor);
    
    // Linear probing: buscar siguiente posición libre
    while (hashOcupado[pos]) {
        pos = (pos + 1) % HASH_SIZE;
    }
    
    hashTabla[pos] = valor;
    hashOcupado[pos] = true;
}

// Buscar en tabla hash
bool buscarHash(long long valor) {
    int pos = funcionHash(valor);
    int inicio = pos;
    
    // Buscar con linear probing
    while (hashOcupado[pos]) {
        if (hashTabla[pos] == valor) {
            return true;
        }
        pos = (pos + 1) % HASH_SIZE;
        
        if (pos == inicio) break;
    }
    
    return false;
}

// BÚSQUEDA BINARIA en array ordenado
bool busquedaBinaria(long long objetivo) {
    int left = 0;
    int right = N - 1;
    
    cout << "  Buscando " << objetivo << " con binary search...\n";
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        cout << "    Rango [" << left << ", " << right << "] -> mid=" << mid 
             << " (valor=" << numeros[mid] << ")\n";
        
        if (numeros[mid] == objetivo) {
            cout << "    ENCONTRADO en posicion " << mid << "\n";
            return true;
        } else if (numeros[mid] < objetivo) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    cout << "    NO encontrado\n";
    return false;
}

int main() {
    cout << "=== BUSQUEDA DE PARES (HASH + BINARY SEARCH) ===\n\n";
    cout << "Cantidad de numeros: ";
    cin >> N;
    
    if (N <= 0 || N > 100000) {
        cout << "Error: N debe estar entre 1 y 100000\n";
        return 1;
    }
    
    // MEMORIA DINÁMICA: Reservar espacio para números
    numeros = new long long[N];
    
    if (numeros == NULL) {
        cout << "Error: No se pudo asignar memoria\n";
        return 1;
    }
    
    cout << "Ingrese " << N << " numeros ORDENADOS:\n";
    for (int i = 0; i < N; i++) {
        cout << "  Numero " << (i + 1) << ": ";
        cin >> numeros[i];
    }
    
    cout << "Suma objetivo: ";
    cin >> S;
    
    // MEMORIA DINÁMICA: Inicializar tabla hash
    hashTabla = new long long[HASH_SIZE];
    hashOcupado = new bool[HASH_SIZE];
    
    if (hashTabla == NULL || hashOcupado == NULL) {
        cout << "Error: No se pudo asignar memoria para hash\n";
        delete[] numeros;
        if (hashTabla != NULL) delete[] hashTabla;
        if (hashOcupado != NULL) delete[] hashOcupado;
        return 1;
    }
    
    for (int i = 0; i < HASH_SIZE; i++) {
        hashOcupado[i] = false;
    }
    
    // ========== MÉTODO 1: TABLA HASH ==========
    cout << "\n========================================\n";
    cout << "METODO 1: USANDO TABLA HASH\n";
    cout << "========================================\n";
    
    // Insertar todos los números en la tabla hash
    for (int i = 0; i < N; i++) {
        insertarHash(numeros[i]);
        cout << "Insertado: " << numeros[i] << " en hash\n";
    }
    
    // Buscar el complemento de cada número
    bool encontrado = false;
    long long num1 = 0, num2 = 0;
    
    cout << "\nBuscando pares...\n";
    for (int i = 0; i < N; i++) {
        long long complemento = S - numeros[i];
        
        cout << "Para " << numeros[i] << " busco complemento " << complemento << "... ";
        
        if (complemento != numeros[i] && buscarHash(complemento)) {
            cout << "ENCONTRADO!\n";
            encontrado = true;
            num1 = numeros[i];
            num2 = complemento;
            break;
        } else {
            cout << "No\n";
        }
    }
    
    if (encontrado) {
        cout << "\nRESULTADO HASH: SI existe el par\n";
        cout << num1 << " + " << num2 << " = " << S << "\n";
    } else {
        cout << "\nRESULTADO HASH: NO existe el par\n";
    }
    
    // ========== MÉTODO 2: BÚSQUEDA BINARIA ==========
    cout << "\n========================================\n";
    cout << "METODO 2: USANDO BUSQUEDA BINARIA\n";
    cout << "========================================\n";
    
    encontrado = false;
    
    for (int i = 0; i < N; i++) {
        long long complemento = S - numeros[i];
        
        cout << "\nPara numero[" << i << "]=" << numeros[i] 
             << " busco complemento=" << complemento << "\n";
        
        if (complemento > numeros[i] && busquedaBinaria(complemento)) {
            encontrado = true;
            num1 = numeros[i];
            num2 = complemento;
            break;
        }
    }
    
    if (encontrado) {
        cout << "\nRESULTADO BINARY SEARCH: SI existe el par\n";
        cout << num1 << " + " << num2 << " = " << S << "\n";
    } else {
        cout << "\nRESULTADO BINARY SEARCH: NO existe el par\n";
    }
    
    // ========== COMPARACIÓN ==========
    cout << "\n========================================\n";
    cout << "COMPARACION DE METODOS\n";
    cout << "========================================\n";
    cout << "HASH TABLE:\n";
    cout << "  - Complejidad: O(N)\n";
    cout << "  - Memoria: O(HASH_SIZE) = " << HASH_SIZE << " espacios\n";
    cout << "  - Ventaja: MUY RAPIDO\n";
    cout << "  - Desventaja: Usa mucha memoria\n\n";
    
    cout << "BINARY SEARCH:\n";
    cout << "  - Complejidad: O(N log N)\n";
    cout << "  - Memoria: O(1) adicional\n";
    cout << "  - Ventaja: Usa poca memoria\n";
    cout << "  - Desventaja: Mas lento que hash\n";
    
    // LIBERAR MEMORIA DINÁMICA
    delete[] numeros;
    delete[] hashTabla;
    delete[] hashOcupado;
    
    cout << "\nMemoria liberada correctamente.\n";
    
    return 0;
}
