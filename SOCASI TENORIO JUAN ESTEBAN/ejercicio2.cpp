#include <bits/stdc++.h>
using namespace std;
int main() {
 
    int n;
    long long X;
    if (!(cin >> n >> X)) return 0;
    long long* a = new long long[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    int l = 0, r = n; // [l, r)
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] >= X) r = m;
        else l = m + 1;
    }
    if (l < n && a[l] >= X) cout << l << "\n";
    else cout << -1 << "\n";
    delete[] a;
    return 0;
}