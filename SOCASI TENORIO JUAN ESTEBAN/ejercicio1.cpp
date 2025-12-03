#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    long long* a = new long long[n];
    for (int i = 0; i < n; ++i) cin >> a[i];

    if (n == 0) { cout << -1 << "\n"; delete[] a; return 0; }
    int l = 0, r = n - 1;
    if (a[l] <= a[r]) { cout << l << "\n"; delete[] a; return 0; }
    while (l < r) {
        int m = l + (r - l) / 2;
        if (a[m] > a[r]) l = m + 1;
        else r = m;
    }
    cout << l << "\n";
    delete[] a;
    return 0;
}