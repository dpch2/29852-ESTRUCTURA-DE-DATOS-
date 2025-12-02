PROGRAMA: Ejercicios de busqueda binaria y tabla hash

Resumen:
- Contiene 4 ejercicios de busqueda binaria y 1 ejercicio de hash.
- Implementacion basada en punteros (no se usan vectores).
- Cada ejercicio imprime resultados, pasos clave y explicacion del por que.

Pasos para compilar (Windows, MinGW):
1) Abrir la terminal en la carpeta del proyecto, por ejemplo:
   cd "d:\\Universidad\\Estructura de datos\\Integrado"
2) Compilar:
   C:\\mingw64\\bin\\g++.exe -fdiagnostics-color=always -g main.cpp busquedaBinaria.cpp hash.cpp -o main.exe
3) Ejecutar:
   .\\main.exe

Que muestra el programa y por que:
- Ejercicio 1 (matriz rotada):
  - Paso clave: se recorre la matriz en forma lineal para localizar el elemento.
  - Por que: la rotacion rompe el orden global que permitiria usar una busqueda binaria 2D directa.

- Ejercicio 2 (frecuencia k):
  - Paso clave: buscar limite izquierdo del objetivo con busqueda binaria y luego contar frecuencia.
  - Por que: aprovecha que el array esta ordenado para reducir comparaciones.

- Ejercicio 3 (pico en array):
  - Paso clave: usar comparaciones con vecinos en la posicion media y moverse hacia el lado que sube.
  - Por que: la existencia de un pico esta garantizada y la estrategia reduce la busqueda a O(log n).

- Ejercicio 4 (cambios de sentido):
  - Paso clave: identificar la monotonia local (lado creciente/decreciente) y descartar la mitad no viable.
  - Por que: conocer el comportamiento local permite eliminar grandes regiones de busqueda.

- Ejercicio Hash (analisis de frecuencia):
  - Paso clave: tokenizar y normalizar palabras, usar tabla hash con encadenamiento para contar frecuencias.
  - Por que: la operacion promedio de busqueda/insert en hash es O(1), ideal para conteo de palabras.

Notas:
- El programa incluye impresiones detalladas de pasos clave y explicaciones, util para entender la logica
  detras de cada solucion.
- Se hicieron cambios para evitar caracteres acentuados en impresiones y comentarios.
