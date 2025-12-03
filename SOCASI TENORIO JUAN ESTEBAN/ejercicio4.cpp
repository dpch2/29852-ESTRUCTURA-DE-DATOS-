#include <bits/stdc++.h>
using namespace std;


int main() {
    cout<<"hola"<<endl;
    int N;
    long long T;
    if (!(cin >> N >> T)) return 0;
    long long* t = new long long[N];
    long long mx = 0;
    for (int i = 0; i < N; ++i) { cin >> t[i]; mx = max(mx, t[i]); }

    if (T < N) { // cada tarea necesita al menos 1 unidad de tiempo
        cout << -1 << "\n";
        delete[] t;
        return 0;
    }
    long long l = 1, r = mx; // buscamos mínimo V en [1, mx]
    while (l < r) {
        long long mid = l + (r - l) / 2;
        __int128 total = 0;
        for (int i = 0; i < N; ++i) {
            total += (t[i] + mid - 1) / mid;
            if (total > (__int128)T) break;
        }
        if (total <= (__int128)T) r = mid;
        else l = mid + 1;
    }

    __int128 total = 0;
    for (int i = 0; i < N; ++i) total += (t[i] + l - 1) / l;
    if (total <= (__int128)T) cout << l << "\n";
    else cout << -1 << "\n";
    delete[] t;
    return 0;
}