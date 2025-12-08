#include <iostream>
using namespace std;

int main()
{
    string nombres[] = {
        "Iron Man", "War Machine", "Black Widow",
        "Thor", "Shang-Chi", "Moon Knight"};

    int anios[] = {2008, 2008, 2010, 2011, 2021, 2022};

    int n = 6;

    // Primer año y último año (sin recorrer toda la lista)
    int primerAnio = anios[0];
    int ultimoAnio = anios[n - 1];

    cout << "Primeros personajes en aparecer:\n";
    int i = 0;
    while (i < n && anios[i] == primerAnio)
    {
        cout << "- " << nombres[i] << " (" << anios[i] << ")\n";
        i++;
    }

    cout << "\nUltimos personajes en aparecer:\n";
    int j = n - 1;
    while (j >= 0 && anios[j] == ultimoAnio)
    {
        cout << "- " << nombres[j] << " (" << anios[j] << ")\n";
        j--;
    }

    return 0;
}