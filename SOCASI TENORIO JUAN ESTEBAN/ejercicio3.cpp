#include <bits/stdc++.h>
using namespace std;

bool feasible(long long* pos, int M, int K, long long D) {
    int count = 1;
    long long last = pos[0];
    for (int i = 1; i < M; ++i) {
        if (pos[i] - last >= D) {
            ++count;
            last = pos[i];
            if (count >= K) return true;
        }
    }
    return count >= K;
}

int main() {
    int M, K;
    if (!(cin >> M >> K)) return 0;
    long long* pos = new long long[M];
    for (int i = 0; i < M; ++i) cin >> pos[i];
    sort(pos, pos + M);
    long long low = 0;
    long long high = pos[M-1] - pos[0] + 1; // búsqueda en [low, high)
    while (low + 1 < high) {
        long long mid = low + (high - low) / 2;
        if (feasible(pos, M, K, mid)) low = mid;
        else high = mid;
    }
    cout << low << "\n";
    delete[] pos;
    return 0;
}