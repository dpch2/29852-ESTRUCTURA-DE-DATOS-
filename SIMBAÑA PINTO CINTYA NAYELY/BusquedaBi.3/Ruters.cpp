#include <iostream>
#include <algorithm>
using namespace std;

int n, c_routers;
long long* casas;

// Verificamos si podemos poner 'c' routers con al menos 'dist' de separación
bool esPosible(long long dist) {
    int colocados = 1;
    long long ultima_pos = casas[0];
    
    for (int i = 1; i < n; i++) {
        if (casas[i] - ultima_pos >= dist) {
            colocados++;
            ultima_pos = casas[i];
        }
    }
    return colocados >= c_routers;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    if (!(cin >> n >> c_routers)) return 0;

    casas = new long long[n];
    for (int i = 0; i < n; i++) cin >> casas[i];

    // Importante: Para que la lógica Greedy funcione, las casas deben estar ordenadas
    sort(casas, casas + n);

    long long bajo = 1; 
    long long alto = casas[n-1] - casas[0]; // Distancia máxima posible
    long long ans = 0;

    while (bajo <= alto) {
        long long mid = bajo + (alto - bajo) / 2;
        if (esPosible(mid)) {
            ans = mid;      // Funciona, intentemos separar más los routers
            bajo = mid + 1;
        } else {
            alto = mid - 1; // Demasiada distancia, no caben los routers
        }
    }

    cout << ans << endl;
    delete[] casas;
    return 0;
}