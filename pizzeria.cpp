#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "pizzeria.h"

using namespace std;

const int PROB_PERSONALIZACION = 20;

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}
Cola::~Cola()
{
    while (!esVacia())
    {
        desencolar();
    }
}

Nodo::Nodo(Pedido p, Nodo* sig) {
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
    string ceros = "000";
    int copia = contador;
    while(copia >= 10) {
        ceros.pop_back();
        copia /= 10;
    }
    string id = "P1" + ceros + to_string(contador);
    return id; 
}

Pedido generarPedidoAleatorio(int &contadorGlobal) {
    string tipos[] = {"Margarita", "Pepperoni", "Cuatro Quesos", "Hawaiana", "Barbacoa"};
    string tamanos[] = {"Familiar", "Mediana", "Individual"};
    string zonas[] = {"Norte", "Sur", "Centro", "Este", "Oeste"};
    string estados[] = {"En preparacion", "En horno", "Listo"};

    contadorGlobal++; // Incrementamos el contador para el siguiente ID

    Pedido p;
    p.id_pedido = generarIdPedido(contadorGlobal);
    p.id_cliente = calcularSecuenciaAleatoria(999);  // IDs entre 0 y 999
    p.tipo_pizza = tipos[calcularSecuenciaAleatoria(5)];
    p.tamano_pizza = tamanos[calcularSecuenciaAleatoria(3)];
    p.zona_reparto = zonas[calcularSecuenciaAleatoria(5)];
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
    cout << "Pedido   |  Cliente  |       Pizza      |    Tamaño    |   Zona   |   Pers  |       Estado" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;

    pNodo aux = primero;

    while (aux != nullptr) {
        string personalizacion = "No";
        if(aux->pedido.personalizada) {
            personalizacion = "Si";
        }

        cout << setw(7) << aux->pedido.id_pedido << setw(3) << "|"
            << setw(9) << aux->pedido.id_cliente << setw(3) << "|"
            << setw(16) << aux->pedido.tipo_pizza << setw(3) << "|"
            << setw(12) << aux->pedido.tamano_pizza << setw(3) << "|"
            << setw(8) << aux->pedido.zona_reparto << setw(3) << "|"
            << setw(7) << personalizacion << setw(3) << "|"
            << setw(15) << aux->pedido.estado << endl;
        
        aux = aux->siguiente;
    }
}
