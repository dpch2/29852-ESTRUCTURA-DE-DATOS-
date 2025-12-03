#include <iostream>
#include <algorithm>
using namespace std;

int n; // Número de árboles
long long m; // Madera necesaria
long long* arboles;

// Función: ¿Cuánta madera obtengo si corto a altura h?
bool esSuficiente(long long h) {
    long long madera = 0;
    for (int i = 0; i < n; i++) {
        if (arboles[i] > h) {
            madera += (arboles[i] - h);
        }
    }
    return madera >= m;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    if (!(cin >> n >> m)) return 0;
    
    arboles = new long long[n];
    long long max_altura = 0;
    
    for (int i = 0; i < n; i++) {
        cin >> arboles[i];
        if (arboles[i] > max_altura) max_altura = arboles[i];
    }

    long long bajo = 0, alto = max_altura;
    long long ans = 0;

    while (bajo <= alto) {
        long long mid = bajo + (alto - bajo) / 2;
        if (esSuficiente(mid)) {
            ans = mid;      // Esta altura funciona, intentemos cortar más arriba (ahorrar árboles)
            bajo = mid + 1;
        } else {
            alto = mid - 1; // No conseguimos suficiente madera, hay que cortar más abajo
        }
    }

    cout << ans << endl;
    delete[] arboles;
    return 0;
}