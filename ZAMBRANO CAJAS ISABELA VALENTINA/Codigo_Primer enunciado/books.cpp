#include <iostream>
#include <cstdlib>
using namespace std;

// -------------------------------------------------------
// BUSQUEDA BINARIA 
// -------------------------------------------------------
int busquedaBinaria(long long* pref, int n, int inicio, long long t) {
    int lo = inicio;
    int hi = n;
    int ans = inicio - 1;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        long long suma = *(pref + mid) - *(pref + (inicio - 1));

        if (suma <= t) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return ans;
}

int main() {

    int n;
    long long t;
    
    cout << "Ingrese n y t: ";
    cin >> n >> t;

    long long* a = static_cast<long long*>(malloc(n * sizeof(long long)));

    cout << "Ingrese los tiempos de lectura de los " << n << " libros:\n";
    for (int i = 0; i < n; i++) {
        cin >> *(a + i);
    }


    long long* pref = static_cast<long long*>(malloc((n + 1) * sizeof(long long)));
    *(pref + 0) = 0;

    for (int i = 1; i <= n; i++) {
        *(pref + i) = *(pref + i - 1) + *(a + (i - 1));
    }

    int best = 0;

    for (int i = 1; i <= n; i++) {
        int j = busquedaBinaria(pref, n, i, t);
        int len = j - i + 1;
        if (len > best) best = len;
    }

    cout << "\nMaximo numero de libros que puede leer: " << best << endl;

    free(a);
    free(pref);

    return 0;
}
