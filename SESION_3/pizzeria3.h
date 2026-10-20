#ifndef PIZZERIA3_H
#define PIZZERIA3_H

#include <string>

using namespace std;

#define ZONAS 4
#define N_PEDIDOS_PASO 10
#define CAP_CAJA 6

struct Pedido {
    string id_pedido;
    int id_cliente;
    string tipo_pizza;
    string tamano;
    string zona_reparto;
    bool personalizada;
    string estado;
};

class Cola;

class Nodo_Cola {
private:
    Pedido pedido;
    Nodo_Cola* siguiente;
public:
    Nodo_Cola(Pedido p, Nodo_Cola* sig = nullptr)
        : pedido(p), siguiente(sig) {}

    friend class Cola;
};

typedef Nodo_Cola* pNodo_Cola;

class Cola {
private:
    pNodo_Cola primero;
    pNodo_Cola ultimo;
public:
    Cola();
    bool esVacia();
    void encolar(Pedido p);
    void desencolar(Pedido &valorFrente);
    void mostrarCola(string nombreCola);
};

class Pila;

class Nodo_Pila {
private:
    Pedido pedido;
    Nodo_Pila* siguiente;
public:
    Nodo_Pila(Pedido p, Nodo_Pila* sig = nullptr)
        : pedido(p), siguiente(sig) {}

    friend class Pila;
};

typedef Nodo_Pila* pNodo_Pila_tipo;

class Pila {
private:
    Nodo_Pila* cima;
public:
    Pila();
    bool esVacia();
    void apilar(Pedido p);
    void desapilar(Pedido &valorCima);
    int contarElementos();
    void mostrarCaja(string nombreZona);
    void retirarPedido(string nombrePedido);
};

string generarIdPedido(int contador);
Pedido generarPedidoAleatorio(int &contadorGlobal);

void ejecutarPasos(
    Cola &recibidos,
    Cola &preparacionEspecial,
    Cola &cocina,
    Cola &expedicionNorte,
    Cola &expedicionSur,
    Cola &expedicionEste,
    Cola &expedicionOeste
    );

#endif // PIZZERIA3_H
