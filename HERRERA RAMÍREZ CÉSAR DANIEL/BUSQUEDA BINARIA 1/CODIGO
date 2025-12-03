#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    long long pueblos[200000], hospitales[200000];

    for (int i = 0; i < n; i++)
        cin >> pueblos[i];

    for (int i = 0; i < m; i++)
        cin >> hospitales[i];

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (pueblos[j] > pueblos[j + 1]) {
                long long temp = pueblos[j];
                pueblos[j] = pueblos[j + 1];
                pueblos[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (hospitales[j] > hospitales[j + 1]) {
                long long temp = hospitales[j];
                hospitales[j] = hospitales[j + 1];
                hospitales[j + 1] = temp;
            }
        }
    }

    long long l = 0, r = 2000000000000LL, ans = r;

    while (l <= r) {
        long long R = (l + r) / 2;
        bool ok = true;

        for (int i = 0; i < n; i++) {
            long long p = pueblos[i];

            long long distMin = 9000000000000000LL;

            for (int j = 0; j < m; j++) {
                long long d = p - hospitales[j];
                if (d < 0) d = -d;
                if (d < distMin)
                    distMin = d;
            }

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

