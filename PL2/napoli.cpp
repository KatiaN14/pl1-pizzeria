#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#include "napoli.h"

using namespace std;

#define N_CENTROS 10;
#define N_VENTAS 30;

Lista::~Lista() {
    pVenta aux;
    esCabeza();
    while (cabeza) {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    //DUDA: la diferencia entre NULL y nullptr? NULL puede ser un entero, cual es mejor usar?
    cabeza=NULL;
    actual = nullptr;
    final = nullptr;
}

void Lista::insertar(Venta v, char c) {
    pVenta aux;
    char tipoInsercion;
    tipoInsercion = c;

    if(esVacia()) {
        aux = new NodoV(v, NULL, NULL);
        final=cabeza=aux;
    }
    //inserción por el final
    else if (tipoInsercion=='f'){
        aux = new NodoV(v, NULL, NULL);
        aux->anterior = final;
        final->siguiente = aux;
        final = aux;
    }
    //inserción por el principio
    else if (tipoInsercion=='p'){
        aux = new NodoV(v, NULL, NULL);
        aux->siguiente=cabeza;
        cabeza->anterior=aux;
        cabeza=aux;
    }
    //y que pasa con insercion en el medio? hace falta?
}

void Lista::eliminar_venta(Venta v) {
    bool eliminado = false;
    pVenta aux;
    esCabeza();
    aux = cabeza;
    //si la venta buscada está en la cabeza
    if(aux->venta.id_venta == v.id_venta){
        cabeza = cabeza->siguiente;
        aux->siguiente=NULL;
        cabeza->anterior=NULL;
        cout << "Venta con id " << aux->venta.id_venta << " ha sido eliminada" << endl;
        eliminado = true;
        delete aux;
    }else{
        while(aux){
            if (aux->venta.id_venta == v.id_venta) {
                if(aux==final){
                    final = final->anterior;
                    aux->anterior=NULL;
                    final->siguiente=NULL;
                    cout << "Venta con id " << aux->venta.id_venta << " ha sido eliminada" << endl;
                    eliminado = true;
                    delete aux;
                }
                aux->anterior->siguiente = aux->siguiente;
                aux->siguiente->anterior = aux->anterior;
                aux->anterior=NULL;
                aux->siguiente=NULL;
                cout << "Venta con id " << aux->venta.id_venta << " ha sido eliminada" << endl;
                eliminado = true;
                delete aux;
            }
        }
    }
    if(!eliminado){
        cout << "La venta no ha sido encontrada y no se ha podido eliminar" << endl;
    }  
}

bool Lista::esVacia(){
    return (cabeza == nullptr) && (final == nullptr); //DUDA: no hace falta verificar el actual, verdad? incluso con solo cabeza o final basta, verdad?
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
    Lista l = Lista();

    Centro c;
    c.id_centro = generarIdCentro();
    c.localidad = localidades[calcularSecuenciaAleatoria(20)];
    //puntero a lista: c.lista_ventas = *l;
}

Venta generarVenta();

Arbol::~Arbol(){
    Podar(raiz);
}

bool Arbol::esVacio(NodoC *r){
    return r==NULL;
}

bool Arbol::esHoja(NodoC *r){
    
}