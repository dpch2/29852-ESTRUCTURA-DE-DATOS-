#include <iostream>

// Variables globales para almacenar resultados
const int MAX_PALABRAS = 10000;
const int MAX_LONGITUD = 100;
char palabrasGeneradas[MAX_PALABRAS][MAX_LONGITUD];
int contadorPalabras = 0;

// Función para obtener longitud de cadena
int longitudCadena(const char* cadena) {
    int len = 0;
    while (cadena[len] != '\0') {
        len++;
    }
    return len;
}

// Función para copiar cadena
void copiarCadena(char* destino, const char* fuente) {
    int i = 0;
    while (fuente[i] != '\0') {
        destino[i] = fuente[i];
        i++;
    }
    destino[i] = '\0';
}

// Función para concatenar un carácter a una cadena
void agregarCaracter(char* cadena, char c) {
    int len = longitudCadena(cadena);
    cadena[len] = c;
    cadena[len + 1] = '\0';
}

// Función para verificar si una letra ya está en el array
int letraYaUsada(char letra, const char* letrasUsadas, int cantidad) {
    for (int i = 0; i < cantidad; i++) {
        if (letrasUsadas[i] == letra) {
            return 1;
        }
    }
    return 0;
}

// Función para imprimir cadena
void imprimirCadena(const char* cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        std::cout << cadena[i];
        i++;
    }
}

// Función para guardar palabra generada
void guardarPalabra(const char* palabra) {
    if (contadorPalabras < MAX_PALABRAS) {
        copiarCadena(palabrasGeneradas[contadorPalabras], palabra);
        contadorPalabras++;
    }
}

// Función recursiva para generar todas las combinaciones de m letras
// usando búsqueda exhaustiva (fuerza bruta)
void generarCombinacionesRecursivo(
    const char* letrasDisponibles,
    int nLetras,
    int m,
    char* palabraActual,
    int posicionActual,
    char* letrasUsadas,
    int cantidadUsadas
) {
    // Caso base: si hemos formado una palabra de longitud m
    if (posicionActual == m) {
        palabraActual[posicionActual] = '\0';
        guardarPalabra(palabraActual);
        return;
    }
    
    // Caso recursivo: probar con cada letra disponible
    for (int i = 0; i < nLetras; i++) {
        char letraActual = letrasDisponibles[i];
        
        // Verificar si la letra ya fue usada en esta palabra
        if (!letraYaUsada(letraActual, letrasUsadas, cantidadUsadas)) {
            // Usar esta letra
            palabraActual[posicionActual] = letraActual;
            letrasUsadas[cantidadUsadas] = letraActual;
            
            // Llamada recursiva para la siguiente posición
            generarCombinacionesRecursivo(
                letrasDisponibles,
                nLetras,
                m,
                palabraActual,
                posicionActual + 1,
                letrasUsadas,
                cantidadUsadas + 1
            );
            
            // Backtracking: quitar la letra usada
            letrasUsadas[cantidadUsadas] = '\0';
        }
    }
}

// Función para validar que no haya letras repetidas en la entrada
int validarLetrasUnicas(const char* letras, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (letras[i] == letras[j]) {
                std::cout << "Error: La letra '" << letras[i] << "' esta repetida." << std::endl;
                return 0;
            }
        }
    }
    return 1;
}

// Función para mostrar todas las palabras generadas
void mostrarPalabras(int m) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "  PALABRAS GENERADAS (longitud " << m << ")" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int palabrasPorLinea = 10;
    int contador = 0;
    
    for (int i = 0; i < contadorPalabras; i++) {
        imprimirCadena(palabrasGeneradas[i]);
        std::cout << "  ";
        contador++;
        
        if (contador == palabrasPorLinea) {
            std::cout << std::endl;
            contador = 0;
        }
    }
    
    if (contador != 0) {
        std::cout << std::endl;
    }
    
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Total de palabras generadas: " << contadorPalabras << std::endl;
    std::cout << "========================================" << std::endl;
}

// Función para calcular factorial (para mostrar el resultado esperado)
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// Función para calcular permutaciones P(n, m) = n!/(n-m)!
int calcularPermutaciones(int n, int m) {
    if (m > n) return 0;
    if (m == 0) return 1;
    
    int resultado = 1;
    for (int i = 0; i < m; i++) {
        resultado *= (n - i);
    }
    return resultado;
}

// Función principal
int main() {
    const int MAX_LETRAS = 26;
    char letras[MAX_LETRAS + 1];
    int n, m;
    
    std::cout << "========================================" << std::endl;
    std::cout << "  GENERADOR DE PALABRAS" << std::endl;
    std::cout << "  Busqueda Exhaustiva (Fuerza Bruta)" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nEste programa genera todas las palabras posibles" << std::endl;
    std::cout << "de longitud m usando n letras distintas.\n" << std::endl;
    
    // Solicitar número de letras
    std::cout << "Ingrese el numero de letras disponibles (n): ";
    std::cin >> n;
    
    if (n < 1 || n > MAX_LETRAS) {
        std::cout << "Error: n debe estar entre 1 y " << MAX_LETRAS << std::endl;
        return 1;
    }
    
    // Solicitar las letras
    std::cout << "Ingrese las " << n << " letras (sin espacios, todas diferentes): ";
    std::cin >> letras;
    
    // Validar longitud de entrada
    if (longitudCadena(letras) != n) {
        std::cout << "Error: Debe ingresar exactamente " << n << " letras." << std::endl;
        return 1;
    }
    
    // Validar que no haya letras repetidas
    if (!validarLetrasUnicas(letras, n)) {
        std::cout << "Por favor, ingrese letras diferentes." << std::endl;
        return 1;
    }
    
    // Solicitar longitud de palabras
    std::cout << "Ingrese la longitud de las palabras a generar (m): ";
    std::cin >> m;
    
    if (m < 1 || m > n) {
        std::cout << "Error: m debe estar entre 1 y " << n << std::endl;
        return 1;
    }
    
    // Mostrar información
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Letras disponibles: ";
    imprimirCadena(letras);
    std::cout << std::endl;
    std::cout << "Cantidad de letras (n): " << n << std::endl;
    std::cout << "Longitud de palabras (m): " << m << std::endl;
    
    int permutacionesEsperadas = calcularPermutaciones(n, m);
    std::cout << "Palabras esperadas: P(" << n << "," << m << ") = " 
              << permutacionesEsperadas << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::cout << "\nGenerando palabras..." << std::endl;
    
    // Inicializar variables para la recursión
    char palabraActual[MAX_LONGITUD];
    char letrasUsadas[MAX_LETRAS];
    contadorPalabras = 0;
    
    // Generar todas las combinaciones usando búsqueda exhaustiva
    generarCombinacionesRecursivo(letras, n, m, palabraActual, 0, letrasUsadas, 0);
    
    // Mostrar resultados
    mostrarPalabras(m);
    
    // Verificar que coincidan las cantidades
    if (contadorPalabras == permutacionesEsperadas) {
        std::cout << "\n Verificacion correcta: Se generaron todas las palabras posibles." << std::endl;
    } else {
        std::cout << "\n Advertencia: Diferencia en el conteo." << std::endl;
    }
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "Complejidad: O(n^m) donde n=" << n << " y m=" << m << std::endl;
    std::cout << "Metodo: Backtracking con busqueda exhaustiva" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}