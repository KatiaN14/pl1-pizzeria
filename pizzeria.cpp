#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
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

/*string generarIdPedido(string contador) {
    string numeroString = contadorTexto.substr(1,5); //en realida contadorTexto es lo que recibirá, porque el contador no es un int, empieza por una P, pero otra funcion lo esta usando ahora como un int, por ahora se deja asi 
    int numero = stoi(numeroString);
    numero = numero + 1;
    contador = to_string(numero);
    contador = 'P' + contador;
    return contador;
    
}*/

//generarIdPedido provisional
string generarIdPedido(int contador) {
    string contadorStr = to_string(contador);
    string numeroString = (contador < 10 ? "P000" : (contador < 100 ? "P00" : "P0")) + contadorStr;
    return numeroString; 
}

Pedido generarPedidoAleatorio(int &contadorGlobal) {
    string tipos[] = {"Margarita", "Pepperoni", "Cuatro Quesos", "Hawaiana", "Barbacoa"};
    string tamanos[] = {"Familiar", "Mediana", "Individual"};
    string zonas[] = {"Norte", "Sur", "Centro", "Este", "Oeste"};
    string estados[] = {"En preparacion", "En horno", "Listo"};
    bool personalizadas[5] = {false, false, false, false, true};

    contadorGlobal++; // Incrementamos el contador para el siguiente ID
    Pedido p;
    p.id_pedido = generarIdPedido(contadorGlobal);
    p.id_cliente = 100 + calcularSecuenciaAleatoria(900);  // IDs entre 0 y 999
    p.tipo_pizza = tipos[calcularSecuenciaAleatoria(5)];
    p.tamano_pizza = tamanos[calcularSecuenciaAleatoria(3)];
    p.zona_reparto = zonas[calcularSecuenciaAleatoria(5)];
    p.personalizada = personalizadas[calcularSecuenciaAleatoria(5)];
    p.estado = estados[calcularSecuenciaAleatoria(3)];

    return p;
}

/*
arrays pizza estado etc

int calcularSecuenciaAleatoria(int x)
{
    int numaleat;
    numaleat = rand() % x;

    return numaleat;
}
 */

void mostrarPedidosRecibidos() {
    cout << "=== RECIBIDOS ===" << endl;
    cout << "Pedido \t | \t Cliente \t | \t Pizza \t | \t Tamaño \t | \t Zona \t | \t Pers \t | \t Estado" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
}
