#include <iostream>
#include <cmath> 

using namespace std;

void ordenarBurbuja(long long arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                long long temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int busquedaBinaria(long long arr[], int n, long long objetivo) {
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (arr[medio] == objetivo) {
            return medio;
        }

        if (arr[medio] < objetivo) {
            izquierda = medio + 1;
        }
        else {
            derecha = medio - 1;
        }
    }
    return -1; 
}

void realizarHashing(long long clave) {
    cout << "\n--- Inicio del Proceso de Hashing (Plegamiento) ---" << endl;
    cout << "Clave original: " << clave << endl;

    long long parte1 = clave / 100000;
    long long parte2 = (clave % 100000) / 100;
    long long parte3 = clave % 100;

    cout << "Parte 1 extraida: " << parte1 << endl;
    cout << "Parte 2 extraida: " << parte2 << endl;
    cout << "Parte 3 extraida: " << parte3 << endl;

    long long suma = parte1 + parte2 + parte3;
    cout << "Suma: " << parte1 << " + " << parte2 << " + " << parte3 << " = " << suma << endl;

    int direccion = suma % 1000;

    cout << "Truncamiento (para rango de direcciones): " << suma << " -> " << direccion << endl;
    cout << "DIRECCION FINAL: " << direccion << endl;
}

int main() {
    int opcion;
    long long claves[100];
    int n = 0;

    cout << "=== SISTEMA DE BUSQUEDA BINARIA Y HASHING ===" << endl;
    cout << endl;

    // Cargar claves predeterminadas
    long long clavesPredeterminadas[] = {12345678, 99999999, 62538194, 11112222, 55555555, 87654321};
    n = 6;
    for(int i = 0; i < n; i++) {
        claves[i] = clavesPredeterminadas[i];
    }

    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Ver claves cargadas" << endl;
        cout << "2. Agregar nueva clave" << endl;
        cout << "3. Eliminar clave" << endl;
        cout << "4. Buscar clave y calcular hash" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch(opcion) {
            case 1: {
                if(n == 0) {
                    cout << "[INFO] No hay claves cargadas." << endl;
                } else {
                    ordenarBurbuja(claves, n);
                    cout << "Claves cargadas (ordenadas): ";
                    for(int i = 0; i < n; i++) {
                        cout << claves[i] << " ";
                    }
                    cout << endl;
                }
                break;
            }
            case 2: {
                if(n >= 100) {
                    cout << "[ERROR] No se pueden agregar mas claves (limite alcanzado)." << endl;
                } else {
                    long long nuevaClave;
                    cout << "Ingrese la nueva clave (numero de 8 digitos): ";
                    cin >> nuevaClave;
                    claves[n] = nuevaClave;
                    n++;
                    cout << "[EXITO] Clave agregada correctamente." << endl;
                }
                break;
            }
            case 3: {
                if(n == 0) {
                    cout << "[ERROR] No hay claves para eliminar." << endl;
                } else {
                    long long claveEliminar;
                    cout << "Ingrese la clave a eliminar: ";
                    cin >> claveEliminar;
                    
                    int indice = -1;
                    for(int i = 0; i < n; i++) {
                        if(claves[i] == claveEliminar) {
                            indice = i;
                            break;
                        }
                    }
                    
                    if(indice != -1) {
                        for(int i = indice; i < n - 1; i++) {
                            claves[i] = claves[i + 1];
                        }
                        n--;
                        cout << "[EXITO] Clave eliminada correctamente." << endl;
                    } else {
                        cout << "[ERROR] La clave no se encuentra." << endl;
                    }
                }
                break;
            }
            case 4: {
                if(n == 0) {
                    cout << "[ERROR] No hay claves para buscar." << endl;
                } else {
                    long long objetivo;
                    cout << "Ingrese la clave a buscar: ";
                    cin >> objetivo;
                    cout << endl;

                    ordenarBurbuja(claves, n);
                    cout << "Claves ordenadas: ";
                    for(int i = 0; i < n; i++) cout << claves[i] << " ";
                    cout << endl;

                    int indice = busquedaBinaria(claves, n, objetivo);

                    if (indice != -1) {
                        cout << "\n[EXITO] Clave " << objetivo << " encontrada en el indice " << indice << " del arreglo local." << endl;
                        cout << "Procediendo a calcular su direccion Hash " << endl;
                        realizarHashing(claves[indice]);
                    } else {
                        cout << "[ERROR] La clave no se encuentra en la base de datos." << endl;
                    }
                }
                break;
            }
            case 5: {
                cout << "Gracias por usar el programa. Hasta luego!" << endl;
                break;
            }
            default: {
                cout << "[ERROR] Opcion no valida. Intente nuevamente." << endl;
            }
        }
    } while(opcion != 5);

    return 0;
}