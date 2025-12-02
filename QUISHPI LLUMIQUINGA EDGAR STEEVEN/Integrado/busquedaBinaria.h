#ifndef BUSQUEDABINARIA_H
#define BUSQUEDABINARIA_H

class BusquedaBinaria {
private:
    int tamanio;
    int* datos;
    
    // Función auxiliar para busqueda binaria
    int busquedaBinariaAux(int* arr, int izq, int der, int objetivo);

public:
    BusquedaBinaria();
    ~BusquedaBinaria();
    
    // Ejercicio 1: Encontrar elemento en matriz rotada
    void ejercicio1_MatrizRotada();
    
    // Ejercicio 2: Buscar en rango con frecuencia mínima
    void ejercicio2_BuscarConFrecuencia();
    
    // Ejercicio 3: Encontrar pico en array
    void ejercicio3_EncontrarPico();
    
    // Ejercicio 4: Búsqueda en array con cambios de sentido
    void ejercicio4_CambiosSentido();
};

#endif // BUSQUEDABINARIA_H
