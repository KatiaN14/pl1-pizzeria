#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "pizzeria2.h"

using namespace std;

#define PROB_PERSONALIZACION 20

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}
Cola::~Cola()
{
    while (!esVacia())
    {
        desencolar();
    }
}

Nodo::Nodo(Pedido p, Nodo *sig) {
    pedido = p;
    siguiente = sig;
}

void Cola::encolar (Pedido p)
{
    pNodo nuevo;
    nuevo = new Nodo (p);
    if (ultimo != nullptr) ultimo->siguiente = nuevo;
    ultimo = nuevo;
    if (primero == nullptr) primero = nuevo;
}

void Cola::desencolar()
{
    if (primero == nullptr) return;
    pNodo aux;
    aux = primero;
    primero = primero->siguiente;
    delete aux;
    if (primero == nullptr) ultimo = nullptr;
}

Pedido Cola::valorFrente() {
    if (esVacia()) {
        Pedido vacio = {"", 0, "", "", "", false, ""};
        return vacio;
    }
    return primero->pedido;
}

bool Cola::esVacia()
{
    return primero == nullptr;
}

int calcularSecuenciaAleatoria(int x) {
    int numaleat;
    numaleat = rand() % x;

    return numaleat;
}

/*
 * He cambiado la función a una más sencilla e igual de funcional con complejidad O(1)
 * porque es una mejor praxis, borrando lineas de código innecesarias.
 */
string generarIdPedido(int contador) {
    string id = "P" + to_string(10000 + contador);
    return id;
}

Pedido generarPedidoAleatorio(int &contadorGlobal) {
    string tipos[6] = {"Margarita", "Barbacoa", "Vegetal", "Hawaiana", "Romana", "Cuatro quesos"};
    string tamanos[2] = {"Mediana", "Grande"};
    string zonas[ZONAS] = {"Norte", "Sur", "Este", "Oeste"};

    contadorGlobal ++;

    Pedido p;
    p.id_pedido = generarIdPedido(contadorGlobal);
    p.id_cliente = 100 + calcularSecuenciaAleatoria(900);
    p.tipo_pizza = tipos[calcularSecuenciaAleatoria(6)];
    p.tamano = tamanos[calcularSecuenciaAleatoria(2)];
    p.zona_reparto = zonas[calcularSecuenciaAleatoria(ZONAS)];
    p.personalizada = (calcularSecuenciaAleatoria(100) < PROB_PERSONALIZACION);

    return p;
}

void Cola::mostrarCola(string nombreCola) {
    if (esVacia()) {
        cout << "\n[Aviso] La cola " << nombreCola << " esta vacia.\n" << endl;
        return;
    }

    pNodo actual = primero;
    cout << "\n=== " << nombreCola << " ===" << endl;
    /*
     * Aquí el cambio que he hecho es poner en vez de recibidos, el estado en el que esté en ese momento
     */
    cout << left << setw(10) << "Pedido"
         << setw(10) << "Cliente"
         << setw(15) << "Pizza"
         << setw(10) << "Tamano"
         << setw(10) << "Zona"
         << setw(8)  << "Pers"
         << setw(15) << "Estado" << endl;
    cout << setfill('-') << setw(86) << "-" << setfill(' ') << endl;
    /*
     * He implementado código que he visto en geeksforgeeks que parece más limpio para
     * tener una cabecera con una alineación a la izquierda y anchos fijos con set width
     */

    while (actual != nullptr) {
        cout << left << setw(10) << actual->pedido.id_pedido
             << setw(10) << actual->pedido.id_cliente
             << setw(15) << actual->pedido.tipo_pizza
             << setw(10) << actual->pedido.tamano
             << setw(10) << actual->pedido.zona_reparto
             << setw(8)  << (actual->pedido.personalizada ? "Si" : "No")
             << setw(15) << actual->pedido.estado << endl;
        actual = actual->siguiente;
    }
    cout << endl;
}