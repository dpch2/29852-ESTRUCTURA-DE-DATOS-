#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <iomanip>   
#include <cctype>

// Definición de la estructura de datos para un Pokémon
struct Pokemon {
    std::string nombreOriginal; // Mantiene el nombre exacto para la salida
    std::string nombreNormalizado; // Nombre en minúsculas para la búsqueda
    int numero;
    std::string tipoPrincipal;
};

// ----------------------------------------------------
// FUNCIÓN AUXILIAR: Normaliza una cadena a minúsculas
// ----------------------------------------------------
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    // std::transform aplica una función (::tolower) a cada caracter de la cadena
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

// ----------------------------------------------------
// 1. FUNCIÓN DE COMPARACIÓN PARA EL ORDENAMIENTO
// ----------------------------------------------------
// Compara usando el nombre normalizado (en minúsculas).
bool compararPorNombreNormalizado(const Pokemon& a, const Pokemon& b) {
    return a.nombreNormalizado < b.nombreNormalizado;
}

int busquedaBinariaPokemon(const std::vector<Pokemon>& lista, int inicio, int fin, const std::string& claveNormalizada) {
    if (inicio > fin) {
        return -1;
    }

    int medio = inicio + (fin - inicio) / 2;
    const std::string& nombreMedioNormalizado = lista[medio].nombreNormalizado;

    if (nombreMedioNormalizado == claveNormalizada) {
        return medio;
    } 
    else if (claveNormalizada < nombreMedioNormalizado) {
        return busquedaBinariaPokemon(lista, inicio, medio - 1, claveNormalizada);
    } 
    else {
        return busquedaBinariaPokemon(lista, medio + 1, fin, claveNormalizada);
    }
}

// ----------------------------------------------------
// 3. FUNCIÓN PRINCIPAL DE PRESENTACIÓN DE DATOS
// ----------------------------------------------------
void mostrarInfoPokemon(const Pokemon& p) {
    std::cout << "\nPokemon Encontrado!\n";
    std::cout << "-----------------------\n";
    // Mostramos el nombre original (con mayúsculas/minúsculas correctas)
    std::cout << std::left << std::setw(15) << "Nombre:" << p.nombreOriginal << std::endl; 
    std::cout << std::left << std::setw(15) << "NNumero (Pokedex):" << p.numero << std::endl;
    std::cout << std::left << std::setw(15) << "Tipo Principal:" << p.tipoPrincipal << std::endl;
    std::cout << "-----------------------\n";
}

int main() {
    // --- Datos iniciales (Solo nombre original, número y tipo) ---
    std::vector<std::tuple<std::string, int, std::string>> datosCrudos = {
        {"Pikachu", 25, "Electrico"},
        {"Bulbasaur", 1, "Planta"},
        {"Groudon", 383, "Tierra"},
        {"Cobalion", 638, "Acero"}, 
        {"Mewtwo", 150, "Psiquico"},
        {"Reshiram", 643, "Dragon"},
        {"Zekrom", 644, "Dragon"},
        {"Eevee", 133, "Normal"},
        {"Snorlax", 143, "Normal"},
        {"Charmander", 4, "Fuego"},
        {"Squirtle", 7, "Agua"}
    };

    // PASO 1: Preprocesar la lista para crear objetos Pokemon con nombres normalizados
    std::vector<Pokemon> pokedex;
    for (const auto& tupla : datosCrudos) {
        std::string nombreOriginal = std::get<0>(tupla);
        pokedex.push_back({
            nombreOriginal,
            toLower(nombreOriginal), // Normalizamos el nombre aquí
            std::get<1>(tupla),
            std::get<2>(tupla)
        });
    }

    // PASO 2: Ordenar la lista usando el nombre normalizado (en minúsculas)
    std::sort(pokedex.begin(), pokedex.end(), compararPorNombreNormalizado);
    
    // --- MENSAJE DE INICIO ---
    std::cout << "--- Busqueda de Pokemon ---\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << "Pokemon disponibles en la lista:\n";
    std::cout << "  ";
    // Mostramos los nombres originales de la lista de datos crudos
    for (size_t i = 0; i < datosCrudos.size(); ++i) {
        std::cout << std::get<0>(datosCrudos[i]) << (i < datosCrudos.size() - 1 ? ", " : "");
    }
    std::cout << "\n----------------------------------------------------------\n";

    // PASO 3: Solicitar el nombre al usuario
    std::string nombreBuscadoUsuario;
    std::cout << "Ingrese el nombre del Pokemon que desea buscar: ";
    std::getline(std::cin, nombreBuscadoUsuario); 

    // PASO 4: Normalizar la clave del usuario para la búsqueda
    std::string claveNormalizada = toLower(nombreBuscadoUsuario);
    
    // PASO 5: Ejecutar la Búsqueda Binaria Recursiva
    int n = pokedex.size();
    int indice = busquedaBinariaPokemon(pokedex, 0, n - 1, claveNormalizada);

    // PASO 6: Mostrar el resultado
    if (indice != -1) {
        mostrarInfoPokemon(pokedex[indice]);
    } else {
        std::cout << "\nPokemon no encontrado. '" << nombreBuscadoUsuario << "' no esta en la Pokedex.\n";
    }

    return 0;
}
