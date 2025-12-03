//encontrar si un numero es T primo

#include <iostream>
#include <cmath>

bool hasDivisorInRange(long long n, long long low, long long high) {
    if (low > high) {
        return false;
    }
    long long mid = low + (high - low) / 2;

    if (mid % 2 == 0) {
        if (mid > low) {
            mid--; 
        } else {
            return hasDivisorInRange(n, low + 1, high);
        }
    }


    for (long long i = mid; i >= low; i -= 2) {
        if (n % i == 0) return true;
    }

        return hasDivisorInRange(n, mid + 2, high);
}

bool isPrime(long long n) {
    if (n < 2) {
        return false;
    }
    if (n == 2) {
        return true;
    }
    if (n % 2 == 0) {
        return false;
    }
    long long limit = sqrt(n);
    
    return !hasDivisorInRange(n, 3, limit);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;

        long long root = round(sqrt(x));

        if (root * root == x && isPrime(root)) {
            std::cout << "SI\n";
        } else {
            std::cout << "NO\n";
        }
    }

    return 0;
}
