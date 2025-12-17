#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

struct Estudiante {
    char nombre1[30];
    char nombre2[30];
    char apellido1[30];
    char apellido2[30];
};

// =========================
// VALIDAR SOLO LETRAS
// =========================
bool soloLetras(const char* texto) {
    int len = strlen(texto);
    if (len == 0) return false;

    for (int i = 0; i < len; i++) {
        if (!isalpha(texto[i])) {
            return false;
        }
    }
    return true;
}

// =========================
// PEDIR TEXTO VALIDADO
// =========================
void pedirCampo(const char* mensaje, char* destino) {
    do {
        cout << " " << mensaje;
        cin >> destino;

        if (!soloLetras(destino)) {
            cout << "   ERROR: Solo letras permitidas. Intente nuevamente.\n";
        }
    } while (!soloLetras(destino));
}

// =========================
// COMPARAR APELLIDOS
// =========================
int comparar(const Estudiante &a, const Estudiante &b) {
    return strcmp(a.apellido1, b.apellido1);
}

// =========================
// ORDENAR CON PUNTEROS
// =========================
void ordenarEstudiantes(Estudiante *arr, int n) {
    Estudiante temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (comparar(*(arr + j), *(arr + j + 1)) > 0) {
                temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
}

// =========================
// BUSCAR SI COINCIDE
// =========================
bool coincide(const Estudiante &e, const char *buscado) {
    if (strstr(e.nombre1, buscado)) return true;
    if (strstr(e.nombre2, buscado)) return true;
    if (strstr(e.apellido1, buscado)) return true;
    if (strstr(e.apellido2, buscado)) return true;
    return false;
}

// =========================
// BUSCAR E IMPRIMIR
// =========================
void buscar(Estudiante *arr, int n) {
    char buscado[30];

    cout << "\nIngrese texto a buscar (nombre o apellido): ";
    cin >> buscado;

    if (!soloLetras(buscado)) {
        cout << "Entrada invalida: solo letras.\n";
        return;
    }

    cout << "\n=== RESULTADOS ENCONTRADOS ===\n";

    bool found = false;
    for (int i = 0; i < n; i++) {
        if (coincide(*(arr + i), buscado)) {
            found = true;
            cout << arr[i].nombre1 << " "
                 << arr[i].nombre2 << " "
                 << arr[i].apellido1 << " "
                 << arr[i].apellido2 << endl;
        }
    }

    if (!found)
        cout << "No se encontraron coincidencias.\n";
}

// =========================
// PROGRAMA PRINCIPAL
// =========================
int main() {
    int n;
    cout << "Cuantos estudiantes desea ingresar?: ";
    cin >> n;

    Estudiante *est = new Estudiante[n];

    cout << "\nIngrese los estudiantes (desordenados):\n"
         << "Cada campo separado. Solo LETRAS.\n\n";

    for (int i = 0; i < n; i++) {

        cout << "Estudiante " << i + 1 << ":\n";

        pedirCampo("Nombre1:", est[i].nombre1);
        pedirCampo("Nombre2:", est[i].nombre2);
        pedirCampo("Apellido1:", est[i].apellido1);
        pedirCampo("Apellido2:", est[i].apellido2);

        cout << endl;
    }

    // Ordenar automáticamente por primer apellido
    ordenarEstudiantes(est, n);

    int opcion;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Buscar estudiante\n";
        cout << "2. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                buscar(est, n);
                break;

            case 2:
                cout << "Saliendo...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 2);

    delete[] est;
    return 0;
}
