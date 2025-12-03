#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    long long parcelas[200000], aspersores[200000];

    for (int i = 0; i < n; i++)
        cin >> parcelas[i];
    for (int i = 0; i < m; i++)
        cin >> aspersores[i];

    // ----- ORDENAR PARCELAS -----
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (parcelas[j] > parcelas[j + 1])
            {
                long long tmp = parcelas[j];
                parcelas[j] = parcelas[j + 1];
                parcelas[j + 1] = tmp;
            }
        }
    }

    // ----- ORDENAR ASPERSORES -----
    for (int i = 0; i < m - 1; i++)
    {
        for (int j = 0; j < m - 1 - i; j++)
        {
            if (aspersores[j] > aspersores[j + 1])
            {
                long long tmp = aspersores[j];
                aspersores[j] = aspersores[j + 1];
                aspersores[j + 1] = tmp;
            }
        }
    }

    long long l = 0, r = 2000000000000LL, ans = r;

    while (l <= r)
    {
        long long R = (l + r) / 2;

        int diff[200001];
        for (int i = 0; i <= n; i++)
            diff[i] = 0;

        // marcar intervalos de cobertura manualmente
        for (int i = 0; i < m; i++)
        {
            long long a = aspersores[i];
            long long L = a - R;
            long long RR = a + R;

            // encontrar primer índice >= L
            int li = n;
            for (int k = 0; k < n; k++)
            {
                if (parcelas[k] >= L)
                {
                    li = k;
                    break;
                }
            }

            // encontrar último índice <= RR
            int ri = -1;
            for (int k = n - 1; k >= 0; k--)
            {
                if (parcelas[k] <= RR)
                {
                    ri = k;
                    break;
                }
            }

            if (li <= ri && li < n && ri >= 0)
            {
                diff[li]++;
                diff[ri + 1]--;
            }
        }

        int sum = 0;
        bool ok = true;

        for (int i = 0; i < n; i++)
        {
            sum += diff[i];
            if (sum == 0)
            {
                ok = false;
                break;
            }
        }

        if (ok)
        {
            ans = R;
            r = R - 1;
        }
        else
        {
            l = R + 1;
        }
    }

    cout << ans;
    return 0;
}