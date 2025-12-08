#include <iostream>
int busquedaBinariaGarantizada(const int A[], int n, int K)
{
    if (n <= 0)
    {
        return -1;
    }

    int inicio = 0;
    int fin = n - 1;
    while (inicio < fin)
    {

        int mid = inicio + (fin - inicio) / 2;

        if (K <= A[mid])
        {
            fin = mid;
        }
        else
        {
            inicio = mid + 1;
        }
    }

    return inicio;
}

int main()
{
    const int A[] = {10, 20, 30, 40, 50, 60, 70};
    const int n = 7;

    std::cout << "--- Busqueda Binaria Optimizada (K Garantizado) ---" << std::endl;
    std::cout << "Arreglo A: {10, 20, 30, 40, 50, 60, 70}" << std::endl;

    for (int K : A)
    {
        int resultado = busquedaBinariaGarantizada(A, n, K);
        std::cout << "Buscando K=" << K << ": Encontrado en el indice " << resultado << " (A[" << resultado << "])" << std::endl;
    }

    const int B[] = {5, 15, 25, 35};
    const int m = 4;
    std::cout << "\n--- Pruebas con n=4 ---" << std::endl;
    for (int K : B)
    {
        int resultado = busquedaBinariaGarantizada(B, m, K);
        std::cout << "Buscando K=" << K << ": Encontrado en el indice " << resultado << " (B[" << resultado << "])" << std::endl;
    }

    return 0;
}