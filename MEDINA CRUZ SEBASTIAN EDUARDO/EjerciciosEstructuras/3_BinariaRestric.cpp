#include <iostream>

int busquedaBinariaUnaComparacion(const int A[], int n, int K)
{
    if (n <= 0)
    {
        return -1;
    }

    int inicio = 0;
    int fin = n - 1;
    while (inicio <= fin)
    {
        int mid = inicio + (fin - inicio) / 2;

        if (K <= A[mid])
        {
            fin = mid - 1;
        }
        else
        {
            inicio = mid + 1;
        }
    }

    if (inicio < n)
    {
        if (K == A[inicio])
        {
            return inicio;
        }
    }
    return -1;
}

int main()
{
    const int A[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    const int n = 9;

    int K1 = 40;
    int K2 = 45;
    int K3 = 10;
    int K4 = 100;

    std::cout << "--- Busqueda Binaria ---" << std::endl;

    // Ejecución de pruebas
    std::cout << "Buscando " << K1 << ": indice " << busquedaBinariaUnaComparacion(A, n, K1) << std::endl;
    std::cout << "Buscando " << K2 << ": indice " << busquedaBinariaUnaComparacion(A, n, K2) << std::endl;
    std::cout << "Buscando " << K3 << ": indice " << busquedaBinariaUnaComparacion(A, n, K3) << std::endl;
    std::cout << "Buscando " << K4 << ": indice " << busquedaBinariaUnaComparacion(A, n, K4) << std::endl;

    return 0;
}