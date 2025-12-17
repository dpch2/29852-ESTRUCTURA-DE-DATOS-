#include "./Nodo/ArbolBMas.cpp"
#include <iostream>

int main(void){
    std::cout << "=== Demo Arbol B+ ===" << std::endl;

    // Instanciamos el arbol con orden 3 para forzar divisiones (splits) con pocos datos
    ArbolBMas<int> arbol(3);

    // Insertamos datos
    int datos[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(datos)/sizeof(datos[0]);

    for(int i = 0; i < n; i++){
        std::cout << "Insertando: " << datos[i] << std::endl;
        arbol.insertar(datos[i]);
    }

    std::cout << "\nEstructura final (Hojas enlazadas):" << std::endl;
    arbol.imprimir();

    // Pruebas de busqueda
    std::cout << "\nPruebas de busqueda:" << std::endl;
    int buscar[] = {6, 15, 30, 100};
    for(int val : buscar){
        std::cout << "Buscando " << val << ": " << (arbol.buscar(val) ? "Encontrado" : "No encontrado") << std::endl;
    }

    return 0;
}