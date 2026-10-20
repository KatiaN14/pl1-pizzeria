#ifndef PIZZERIA_H
#define PIZZERIA_H
#include <string>

using namespace std;

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
    friend class Cola;
public:
    Nodo_Cola(Pedido p, Nodo_Cola* sig = nullptr);
};

typedef Nodo_Cola* pNodo;

class Cola {

private:
    pNodo primero;
    pNodo ultimo;

public:
    Cola();
    ~Cola();
    bool esVacia();
    void encolar(Pedido);
    void desencolar();
    Pedido valorFrente();
    void mostrarCola();
};

string generarIdPedido(int contador);
Pedido generarPedidoAleatorio(int &contadorGlobal);

#endif //PIZZERIA_H