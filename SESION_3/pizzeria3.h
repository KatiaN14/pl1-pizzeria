#ifndef PIZZERIA3_H
#define PIZZERIA3_H

#include <string>

using namespace std;

const int ZONAS = 4;
const int N_PEDIDOS_PASO = 10;
const int CAP_CAJA = 6;
const int MAX_PEDIDOS = 9999;

struct Pedido {
    string id_pedido;
    int id_cliente;
    string tipo_pizza;
    string tamano;
    string zona_reparto;
    bool personalizada;
    string estado;
};

class Nodo {
private:
    Pedido pedido;
    Nodo *siguiente;
    friend class Cola;
    friend class Pila;
public:
    Nodo(Pedido p, Nodo *sig = nullptr) : pedido(p), siguiente(sig) {}
};

typedef Nodo *pNodo;

class Cola {
private:
    pNodo primero;
    pNodo ultimo;
public:
    Cola();                          
    ~Cola();
    Cola(const Cola &) = delete;     
    Cola &operator=(const Cola &) = delete;
    void encolar(Pedido p);          
    void desencolar();               
    Pedido valorFrente();           
    bool esVacia();                  
};

class Pila {
private:
    pNodo cima;
public:
    Pila();                          
    ~Pila();
    Pila(const Pila &) = delete;
    Pila &operator=(const Pila &) = delete;

    void apilar(Pedido p);           
    void desapilar();                
    Pedido valorCima();              
    bool esVacia();                
};

int calcularSecuenciaAleatoria(int x);
string generarIdPedido(int contador);
Pedido generarPedidoAleatorio(int &contadorGlobal);

int contarCola(Cola &c);
int contarCaja(Pila &caja);
void mostrarCola(Cola &c, const string &nombreCola);
void mostrarCaja(Pila &caja);
bool retirarPedido(Pila &caja, const string &idPedido, Cola &finalizados);

void mostrarResumenCajas(Pila &cajaNorte, Pila &cajaSur, Pila &cajaEste, Pila &cajaOeste, int cajasEnviadas[], int totalPedidosRetirados);

void procesarCaja(Pila &caja, Cola &expedicionZona, int cajasEnviadas[], Cola &finalizados, int zona);

void ejecutarPasos(Cola &recibidos, Cola &preparacionEspecial, Cola &cocina, Cola &expedicionNorte, Cola &expedicionSur, Cola &expedicionEste, Cola &expedicionOeste, Pila &cajaNorte, Pila &cajaSur, Pila &cajaEste, Pila &cajaOeste, int cajasEnviadas[], Cola &finalizados);

#endif // PIZZERIA3_H