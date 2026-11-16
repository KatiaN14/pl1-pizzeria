#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#include "napoli.h"

using namespace std;

#define N_CENTROS 10;
#define N_VENTAS 30;

Lista::Lista() : cabeza(nullptr), actual(nullptr), final(nullptr) {}

Lista::~Lista() {
    pVenta aux;
    while (cabeza != nullptr) {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    actual = nullptr;
    final = nullptr;
}

void Lista::insertar(Venta v) {
    //crear nuevo nodo venta
    //insertar en la posicion actual, viendo si hay que modificar los punteros cabeza y/o final
}

void Lista::eliminar_venta(Venta v) {
    //mirar si la lista esta vacia
    //usar nodo aux y eliminar la venta, dependiendo de la posicion actual modificar cabeza y/o final
}

bool Lista::esVacia(){
    return (cabeza == nullptr) && (final == nullptr); //no hace falta verificar el actual, verdad?
}

Venta Lista::getCabeza() {
    if(esVacia()){
        throw runtime_error("Lista vacía");
    }
    return cabeza->venta;
}

Venta Lista::getActual() {
    if(esVacia()){
        throw runtime_error("Lista vacía");
    }
    return actual->venta;
}

Venta Lista::getFinal() {
    if(esVacia()){
        throw runtime_error("Lista vacía");
    }
    return final->venta;
}

int calcularSecuenciaAleatoria(int x) {
    return rand() % x;
}

int generarIdCentro() {
    int num = calcularSecuenciaAleatoria(999);
    //recorrer arbol y verificar que el id no existe ya
    return num;
}

string generarIdVenta(int contador) {
    return "V"+to_string(10000 + contador);
}
//DUDA: no se pueden utilizar contadores globales para las estadisticas, pero se puede para el id de venta?

Centro generarCentro() {
    string localidades[20] = {"Móstoles", "Alcalá", "Leganés", "Fuenlabrada", "Getafe", "Alcorcón", "Torrejón", "Parla", "Alcobendas", "Coslada", "Pozuelo", "Rivas", "Valdemoro", "Majadahonda", "Aranjuez", "Arganda", "Boadilla", "Pinto", "Colmenar", "Tres Cantos"};
    
    Centro c;
    c.id_centro = generarIdCentro();
    c.localidad = localidades[calcularSecuenciaAleatoria(20)];
    c.lista_ventas = Lista();
}

Venta generarVenta();