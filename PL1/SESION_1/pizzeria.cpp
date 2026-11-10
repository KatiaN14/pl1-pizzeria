#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "pizzeria.h"

using namespace std;

#define PROB_PERSONALIZACION 20
/*
 * He puesto PROB_PERSONALIZACION como lo pone en el doc de la sesión 1 para seguir la praxis del profe
 */

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}
Cola::~Cola()
{
    while (!esVacia())
    {
        desencolar();
    }
}

Nodo_Cola::Nodo_Cola(Pedido p, Nodo_Cola* sig) {
    pedido = p;
    siguiente = sig;
}

void Cola::encolar (Pedido p)
{
    pNodo nuevo;
    nuevo = new Nodo_Cola (p);
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

Pedido Cola::valorFrente()
{
    if (primero == nullptr)
    {
        cout << "Error: Cola vacia al consultar el frente." << endl;
        Pedido vacio = {"", 0, "", "", "", false, ""};
        return vacio;
    }

    return primero->pedido;
}

bool Cola::esVacia()
{
    return primero == nullptr;
}

int calcularSecuenciaAleatoria(int x)
{
    int numaleat;
    numaleat = rand() % x;

    return numaleat;
}

string generarIdPedido(int contador) {
    string id = "P" + to_string(10000 + contador);
    return id;
}

Pedido generarPedidoAleatorio(int &contadorGlobal) {
    string tipos[] = {"Margarita", "Barbacoa", "Vegetal", "Cuatro Quesos", "Hawaiana", "Romana"};
    string tamanos[] = {"Mediana", "Grande"};
    string zonas[] = {"Norte", "Sur", "Este", "Oeste"};

    contadorGlobal ++;

    Pedido p;
    p.id_pedido = generarIdPedido(contadorGlobal);
    p.id_cliente = 100 + calcularSecuenciaAleatoria(900);  // IDs entre 100 y 999
    p.tipo_pizza = tipos[calcularSecuenciaAleatoria(6)];
    p.tamano = tamanos[calcularSecuenciaAleatoria(2)];
    p.zona_reparto = zonas[calcularSecuenciaAleatoria(4)];
    p.personalizada = (calcularSecuenciaAleatoria(100) < PROB_PERSONALIZACION);
    p.estado = "Recibido"; //estados[calcularSecuenciaAleatoria(3)]; en la PL1 el estado es por defecto "recibido"

    return p;
}

void Cola::mostrarCola() {
    if (esVacia()) {
        cout << "La cola de pedidos está vacía." << endl;
        return;
    }
    cout << "=== RECIBIDOS ===" << endl;
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
    pNodo aux = primero;

    while (aux != nullptr) {
        string personalizacion = "No";
        if(aux->pedido.personalizada) {
            personalizacion = "Si";
        }

        cout << setw(7) << aux->pedido.id_pedido << setw(3) << "|"
            << setw(9) << aux->pedido.id_cliente << setw(3) << "|"
            << setw(16) << aux->pedido.tipo_pizza << setw(3) << "|"
            << setw(12) << aux->pedido.tamano << setw(3) << "|"
            << setw(8) << aux->pedido.zona_reparto << setw(3) << "|"
            << setw(7) << personalizacion << setw(3) << "|"
            << setw(15) << aux->pedido.estado << endl;

        aux = aux->siguiente;
    }
}