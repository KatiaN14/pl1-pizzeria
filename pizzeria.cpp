#include <iostream>
#include <string>
#include "pizzeria.h"

using namespace std;

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}
Cola::~Cola()
{
    while (!esVacia())
    {
        desencolar();
    }
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

//prueba
