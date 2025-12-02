#include <iostream>
using namespace std;

bool posible(int n, int a, int b, int c, int k) {

    for (int x = 0; x <= k; x++) {

        long long rhs = 1LL * n - 1LL * k * c - 1LL * x * (a - c);
        long long denom = (b - c);

        long long y;

        if (denom == 0) {
            
            if (rhs == 0) {
                y = 0;
            } else {
                continue;
            }
        } else {
            if (rhs % denom != 0) continue;     
            y = rhs / denom;
        }

        long long z = k - x - y;

        if (y >= 0 && z >= 0) {
            return true;
        }
    }

    return false;
}

// --------------------------------------------------------
// BÚSQUEDA BINARIA PARA MAXIMIZAR k
// --------------------------------------------------------
int main() {

    int n, a, b, c;
    cout << "Ingrese n, a, b, c:\n";
    cin >> n >> a >> b >> c;

    int lo = 0;
    int hi = n;       
    int best = 0;

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;

        if (posible(n, a, b, c, mid)) {
            best = mid;
            lo = mid + 1;     
        } else {
            hi = mid - 1;
        }
    }

    cout << "\nMaximo numero de piezas: " << best << endl;
    return 0;
}
