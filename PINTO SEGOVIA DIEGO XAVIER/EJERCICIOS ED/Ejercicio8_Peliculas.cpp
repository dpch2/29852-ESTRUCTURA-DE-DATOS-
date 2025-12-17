#include <iostream>
#include <vector>
#include <string>
#include <iomanip>   
#include <algorithm> 
#include <cctype>    
#include <tuple>     

struct Pelicula {
    std::string tituloOriginal;    // Título exacto para mostrar
    std::string tituloNormalizado; // Título en minúsculas para la búsqueda/ordenamiento
    int anioEstreno;
    double recaudacion;
    int valoracion;
};

// Función auxiliar: Normaliza una cadena a minúsculas
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

// Función de comparación para ordenar por el título normalizado
bool compararPorTituloNormalizado(const Pelicula& a, const Pelicula& b) {
    return a.tituloNormalizado < b.tituloNormalizado;
}

// Función auxiliar para mostrar la información de una película
void mostrarInfoPelicula(const Pelicula& p, size_t indice) {
    std::cout << "------------------------------------------\n";
    std::cout << "Pelicula encontrada en la posicion/indice (en lista ordenada): " << indice << std::endl;
    std::cout << std::left << std::setw(20) << "Titulo:" << p.tituloOriginal << std::endl;
    std::cout << std::left << std::setw(20) << "Anio de Estreno:" << p.anioEstreno << std::endl;
    std::cout << std::left << std::setw(20) << "Recaudacion (M):" << std::fixed << std::setprecision(2) << p.recaudacion << std::endl;
    std::cout << std::left << std::setw(20) << "Valoracion (1-5):" << p.valoracion << std::endl;
    std::cout << "------------------------------------------\n";
}

size_t busquedaBinariaPelicula(const std::vector<Pelicula>& lista, size_t inicio, size_t fin, const std::string& claveNormalizada) {
    // Caso Base de Falla (El segmento de búsqueda es inválido o se ha superado el límite)
    if (inicio > fin || inicio >= lista.size()) {
        return lista.size(); // Retorna un índice que está fuera de rango
    }

    size_t medio = inicio + (fin - inicio) / 2;
    const std::string& tituloMedioNormalizado = lista[medio].tituloNormalizado;

    // Caso de Éxito
    if (tituloMedioNormalizado == claveNormalizada) {
        return medio;
    } 
    // Buscar a la izquierda
    else if (claveNormalizada < tituloMedioNormalizado) {
        // Manejo seguro del límite inferior (para evitar desbordamiento de size_t)
        if (medio == 0) return lista.size(); 
        return busquedaBinariaPelicula(lista, inicio, medio - 1, claveNormalizada);
    } 
    // Buscar a la derecha
    else { 
        return busquedaBinariaPelicula(lista, medio + 1, fin, claveNormalizada);
    }
}

// Función genérica para resolver ambas tareas
void ejecutarBusqueda(const std::vector<Pelicula>& lista, const std::string& tituloBuscado) {
    std::cout << "\n--- Buscando '" << tituloBuscado << "' (Busqueda Binaria) ---\n";
    
    // 1. Normalizar la clave de búsqueda
    std::string claveNormalizada = toLower(tituloBuscado);

    // 2. Ejecutar Búsqueda Binaria
    size_t n = lista.size();
    size_t indice = busquedaBinariaPelicula(lista, 0, n - 1, claveNormalizada);

    // 3. Mostrar Resultado
    if (indice != n) {
        // Tarea 1: Mostrar información y determinar existencia
        // Tarea 2: Indicar posición
        std::cout << "Exito: La pelicula se encuentra en la lista.\n";
        mostrarInfoPelicula(lista[indice], indice);
    } else {
        std::cout << "Fracaso: '" << tituloBuscado << "' no se encontro en la lista.\n";
        std::cout << "------------------------------------------\n";
    }
}

int main() {
    // --- Datos crudos iniciales ---
    std::vector<std::tuple<std::string, int, double, int>> datosCrudos = {
        {"Pulp Fiction", 1994, 213.9, 5},
        {"Star Wars: A New Hope", 1977, 775.5, 5},
        {"Avengers: Infinity War", 2018, 2048.4, 4}, 
        {"Star Wars: The Return of Jedi", 1983, 475.1, 4}, 
        {"The Dark Knight", 2008, 1004.9, 5},
        {"Avatar", 2009, 2923.7, 3}
    };

    // PASO A: Preprocesar y Normalizar la lista
    std::vector<Pelicula> catalogo;
    for (const auto& tupla : datosCrudos) {
        std::string titulo = std::get<0>(tupla);
        catalogo.push_back({
            titulo,
            toLower(titulo), 
            std::get<1>(tupla),
            std::get<2>(tupla),
            std::get<3>(tupla)
        });
    }

    // PASO B: Ordenar la lista por el título normalizado (Requisito de Búsqueda Binaria)
    std::sort(catalogo.begin(), catalogo.end(), compararPorTituloNormalizado);

    std::cout << "Iniciando procesamiento de la lista de peliculas (BBusqueda Binaria)...\n";
    std::cout << "La lista ha sido ordenada alfabeticamente por titulo para busquedas eficientes.\n";
    
    // --- Ejecución de Tareas ---
    
    // Tarea 1: Determinar si existe "Avengers: Infinity War" y mostrar info.
    const std::string titulo1 = "Avengers: Infinity War";
    ejecutarBusqueda(catalogo, titulo1);

    // Tarea 2: Indicar en qué posición se encuentra "Star Wars: The Return of Jedi".
    const std::string titulo2 = "Star Wars: The Return of Jedi";
    ejecutarBusqueda(catalogo, titulo2);

    // Ejemplo extra para demostrar la insensibilidad a mayúsculas
    ejecutarBusqueda(catalogo, "the dark knight"); 
    ejecutarBusqueda(catalogo, "FNAF 2"); 

    return 0;
}