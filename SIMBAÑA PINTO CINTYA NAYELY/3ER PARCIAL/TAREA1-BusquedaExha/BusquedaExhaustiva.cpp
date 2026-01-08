#include <iostream>
#include <fstream>

// Variables globales para el conteo de operaciones
int contadorOperaciones = 0;
int tamanoProblema = 0;

// Función para escribir en archivo (implementación manual)
void escribirArchivo(const char* nombreArchivo, const char* texto) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo != NULL) {
        fprintf(archivo, "%s", texto);
        fclose(archivo);
    }
}

// Función para agregar texto al archivo
void agregarTexto(const char* nombreArchivo, const char* texto) {
    FILE* archivo = fopen(nombreArchivo, "a");
    if (archivo != NULL) {
        fprintf(archivo, "%s", texto);
        fclose(archivo);
    }
}

// Función para convertir entero a cadena
void intACadena(int num, char* cadena) {
    int i = 0;
    int esNegativo = 0;
    
    if (num < 0) {
        esNegativo = 1;
        num = -num;
    }
    
    if (num == 0) {
        cadena[i++] = '0';
        cadena[i] = '\0';
        return;
    }
    
    // Extraer dígitos en orden inverso
    int inicio = i;
    while (num > 0) {
        cadena[i++] = (num % 10) + '0';
        num /= 10;
    }
    
    if (esNegativo) {
        cadena[i++] = '-';
    }
    
    cadena[i] = '\0';
    
    // Invertir la cadena
    int fin = i - 1;
    inicio = 0;
    while (inicio < fin) {
        char temp = cadena[inicio];
        cadena[inicio] = cadena[fin];
        cadena[fin] = temp;
        inicio++;
        fin--;
    }
}

// Función para concatenar cadenas
void concatenarCadenas(char* destino, const char* fuente) {
    int i = 0;
    while (destino[i] != '\0') {
        i++;
    }
    
    int j = 0;
    while (fuente[j] != '\0') {
        destino[i++] = fuente[j++];
    }
    destino[i] = '\0';
}

// Función para copiar cadenas
void copiarCadena(char* destino, const char* fuente) {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
    }
    destino[i] = '\0';
}

// Función para obtener longitud de cadena
int longitudCadena(const char* cadena) {
    int len = 0;
    while (cadena[len] != '\0') {
        len++;
    }
    return len;
}

// Función para abrir MATLAB y ejecutar el script de graficación
void abrirMATLAB() {
    std::cout << "\nAbriendo MATLAB para graficar los datos..." << std::endl;
    
    // Comando para abrir MATLAB y ejecutar el script
    // En Windows, usamos 'start' para abrir MATLAB en paralelo
    system("start matlab -r \"cd(pwd); graficar_complejidad; disp('Presione cualquier tecla para cerrar MATLAB')\" ");
    
    std::cout << "MATLAB se abrirá en una nueva ventana..." << std::endl;
}

// Función para validar si un carácter es dígito
int esDigito(char c) {
    return c >= '0' && c <= '9';
}

// Función para convertir cadena a entero
int cadenaAInt(const char* cadena, int* exito) {
    int resultado = 0;
    int i = 0;
    int signo = 1;
    
    *exito = 1;
    
    // Manejar signo negativo
    if (cadena[i] == '-') {
        signo = -1;
        i++;
    }
    
    // Validar que solo contenga dígitos
    if (cadena[i] == '\0') {
        *exito = 0;
        return 0;
    }
    
    while (cadena[i] != '\0') {
        if (!esDigito(cadena[i])) {
            *exito = 0;
            return 0;
        }
        resultado = resultado * 10 + (cadena[i] - '0');
        i++;
    }
    
    return resultado * signo;
}

// Función recursiva para buscar pares que sumen 20 (fuerza bruta)
void buscarParesRecursivo(int inicio, int limite, int objetivo, int nivel) {
    contadorOperaciones++; // Incrementar contador de operaciones
    
    // Caso base: si hemos llegado al límite
    if (inicio > limite) {
        return;
    }
    
    // Buscar el segundo número que complete la suma
    for (int j = inicio + 1; j <= limite; j++) {
        contadorOperaciones++; // Contar cada comparación
        
        if (inicio + j == objetivo) {
            std::cout << inicio << " + " << j << " = " << objetivo << std::endl;
        }
    }
    
    // Llamada recursiva para el siguiente número
    buscarParesRecursivo(inicio + 1, limite, objetivo, nivel + 1);
}

// Función para verificar un par específico
void verificarPar(int num1, int num2, int objetivo, int rangoMin, int rangoMax) {
    contadorOperaciones = 0;
    
    std::cout << "\n=== VERIFICACION DE PAR ESPECIFICO ===" << std::endl;
    std::cout << "Numero 1: " << num1 << std::endl;
    std::cout << "Numero 2: " << num2 << std::endl;
    
    // Validar que ambos números estén en el rango
    int dentroRango = 1;
    
    if (num1 < rangoMin || num1 > rangoMax) {
        std::cout << " ERROR: El primer numero (" << num1 << ") esta FUERA del rango permitido [" 
                  << rangoMin << "-" << rangoMax << "]" << std::endl;
        dentroRango = 0;
    }
    
    if (num2 < rangoMin || num2 > rangoMax) {
        std::cout << " ERROR: El segundo numero (" << num2 << ") esta FUERA del rango permitido [" 
                  << rangoMin << "-" << rangoMax << "]" << std::endl;
        dentroRango = 0;
    }
    
    if (!dentroRango) {
        std::cout << "\nVALIDACION FALLIDA: Uno o ambos numeros no cumplen con el rango." << std::endl;
        return;
    }
    
    // Si ambos están en rango, proceder con la verificación
    std::cout << " Ambos numeros estan dentro del rango [" << rangoMin << "-" << rangoMax << "]" << std::endl;
    std::cout << "\nCalculando suma..." << std::endl;
    std::cout << "Suma: " << num1 << " + " << num2 << " = " << (num1 + num2) << std::endl;
    
    contadorOperaciones = 1; // Una operación de suma
    
    if (num1 + num2 == objetivo) {
        std::cout << "\n";
        std::cout << " RESULTADO CORRECTO " << std::endl;
        std::cout << "  " << num1 << " + " << num2 << " = " << objetivo << std::endl;
        std::cout << "  Los numeros SI suman el objetivo!" << std::endl;
    } else {
        std::cout << "\n";
        std::cout << " RESULTADO INCORRECTO " << std::endl;
        std::cout << "  " << num1 << " + " << num2 << " = " << (num1 + num2) 
                  << " (se esperaba: " << objetivo << ")" << std::endl;
        std::cout << "  Los numeros NO suman el objetivo." << std::endl;
        std::cout << "  Diferencia: " << ((num1 + num2) - objetivo) << std::endl;
    }
    
    std::cout << "\nOperaciones realizadas: " << contadorOperaciones << std::endl;
}

// Función para validar entrada numérica
int leerNumeroValidado(int min, int max, const char* mensaje) {
    char entrada[100];
    int numero;
    int exito;
    
    while (1) {
        std::cout << mensaje;
        std::cin >> entrada;
        
        numero = cadenaAInt(entrada, &exito);
        
        if (!exito) {
            std::cout << "Error: Debe ingresar solo numeros. Intente nuevamente." << std::endl;
            continue;
        }
        
        if (numero < min || numero > max) {
            std::cout << "Error: El numero debe estar entre " << min << " y " << max 
                      << ". Intente nuevamente." << std::endl;
            continue;
        }
        
        return numero;
    }
}

// Función para generar datos de complejidad temporal
void generarDatosComplejidad() {
    std::cout << "\n=== GENERANDO DATOS DE COMPLEJIDAD TEMPORAL ===" << std::endl;
    
    // Crear archivo para datos de complejidad
    escribirArchivo("complejidad_datos.txt", "% Datos de complejidad temporal\n");
    agregarTexto("complejidad_datos.txt", "% Tamaño_Problema Operaciones\n");
    
    // Probar con diferentes tamaños de problema
    int tamanos[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 99};
    int numTamanos = 10;
    
    for (int i = 0; i < numTamanos; i++) {
        contadorOperaciones = 0;
        tamanoProblema = tamanos[i];
        
        // Ejecutar búsqueda sin imprimir resultados
        for (int j = 1; j <= tamanoProblema; j++) {
            for (int k = j + 1; k <= tamanoProblema; k++) {
                contadorOperaciones++;
                // No imprimimos, solo contamos
            }
        }
        
        // Guardar datos en archivo
        char linea[200];
        char numTam[50], numOp[50];
        intACadena(tamanoProblema, numTam);
        intACadena(contadorOperaciones, numOp);
        
        copiarCadena(linea, numTam);
        concatenarCadenas(linea, " ");
        concatenarCadenas(linea, numOp);
        concatenarCadenas(linea, "\n");
        
        agregarTexto("complejidad_datos.txt", linea);
        
        std::cout << "N=" << tamanoProblema << " -> Operaciones: " << contadorOperaciones << std::endl;
    }
    
    // Crear script de MATLAB
    escribirArchivo("graficar_complejidad.m", 
        "% Script para graficar complejidad temporal\n"
        "clear; clc;\n\n"
        "% Leer datos del archivo\n"
        "datos = load('complejidad_datos.txt');\n"
        "n = datos(:, 1);\n"
        "operaciones = datos(:, 2);\n\n"
        "% Crear figura\n"
        "figure('Position', [100, 100, 800, 600]);\n\n"
        "% Graficar datos reales\n"
        "plot(n, operaciones, 'bo-', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'b');\n"
        "hold on;\n\n"
        "% Graficar curva teorica O(n^2)\n"
        "n_teorico = linspace(min(n), max(n), 100);\n"
        "operaciones_teoricas = (n_teorico .* (n_teorico - 1)) / 2;\n"
        "plot(n_teorico, operaciones_teoricas, 'r--', 'LineWidth', 1.5);\n\n"
        "% Configurar grafica\n"
        "xlabel('Tamaño del Problema (N)', 'FontSize', 12, 'FontWeight', 'bold');\n"
        "ylabel('Numero de Operaciones', 'FontSize', 12, 'FontWeight', 'bold');\n"
        "title('Complejidad Temporal - Busqueda Exhaustiva de Pares', 'FontSize', 14, 'FontWeight', 'bold');\n"
        "legend('Datos Reales', 'Complejidad Teorica O(n^2)', 'Location', 'northwest');\n"
        "grid on;\n"
        "hold off;\n\n"
        "% Guardar grafica\n"
        "saveas(gcf, 'complejidad_temporal.png');\n"
        "disp('Grafica generada exitosamente: complejidad_temporal.png');\n"
    );
    
    std::cout << "\nArchivos generados:" << std::endl;
    std::cout << "  - complejidad_datos.txt (datos de complejidad)" << std::endl;
    std::cout << "  - graficar_complejidad.m (script de MATLAB)" << std::endl;
    
    // Abrir MATLAB automáticamente
    abrirMATLAB();
}

// Función principal
int main(int argc, char* argv[]) {
    // Verificar si se ejecuta desde MATLAB con parámetro de modo
    if (argc == 2 && cadenaAInt(argv[1], &argc) == 1) {
        // Modo: ejecutar directamente la generación de datos
        generarDatosComplejidad();
        return 0;
    }
    
    // Modo interactivo (si se ejecuta sin parámetros)
    int opcion;
    const int RANGO_MIN = 1;
    const int RANGO_MAX = 99;
    const int OBJETIVO = 80;
    
    std::cout << "========================================" << std::endl;
    std::cout << "  BUSQUEDA DE PARES QUE SUMAN 80" << std::endl;
    std::cout << "  Algoritmo de Fuerza Bruta Recursivo" << std::endl;
    std::cout << "========================================" << std::endl;
    
    while (1) {
        std::cout << "\n--- MENU PRINCIPAL ---" << std::endl;
        std::cout << "1. Buscar todos los pares que suman 20" << std::endl;
        std::cout << "2. Verificar un par especifico" << std::endl;
        std::cout << "3. Generar datos de complejidad temporal" << std::endl;
        std::cout << "4. Salir" << std::endl;
        
        opcion = leerNumeroValidado(1, 4, "Seleccione una opcion (1-4): ");
        
        if (opcion == 1) {
            std::cout << "\n=== BUSCANDO TODOS LOS PARES ===" << std::endl;
            std::cout << "Rango: " << RANGO_MIN << " a " << RANGO_MAX << std::endl;
            std::cout << "Objetivo: " << OBJETIVO << std::endl;
            std::cout << "\nResultados:" << std::endl;
            
            contadorOperaciones = 0;
            tamanoProblema = RANGO_MAX;
            
            buscarParesRecursivo(RANGO_MIN, RANGO_MAX, OBJETIVO, 0);
            
            std::cout << "\nOperaciones realizadas: " << contadorOperaciones << std::endl;
            std::cout << "Complejidad: O(n^2) donde n = " << RANGO_MAX << std::endl;
            
        } else if (opcion == 2) {
            std::cout << "\n=== VERIFICAR PAR ESPECIFICO ===" << std::endl;
            std::cout << "Rango permitido: " << RANGO_MIN << " a " << RANGO_MAX << std::endl;
            std::cout << "Objetivo de suma: " << OBJETIVO << std::endl;
            std::cout << "\nIngrese dos numeros para verificar si suman " << OBJETIVO << ":\n" << std::endl;
            
            int num1 = leerNumeroValidado(RANGO_MIN, RANGO_MAX, 
                "Ingrese el primer numero (1-99): ");
            int num2 = leerNumeroValidado(RANGO_MIN, RANGO_MAX, 
                "Ingrese el segundo numero (1-99): ");
            
            verificarPar(num1, num2, OBJETIVO, RANGO_MIN, RANGO_MAX);
            
        } else if (opcion == 3) {
            generarDatosComplejidad();
            
        } else if (opcion == 4) {
            std::cout << "\nGracias por usar el programa. ¡Hasta luego!" << std::endl;
            break;
        }
    }
    
    return 0;
}