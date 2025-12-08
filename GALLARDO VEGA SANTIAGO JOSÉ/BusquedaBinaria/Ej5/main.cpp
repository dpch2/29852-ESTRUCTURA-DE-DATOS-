#include "Personajes.hpp"
#include "IO.hpp"
#include "sort.hpp"
#include "busqueda.hpp"

int main(void){
    
    int size=ingresarDatoTeclado<int>("Ingrese el tamanio de la lista");
    Personaje* arrayPersonajes=crearMatriz<Personaje>(size);
    for(int i =0;i<size;i++){
        arrayPersonajes[i]=Personaje(ingresarDatoTeclado<string>("Ingrese el Nombre"),
                            i+1);
    }
    
    std::cout << "\n=== ARREGLO ORIGINAL ===" << std::endl;
    for(int i =0;i<size;i++){
        arrayPersonajes[i].imprimirPersonaje();
    }
    
    // Crear un array de punteros a Personaje
    Personaje** arrayReferencias = new Personaje*[size];
    for(int i = 0; i < size; i++){
        arrayReferencias[i] = &arrayPersonajes[i];
    }

    // Ordenar el array de punteros alfabéticamente por nombre
    Sort::bubbleSort(arrayReferencias, size);

    std::cout << "\n=== ARREGLO ORDENADO ALFABETICAMENTE POR NOMBRE ===" << std::endl;
    for(int i = 0; i < size; i++){
        arrayReferencias[i]->imprimirPersonaje();
    }
    int indice=Busqueda::busquedaNombre(arrayReferencias,ingresarDatoTeclado<string>("Ingrese el nombre a buscar"),size);
    cout<<"El indice buscado está en: "<<indice;
    // Liberar la memoria de ambos arrays
    delete[] arrayReferencias;
    delete[] arrayPersonajes;
    
    return 0;
}