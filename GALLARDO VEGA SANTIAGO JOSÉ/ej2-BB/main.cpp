//Encontrar la cantidad minima de movimientos para que todos los asteriscos
//esten juntos
#include <iostream>
#include <string>
#include <cmath> 

long long calculate_cost(long long s, int sheep_count, int* sheep_pos) {
    long long total_cost = 0;
    for (int i = 0; i < sheep_count; ++i) {
        total_cost += std::abs(sheep_pos[i] - (s + i));
    }
    return total_cost;
}

void solve() {
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    int sheep_count = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '*') {
            sheep_count++;
        }
    }

    if (sheep_count == 0 || sheep_count == n) {
        std::cout << 0 << "\n";
        return;
    }

    
    int* sheep_pos = new int[sheep_count];
    int current_sheep = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '*') {
            sheep_pos[current_sheep] = i;
            current_sheep++;
        }
    }

    long long low = 0;
    long long high = n - sheep_count;
    long long ans_s = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long cost1 = calculate_cost(mid, sheep_count, sheep_pos);
        long long cost2 = calculate_cost(mid + 1, sheep_count, sheep_pos);

        if (cost1 < cost2) {
            ans_s = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    std::cout << calculate_cost(ans_s, sheep_count, sheep_pos) << "\n";

    delete[] sheep_pos;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
