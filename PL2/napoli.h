//centros organizados en árboles binarios de búsqueda
//cada nodo del árbol tiene datos del centro y una lista enlazada con sus ventas
//no se permiten vectores, lists, sets, maps, queues, plantillas...

#ifndef NAPOLI_H
#define NAPOLI_H

#include <string>

using namespace std;

struct Fecha {

};

struct Venta {
    int id_centro;
    string id_venta; //letra V seguida de cinco cifras
    string cod_pizza;
    string categoria; //categoria de la pizza
    int unidades; //entre 1 y 20
    Fecha fecha_venta; //fecha válida en formato DD-MM-2026
};

class NodoV {
private:
    Venta venta;
    NodoV *siguiente;
    NodoV *anterior;
    friend class Lista;
public:
    NodoV(Venta v, NodoV *anterior = nullptr, NodoV *siguiente = nullptr) : venta (v), anterior(anterior), siguiente(siguiente) {}
};

typedef NodoV *pVenta;

class Lista {
private:
    pVenta cabeza;
    pVenta actual;
    pVenta final;
public:
    Lista();
    ~Lista();
    //Lista(const Lista &) = delete;
    //Lista &operator=(const Lista &) = delete;
    void insertar(Venta v); //puede que aquí haga falta otro parámetro, la posición de inserción 
    void eliminar_venta(Venta v); //o se elimina por posición?
    bool esVacia();
    Venta getCabeza();
    Venta getActual();
    Venta getFinal();
};

struct Centro {
    int id_centro; //único, tres cifras
    string localidad; //Móstoles, Alcalá, Leganés, Fuenlabrada, Getafe, Alcorcón. Torrejón, Parla, Alcobendas, Coslada, Pozuelo, Rivas, Valdemoro, Majadahonda, Aranjuez, Arganda, Boadilla, Pinto, Colmenar, Tres Cantos
    Lista lista_ventas; //lista enlazada
};

//cambiar, porque tiene que ser un nodo de árbol, no lista
class NodoC {
private:
    Centro centro;
    NodoC *siguiente;
    NodoC *anterior;
    friend class Arbol;
public:
    //MEMORIA: aquí hubo un problema con pasar el centro al constructor del Nodo, ya que centro usa listas y listas no permite copias...
    //DUDA: dos soluciones: permito copias o creo el centro ya aqui, pasandole al nodo int id y localidad, asignando los valores dentro, así: centro.id_centro = id; 
    NodoC(Centro c, NodoC *anterior = nullptr, NodoC *siguiente = nullptr) : centro (c), anterior(anterior), siguiente(siguiente) {}
};

class Arbol {
    
};

int calcularSecuenciaAleatoria(int x);
int generarIdCentro(int contador);
string generarIdVenta();
Centro generarCentro();
Venta generarVenta();

/*
Catálogo de pizzas:
Código  Pizza           Categoría
------------------------------------
NP01    Margarita       Tradicional
NP02    Marinara        Tradicional 
NP03    Barbacoa        Carne
NP04    Pollo BBQ       Carne
NP05    Vegetal         Verduras
NP06    Espinacas       Verduras
NP07    Cuatro quesos   Quesos
NP08    Gorgonzola      Quesos
*/

#endif