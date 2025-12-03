#include <bits/stdc++.h>
using namespace std;

long long distanciaMinima(long long x, long long recarga[], int m) {
    int left = 0, right = m - 1;
    int pos = m;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (recarga[mid] >= x) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    long long distMin = 9000000000000000LL;

    if (pos < m) {
        long long d = recarga[pos] - x;
        if (d < 0) d = -d;
        if (d < distMin) distMin = d;
    }

    if (pos - 1 >= 0) {
        long long d = recarga[pos - 1] - x;
        if (d < 0) d = -d;
        if (d < distMin) distMin = d;
    }

    return distMin;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    long long autos[200000], recarga[200000];

    for (int i = 0; i < n; i++)
        cin >> autos[i];

    for (int i = 0; i < m; i++)
        cin >> recarga[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (autos[j] > autos[j + 1]) {
                long long temp = autos[j];
                autos[j] = autos[j + 1];
                autos[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (recarga[j] > recarga[j + 1]) {
                long long temp = recarga[j];
                recarga[j] = recarga[j + 1];
                recarga[j + 1] = temp;
            }
        }
    }

    long long l = 0, r = 2000000000000LL, ans = r;

    while (l <= r) {
        long long R = (l + r) / 2;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            long long posAuto = autos[i];

            long long distMin = distanciaMinima(posAuto, recarga, m);

            if (distMin > R) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = R;
            r = R - 1;
        } else {
            l = R + 1l
        }
    }

    cout << ans;
    return 0;
}
