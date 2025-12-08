#include <iostream>
using namespace std;

int hashFuncion(int x)
{
    return x % 101;
}

int main()
{

    int T[101];

    long long dni = 234661454;

    int posicion = hashFuncion(dni);

    cout << "DNI: " << dni << endl;
    cout << "Posicion en la tabla hash: " << posicion << endl;

    return 0;
}