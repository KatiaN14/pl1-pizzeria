#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "pizzeria2.h"

using namespace std;

#define PROB_PERSONALIZACION 20
#define N_PEDIDOS_PASO 10

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

//pero por ejemplo el pedido numero 150 tendra Id P10000150 en vez de P100150...
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
    p.estado = "Recibido";

    return p;
}

void Cola::mostrarCola(string nombreCola) {
    if (esVacia()) {
        cout << "\n[Aviso] La cola " << nombreCola << " esta vacia.\n" << endl;
        return;
    }

    cout << "\n=== " << nombreCola << " ===" << endl;
    cout << "Pedido   |  Cliente  |       Pizza      |    Tamaño    |   Zona   |   Pers  |       Estado" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;

    pNodo aux = primero;

    while (aux != nullptr) {
        cout << setw(7) << aux->pedido.id_pedido << setw(3) << "|"
            << setw(9) << aux->pedido.id_cliente << setw(3) << "|"
            << setw(16) << aux->pedido.tipo_pizza << setw(3) << "|"
            << setw(12) << aux->pedido.tamano << setw(3) << "|"
            << setw(8) << aux->pedido.zona_reparto << setw(3) << "|"
            << setw(7) << (aux->pedido.personalizada ? "Si" : "No") << setw(3) << "|"
            << setw(15) << aux->pedido.estado << endl;

        aux = aux->siguiente;
    }
}




int Cola::contarElementos() {
    int contador = 0;
    pNodo aux = primero;
    while(aux != nullptr) {
        contador++;
        aux = aux -> siguiente;
    }
    return contador;
}

void ejecutarPasos(Cola &recibidos, Cola &preparacionEspecial, Cola &cocina, Cola &expedicionNorte, Cola &expedicionSur, Cola &expedicionEste, Cola &expedicionOeste) {
    int pasosCocina = cocina.contarElementos();
    if (pasosCocina > N_PEDIDOS_PASO) {
        pasosCocina = N_PEDIDOS_PASO;
    }
    for(int i = 0; i < pasosCocina; i++) {
        Pedido p = cocina.valorFrente();
        cocina.desencolar();
        if (p.zona_reparto == "Norte") {
            expedicionNorte.encolar(p);
        } else if (p.zona_reparto == "Sur") {
            expedicionSur.encolar(p);
        } else if (p.zona_reparto == "Este") {
            expedicionEste.encolar(p);
        } else {
            expedicionOeste.encolar(p);
        }
    }

    int pasosEspecial = preparacionEspecial.contarElementos();
    if (pasosEspecial > N_PEDIDOS_PASO) {
        pasosEspecial = N_PEDIDOS_PASO;
    }
    for (int i = 0; i < pasosEspecial; i++) {
        Pedido p = preparacionEspecial.valorFrente();
        preparacionEspecial.desencolar();
        cocina.encolar(p);
    }

    int pasosRecibidos = recibidos.contarElementos();
    if(pasosRecibidos > N_PEDIDOS_PASO) {
        pasosRecibidos = N_PEDIDOS_PASO;
    }

    for (int i = 0; i < pasosRecibidos; i++) {
        Pedido p = recibidos.valorFrente();
        recibidos.desencolar();
        if(p.personalizada) {
            preparacionEspecial.encolar(p);
        }else{
            cocina.encolar(p);
        }
    }
}


