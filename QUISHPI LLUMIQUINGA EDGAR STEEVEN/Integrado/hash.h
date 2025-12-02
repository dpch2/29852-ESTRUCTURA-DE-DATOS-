#ifndef HASH_H
#define HASH_H

struct NodoHash {
    char* clave;
    int valor;
    NodoHash* siguiente;
};

class TablaHash {
private:
    static const int TAMANIO = 101;
    NodoHash** tabla;
    
    int funcionHash(const char* clave);
    int contarPalabras(const char* texto, char separador);

public:
    TablaHash();
    ~TablaHash();
    
    void insertar(const char* clave, int valor);
    int buscar(const char* clave);
    void eliminar(const char* clave);
    
    // Ejercicio: Análisis de frecuencia de palabras con resolución de colisiones
    void ejercicio_AnalisisFrecuencia();
};

#endif // HASH_H
