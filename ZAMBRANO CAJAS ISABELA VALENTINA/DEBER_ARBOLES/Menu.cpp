#include "Menu.hpp"

Menu::Menu() {
    opcionSeleccionada = 0;
    tipoArbol = 0;
}

void Menu::limpiarPantalla() {
    system("cls");
}

void Menu::pausar() {
    std::cout << "\nPresione cualquier tecla para continuar..." << std::endl;
    _getch();
}

void Menu::seleccionarTipoArbol() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|        SELECCIONE TIPO DE ARBOL           |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    int opcion = 0;
    bool seleccionado = false;
    
    while(!seleccionado) {
        limpiarPantalla();
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "|        SELECCIONE TIPO DE ARBOL           |" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << std::endl;
        
        const char* tipos[] = {
            "1. Arbol Binario de Busqueda (ABB)",
            "2. Arbol AVL (Auto-equilibrado)",
            "3. Salir"
        };
        
        for(int i = 0; i < 3; i++) {
            if(i == opcion) {
                std::cout << ">> " << tipos[i] << " <<" << std::endl;
            } else {
                std::cout << "   " << tipos[i] << std::endl;
            }
        }
        
        std::cout << std::endl << "Use FLECHAS para navegar, ENTER para seleccionar" << std::endl;
        
        int tecla = _getch();
        
        if(tecla == 224) {
            tecla = _getch();
            if(tecla == 72) {
                opcion = (opcion - 1 + 3) % 3;
            } else if(tecla == 80) {
                opcion = (opcion + 1) % 3;
            }
        } else if(tecla == 13) {
            seleccionado = true;
            if(opcion == 0) {
                tipoArbol = 1;
            } else if(opcion == 1) {
                tipoArbol = 2;
            } else {
                exit(0);
            }
        }
    }
}

void Menu::mostrarMenuPrincipal() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    if(tipoArbol == 1) {
        std::cout << "|  ARBOL BINARIO DE BUSQUEDA (ABB)         |" << std::endl;
    } else {
        std::cout << "|  ARBOL AVL (AUTO-EQUILIBRADO)            |" << std::endl;
    }
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    const char* opciones[] = {
        "1. Insertar datos",
        "2. Buscar dato",
        "3. Eliminar dato",
        "4. Ver recorridos",
        "5. Ver arbol (visual)",
        "6. Cambiar tipo de arbol",
        "7. Salir"
    };
    
    for(int i = 0; i < 7; i++) {
        if(i == opcionSeleccionada) {
            std::cout << ">> " << opciones[i] << " <<" << std::endl;
        } else {
            std::cout << "   " << opciones[i] << std::endl;
        }
    }
    
    std::cout << std::endl << "Use FLECHAS para navegar, ENTER para seleccionar" << std::endl;
}

void Menu::ingresarDatos() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|           INSERTAR DATOS AL ARBOL         |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    int cantidad;
    std::cout << "¿Cuantos datos desea ingresar? ";
    std::cin >> cantidad;
    std::cout << std::endl;
    
    for(int i = 0; i < cantidad; i++) {
        int dato;
        std::cout << "Ingrese el dato " << (i + 1) << ": ";
        std::cin >> dato;
        
        if(tipoArbol == 1) {
            arbolABB.insertarNodo(dato);
        } else {
            arbolAVL.insertarNodo(dato);
        }
    }
    
    std::cout << std::endl << "Datos insertados correctamente" << std::endl;
    pausar();
}

void Menu::buscarDato() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|             BUSCAR DATO EN EL ARBOL       |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    int dato;
    std::cout << "Ingrese el dato a buscar: ";
    std::cin >> dato;
    std::cout << std::endl;
    
    bool encontrado = false;
    if(tipoArbol == 1) {
        encontrado = arbolABB.buscar(dato);
    } else {
        encontrado = arbolAVL.buscar(dato);
    }
    
    if(encontrado) {
        std::cout << "El valor " << dato << " SE ENCUENTRA en el arbol" << std::endl;
    } else {
        std::cout << "El valor " << dato << " NO se encuentra en el arbol" << std::endl;
    }
    
    pausar();
}

void Menu::eliminarDato() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|            ELIMINAR DATO DEL ARBOL        |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    int dato;
    std::cout << "Ingrese el dato a eliminar: ";
    std::cin >> dato;
    std::cout << std::endl;
    
    if(tipoArbol == 1) {
        arbolABB.eliminarNodo(dato);
    } else {
        arbolAVL.eliminarNodo(dato);
    }
    
    std::cout << std::endl << "Operacion completada" << std::endl;
    pausar();
}

void Menu::mostrarRecorridoMenu() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|         SELECCIONE TIPO DE RECORRIDO      |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    int opcion = 0;
    bool seleccionado = false;
    
    while(!seleccionado) {
        limpiarPantalla();
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "|         SELECCIONE TIPO DE RECORRIDO      |" << std::endl;
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << std::endl;
        
        const char* tipos[] = {
            "1. Inorden (Izquierda - Raiz - Derecha)",
            "2. Preorden (Raiz - Izquierda - Derecha)",
            "3. Postorden (Izquierda - Derecha - Raiz)",
            "4. Volver"
        };
        
        for(int i = 0; i < 4; i++) {
            if(i == opcion) {
                std::cout << ">> " << tipos[i] << " <<" << std::endl;
            } else {
                std::cout << "   " << tipos[i] << std::endl;
            }
        }
        
        std::cout << std::endl << "Use FLECHAS para navegar, ENTER para seleccionar" << std::endl;
        
        int tecla = _getch();
        
        if(tecla == 224) {
            tecla = _getch();
            if(tecla == 72) {
                opcion = (opcion - 1 + 4) % 4;
            } else if(tecla == 80) {
                opcion = (opcion + 1) % 4;
            }
        } else if(tecla == 13) {
            seleccionado = true;
            
            limpiarPantalla();
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "|              RESULTADO DEL RECORRIDO      |" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << std::endl;
            
            Nodo<int>* raiz = nullptr;
            if(tipoArbol == 1) {
                raiz = arbolABB.getRaiz();
            } else {
                raiz = arbolAVL.getRaiz();
            }
            
            if(raiz == nullptr) {
                std::cout << "El arbol está vacio" << std::endl;
            } else {
                switch(opcion) {
                    case 0:
                        std::cout << "Recorrido Inorden: ";
                        if(tipoArbol == 1) {
                            arbolABB.inorden(raiz);
                        } else {
                            arbolAVL.inorden(raiz);
                        }
                        std::cout << std::endl;
                        break;
                    case 1:
                        std::cout << "Recorrido Preorden: ";
                        if(tipoArbol == 1) {
                            arbolABB.preorden(raiz);
                        } else {
                            arbolAVL.preorden(raiz);
                        }
                        std::cout << std::endl;
                        break;
                    case 2:
                        std::cout << "Recorrido Postorden: ";
                        if(tipoArbol == 1) {
                            arbolABB.postorden(raiz);
                        } else {
                            arbolAVL.postorden(raiz);
                        }
                        std::cout << std::endl;
                        break;
                    case 3:
                        return;
                }
            }
            pausar();
        }
    }
}

void Menu::mostrarRecorridos() {
    mostrarRecorridoMenu();
}

void Menu::ejecutarOpcion(int opcion) {
    switch(opcion) {
        case 0:
            ingresarDatos();
            break;
        case 1:
            buscarDato();
            break;
        case 2:
            eliminarDato();
            break;
        case 3:
            mostrarRecorridos();
            break;
        case 4:
            mostrarArbol();
            break;
        case 5:
            seleccionarTipoArbol();
            opcionSeleccionada = 0;
            break;
        case 6:
            limpiarPantalla();
            std::cout << "--------------------------------------------" << std::endl;
            std::cout << "|          ¡Hasta luego! Programa finalizado|" << std::endl;
            std::cout << "--------------------------------------------" << std::endl;
            exit(0);
    }
}

void Menu::iniciar() {
    seleccionarTipoArbol();
    
    bool continuar = true;
    
    while(continuar) {
        mostrarMenuPrincipal();
        
        int tecla = _getch();
        
        if(tecla == 224) {
            tecla = _getch();
            if(tecla == 72) {
                opcionSeleccionada = (opcionSeleccionada - 1 + 7) % 7;
            } else if(tecla == 80) {
                opcionSeleccionada = (opcionSeleccionada + 1) % 7;
            }
        } else if(tecla == 13) {
            ejecutarOpcion(opcionSeleccionada);
        }
    }
}

int Menu::calcularAltura(Nodo<int>* nodo) {
    if(nodo == nullptr) {
        return 0;
    }
    
    int alturaIzq = calcularAltura(nodo->getIzquierda());
    int alturaDer = calcularAltura(nodo->getDerecha());
    
    return 1 + (alturaIzq > alturaDer ? alturaIzq : alturaDer);
}

void Menu::dibujarArbol(Nodo<int>* nodo, int espacio, int altura) {
    if(nodo == nullptr) {
        return;
    }
    
    espacio += altura;
    
    dibujarArbol(nodo->getDerecha(), espacio, altura);
    
    std::cout << std::endl;
    for(int i = altura; i < espacio; i++) {
        std::cout << " ";
    }
    std::cout << nodo->getDato();
    
    dibujarArbol(nodo->getIzquierda(), espacio, altura);
}

void Menu::mostrarArbol() {
    limpiarPantalla();
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "|              VISUALIZAR ARBOL             |" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << std::endl;
    
    Nodo<int>* raiz = nullptr;
    if(tipoArbol == 1) {
        raiz = arbolABB.getRaiz();
    } else {
        raiz = arbolAVL.getRaiz();
    }
    
    if(raiz == nullptr) {
        std::cout << "El arbol esta vacio" << std::endl;
    } else {
        int altura = calcularAltura(raiz);
        std::cout << "Altura del arbol: " << altura << std::endl;
        std::cout << std::endl;
        std::cout << "Representación visual del arbol:" << std::endl;
        std::cout << std::endl;
        
        dibujarArbol(raiz, 0, 4);
        
        std::cout << std::endl << std::endl;
        std::cout << "Estadisticas del arbol:" << std::endl;
        std::cout << "- Altura: " << altura << std::endl;
    }
    
    pausar();
}