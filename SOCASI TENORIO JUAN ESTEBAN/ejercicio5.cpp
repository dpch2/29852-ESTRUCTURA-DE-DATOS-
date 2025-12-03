#include <bits/stdc++.h>
using namespace std;

long long hashSumaASCII(const string& s) {
    long long h = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        h += (int)s[i];  // suma el código ASCII
    }
    return h;
}

bool sonAnagramas(const string& A, const string& B) {
    if (A.size() != B.size()) return false; // si longitudes difieren, no puede haber anagrama

    long long hashA = hashSumaASCII(A);
    long long hashB = hashSumaASCII(B);

    return hashA == hashB;
}

int main() {
    string A, B;
    getline(cin, A);
    getline(cin, B);

    if (sonAnagramas(A, B)) cout << "SI\n";
    else cout << "NO\n";

    return 0;
}
