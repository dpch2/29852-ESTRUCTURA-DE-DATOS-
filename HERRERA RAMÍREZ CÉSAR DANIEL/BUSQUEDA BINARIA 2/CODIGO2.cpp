#include <bits/stdc++.h>
using namespace std;

long long distanciaMinima(long long x, long long faros[], int m) {
    int left = 0, right = m - 1;
    int pos = m;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (faros[mid] >= x) {
            pos = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    long long distMin = 9000000000000000LL; 
  
    if (pos < m) {
        long long d = faros[pos] - x;
        if (d < 0) d = -d;
        if (d < distMin) distMin = d;
    }

    if (pos - 1 >= 0) {
        long long d = faros[pos - 1] - x;
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

    long long islas[200000], faros[200000];

    for (int i = 0; i < n; i++)
        cin >> islas[i];

    for (int i = 0; i < m; i++)
        cin >> faros[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (islas[j] > islas[j + 1]) {
                long long temp = islas[j];
                islas[j] = islas[j + 1];
                islas[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (faros[j] > faros[j + 1]) {
                long long temp = faros[j];
                faros[j] = faros[j + 1];
                faros[j + 1] = temp;
            }
        }
    }

    long long l = 0, r = 2000000000000LL, ans = r;

    while (l <= r) {
        long long R = (l + r) / 2;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            long long posIsla = islas[i];

            long long distMin = distanciaMinima(posIsla, faros, m);

            if (distMin > R) {
                ok = false;
                break;
            }
        }

        if (ok) {
            ans = R;
            r = R - 1;
        } else {
            l = R + 1;
        }
    }

    cout << ans;
    return 0;
}
