/*
1) al comenzar el programa se crean N_CENTROS y se insertan en el árbol, tiene ids únicos y listas vacías y localidades diferentes
2) se generan N_VENTAS aleatorias
3) se muestra resumen inicial de árbol creado
4) se distribuyen las ventas a los centros y se muestra un menu de opciones

Menú
1) Insertar un centro
    - se inserta de fomra manual el id y la localidad (se comprueba que id no existe, se añade al árbol con lista de ventas vacía)
    - se informa si id ya existe
2) Borrar un centro 
    - se indica el id del centro que se quiere eliminar, si existe se elimina del arbol, junto con todas las ventas, liberando la memoria dinamica 
    - se informa si no existe
3) Mostrar las ventas de un centro 
    - se introduce id del centro y se muestra su localidad y todas las ventas en su orden de incorporación
    - si no hay ventas, se indica expresamente
    CENTRO 381 - MÓSTOLES
    Venta   Pizza   Categoría    Unidades    Fecha
    ---------------------------------------------
    V21508  NP01    Tradicional         3    12-10-2026
4) Buscar una venta
    - se indica id de venta, si se encuentra se muestran sus datos y el centro perteneciente
    - si no existe, se informa
5) Extraer una venta
    - se indica id de venta, se elimina de la lista del centro 
    - si la venta no existe, no se modifica ?se informa tambien, no?
6) Trasladar una venta a otro centro 
    - se indica id de venta y el id del centro de destino, si ambos existen, la venta pasa al final de la lista de destino, se actualiza su campo id_centro
    - si alguno no existe u origen==destino, se informa de ello 
7) Mostrar estadísticas de los centros 
    - número de ventas registradas y número de pizzas vendidas en cada centro
    - pizza más vendida en total, según la suma de sus unidades
    - centro con más pizzas vendidas
    - si no hay ventas, se indican ceros y se informa de que no es posible determinar elementos con más ventas
8) Generar y distribuir nuevas ventas
    - se generan otras N_VENTAS, se muestran antes de distribuirse
0) Salir del programa
    - se eliminan todas las estructuras de datos utilizadas, liberando la memoria correspondiente
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "napoli.h"

using namespace std;

int main()
{
    srand(time(nullptr));

    int opcion1;
    int contador = 0;
}