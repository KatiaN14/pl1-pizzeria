#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "pizzeria3.h"

using namespace std;

#define PROB_PERSONALIZACION 20
#define N_PEDIDOS_PASO 10
#define CAP_CAJA 6

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}
Cola::~Cola()
{
    while (!esVacia())
    {
        Pedido aux;
        desencolar(aux);
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

void Cola::desencolar(Pedido &valorFrente)
{
    if (primero == nullptr) return;
    pNodo aux;
    aux = primero;
    primero = primero->siguiente;
    delete aux;
    if (primero == nullptr) ultimo = nullptr;
}

bool Cola::esVacia()
{
    return primero == nullptr;
}

Pila::Pila() : cima(nullptr) {}

Pila::~Pila() {
    while (!esVacia()) {
        desapilar();
    }
}

void Pila::apilar(int v) {
    cima = new Nodo(v, cima);
}

void Pila::desapilar() {
    if (esVacia()) return;
    pNodo aux = cima;
    cima = cima->siguiente;
    delete aux;
}

int Pila::valorCima() {
    if (esVacia()) {
        throw std::runtime_error("Error: Pila vacia.");
    }
    return cima->valor;
}

bool Pila::esVacia() {
    return cima == nullptr;
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

    pNodo_Cola aux = primero;

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

Pila::Pila() : cima(nullptr) {}
Pila::~Pila() {
    while (!esVacia())
    {
        Pedido aux;
        desapilar(aux);
    }
}

void Pila::apilar(Pedido p) {
    cima = new Nodo_Pila(p, cima);
}

void Pila::desapilar(Pedido &valorCima) {
    if (esVacia()) return;
    valorCima = cima->pedido;
    pNodo_Pila_tipo aux = cima;
    cima = cima->siguiente;
    delete aux;
}

int Pila::contarElementos() {
    int contador = 0;
    pNodo_Pila_tipo aux = cima;
    while (aux != nullptr) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

bool Pila::esVacia() {
    return cima == nullptr;
}

int calcularSecuenciaAleatoria(int x) {
    int numaleat;
    numaleat = rand() % x;
    return numaleat;
}

string generarIdPedido(int contador) {
    string id = "P" + to_string(10000 + contador);
    return id;
}

Pedido generarPedidoAleatorio(int &contadorGlobal) {
    string tipos[6] = {"Margarita", "Barbacoa", "Vegetal", "Hawaiana", "Romana", "Cuatro quesos"};
    string tamanos[2] = {"Mediana", "Grande"};
    string zonas[ZONAS] = {"Norte", "Sur", "Este", "Oeste"};

    contadorGlobal++;

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

void mostrarResumenCajas(Pila &cajaNorte, Pila &cajaSur, Pila &cajaEste, Pila &cajaOeste, int cajasEnviadas[], int totalPedidosRetirados) {
    cout << "\n=== CAJAS TERMICAS ===" << endl;
    cout << "Zona Norte -> activa: " << cajaNorte.contarElementos() << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[0] << endl;
    cout << "Zona Sur   -> activa: " << cajaSur.contarElementos()   << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[1] << endl;
    cout << "Zona Este  -> activa: " << cajaEste.contarElementos()  << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[2] << endl;
    cout << "Zona Oeste -> activa: " << cajaOeste.contarElementos() << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[3] << endl;

    /*
     * mostrarResumenCajas es literalmente el siguiente menu:
    === CAJAS TERMICAS ===
    Zona Norte -> activa: a1/6 enviadas: a2
    Zona Sur -> activa: b1/6 enviadas: b2
    Zona Este -> activa: c1/6 enviadas: c2
    Zona Oeste -> activa: d1/6 enviadas: d2
    Total de cajas enviadas: X
    Pedidos enviados o retirados: Y
     *
     */

    /*
     * totalEnviadas literalmente suma los valores de las 4 posiciones del array del main
     */
    int totalEnviadas = cajasEnviadas[0] + cajasEnviadas[1] + cajasEnviadas[2] + cajasEnviadas[3];
    cout << "Total de cajas enviadas: " << totalEnviadas << endl;
    cout << "Pedidos enviados o retirados: " << (totalEnviadas * CAP_CAJA) + totalPedidosRetirados << endl;
    /*
     * Aqui calculo el volumen total de pedidos que hemos retirado (si son 3 cajas, 18 pedidos vaya), para eso he multiplicado
     * para obtener los pedidos entregados con éxito, y le sumo la variable para contar los descartados por incidencias
     */
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
 
//funcion para ver el contenido de una caja
/*
=== CAJA ACTIVA: ZONA Norte ===
(cima)
P10008 - Barbacoa
P10006 - Vegetal
P10005 - Romana
P10000 - Romana
(fondo)
*/

void Pila::mostrarCaja() {
    if (Pila == cajaNorte) {
        cout << "\n=== CAJA ACTIVA: ZONA Norte ===" << endl;
    } else if (Pila == cajaSur) {
        cout << "\n=== CAJA ACTIVA: ZONA Sur ===" << endl;
    } else if (Pila == cajaEste) {
        cout << "\n=== CAJA ACTIVA: ZONA Este ===" << endl;
    } else if (Pila == cajaOeste) {
        cout << "\n=== CAJA ACTIVA: ZONA Oeste ===" << endl;
    }

    if (esVacia()) {
        cout << "[Aviso] La caja está vacía." << endl;
        return;
    }

    cout << "(cima)" << endl;
    pNodo_Pila_tipo aux = cima;
    while (aux != nullptr) {
        cout << aux->valor << endl;
        aux = aux->siguiente;
    }
    cout << "(fondo)" << endl;
}

void Pila::retirarPedido() {
    cout << "Ingrese el ID del pedido que desea retirar: ";
    cout << "ID: " << endl;
    if(!(cin >> idPedido)) {
        cin.clear();
        cin.ignore(1000,'\n');
        idPedido = -1;
    }
    if (esVacia()) {
        cout << "[Aviso] La caja está vacía. No se puede retirar ningún pedido." << endl;
        return;
    }

    Pila auxPila;
    bool encontrado = false;

    while (!esVacia()) {
        Pedido p;
        desapilar(p);
        if (p.id_pedido == idPedido) {
            encontrado = true;
            cout << "Pedido " << idPedido << " retirado de la caja." << endl;
            break;
        } else {
            auxPila.apilar(p);
        }
    }

    while (!auxPila.esVacia()) {
        Pedido p;
        auxPila.desapilar(p);
        apilar(p);
    }

    if (!encontrado) {
        cout << "[Aviso] Pedido " << idPedido << " no encontrado en la caja." << endl;
    }
}

