#ifndef PIZZERIA2_H
#define PIZZERIA2_H

#include <string>

using namespace std;

#define ZONAS 4
// por que el define PROB_PERSONALIZACION esta en pizzeria2.cpp y no aqui? -> porque se usa allí, pero no debería estar todo junto? que quede más bonito y limpio?
// no, así lo pone en el doc

/*
 * Esto lo he añadido pq los pedidos avanzan en pasos de de 10 en 10 y se bifurcan en 4 zonas
 * con el define (macros) como pone en el documento
 */
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

class Nodo {
private:
    Pedido pedido;
    Nodo *siguiente;
public:
    Nodo(Pedido p, Nodo *sig = nullptr);
    friend class Cola;
};

typedef Nodo *pNodo;

class Cola {
private:
    pNodo primero;
    pNodo ultimo;
public:
    Cola();
    ~Cola();
    bool esVacia();
    void encolar(Pedido p);
    void desencolar();
    Pedido valorFrente();
    void mostrarCola(string nombreCola);
    void paso(string nombreCola);
    int contarElementos();
    /*
     * void mostrarCola(string nombreCola);
     *Lo de dentro lo he añadido porque ahora tenemos 7 colas, las de expedición y de
     *preparación, necesitamos pasarle un string para que sepamos qué cola estamos viendo exactamente
     */
};

string generarIdPedido(int contador);
Pedido generarPedidoAleatorio(int &contadorGlobal);

void ejecutarPasos(Cola &recibidos, Cola &preparacionEspecial, Cola &cocina, Cola &expedicionNorte, Cola &expedicionSur, Cola &expedicionEste, Cola &expedicionOeste);

#endif //PIZZERIA2_H