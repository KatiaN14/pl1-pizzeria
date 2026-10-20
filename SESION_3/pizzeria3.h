#ifndef PIZZERIA2_H
#define PIZZERIA2_H

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
    Nodo_Cola *siguiente;
public:
    Nodo_Cola(Pedido p, Nodo_Cola *sig = nullptr);
    friend class Cola;
};

typedef Nodo_Cola *pNodo_Cola;

class Cola {
private:
    pNodo_Cola primero;
    pNodo_Cola ultimo;
public:
    Cola();
    ~Cola();
    bool esVacia();
    void encolar(Pedido p);
    void desencolar();
    Pedido valorFrente();
    void mostrarCola(string nombreCola);

    /*
     * void mostrarCola(string nombreCola);
     *Lo de dentro lo he añadido porque ahora tenemos 7 colas, las de expedición y de
     *preparación, necesitamos pasarle un string para que sepamos qué cola estamos viendo exactamente
     */
};

class Pila;

class Nodo_Pila {
private:
    Pedido pedido;
    Nodo_Pila *siguiente;
    friend class Pila;
public:
    Nodo_Cola(Pedido p, Nodo_Pila *sig = nullptr) {
        pedido = p;
        siguiente = sig;
    }


typedef Nodo_Pila *pNodo_Pila;

class Pila
{
private:
    pNodo_Pila cima;
public:
    Pila();
    ~Pila();
    void apilar(int v);
    void desapilar();
    int valorCima();
    bool esVacia();
    int contarElementos();
};

string generarIdPedido(int contador);
Pedido generarPedidoAleatorio(int &contadorGlobal);

void ejecutarPasos(Cola &recibidos, Cola &preparacionEspecial, Cola &cocina, Cola &expedicionNorte, Cola &expedicionSur, Cola &expedicionEste, Cola &expedicionOeste);


#endif //PIZZERIA2_H