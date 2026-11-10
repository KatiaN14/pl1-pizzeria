#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>
#include "pizzeria5.h"

using namespace std;

#define PROB_PERSONALIZACION 20

Cola::Cola() : primero(nullptr), ultimo(nullptr) {}

Cola::~Cola() {
    while (!esVacia()) {
        desencolar();
    }
}

void Cola::encolar(Pedido p) {
    pNodo nuevo = new Nodo(p);
    if (ultimo != nullptr) ultimo->siguiente = nuevo;
    ultimo = nuevo;
    if (primero == nullptr) primero = nuevo;
}

void Cola::desencolar() {
    if (primero == nullptr) return;
    pNodo aux = primero;
    primero = primero->siguiente;
    delete aux;
    if (primero == nullptr) ultimo = nullptr;
}

Pedido Cola::valorFrente() {
    if (esVacia()) {
        throw runtime_error("Error: Cola vacia.");
    }
    return primero->pedido;
}

bool Cola::esVacia() {
    return primero == nullptr;
}

Pila::Pila() : cima(nullptr) {}

Pila::~Pila() {
    while (!esVacia()) {
        desapilar();
    }
}

void Pila::apilar(Pedido p) {
    cima = new Nodo(p, cima);
}

void Pila::desapilar() {
    if (esVacia()) return;
    pNodo aux = cima;
    cima = cima->siguiente;
    delete aux;
}

Pedido Pila::valorCima() {
    if (esVacia()) {
        throw runtime_error("Error: Pila vacia.");
    }
    return cima->pedido;
}

bool Pila::esVacia() {
    return cima == nullptr;
}

int calcularSecuenciaAleatoria(int x) {
    return rand() % x;
}

string generarIdPedido(int contador) {
    return "P" + to_string(10000 + contador);
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

int contarCola(Cola &c) {
    Cola aux;
    int contador = 0;
    while (!c.esVacia()) {
        aux.encolar(c.valorFrente());
        c.desencolar();
        contador++;
    }
    while (!aux.esVacia()) {
        c.encolar(aux.valorFrente());
        aux.desencolar();
    }
    return contador;
}

int contarCaja(Pila &caja) {
    Pila aux;
    int contador = 0;
    while (!caja.esVacia()) {
        aux.apilar(caja.valorCima());
        caja.desapilar();
        contador++;
    }
    while (!aux.esVacia()) {
        caja.apilar(aux.valorCima());
        aux.desapilar();
    }
    return contador;
}

void mostrarCola(Cola &c, const string &nombreCola) {
    if (c.esVacia()) {
        cout << "\n[Aviso] La cola " << nombreCola << " esta vacia.\n" << endl;
        return;
    }

    cout << "\n=== " << nombreCola << " ===" << endl;
    cout << "Pedido   |  Cliente  |       Pizza      |    Tamaño    |   Zona   |   Pers  |       Estado" << endl;
    cout << "---------------------------------------------------------------------------------------------------" << endl;

    Cola aux;
    while (!c.esVacia()) {
        Pedido p = c.valorFrente();
        c.desencolar();
        cout << setw(7) << p.id_pedido << setw(3) << "|"
             << setw(9) << p.id_cliente << setw(3) << "|"
             << setw(16) << p.tipo_pizza << setw(3) << "|"
             << setw(12) << p.tamano << setw(3) << "|"
             << setw(8) << p.zona_reparto << setw(3) << "|"
             << setw(7) << (p.personalizada ? "Si" : "No") << setw(3) << "|"
             << setw(15) << p.estado << endl;
        aux.encolar(p);
    }
    while (!aux.esVacia()) {
        c.encolar(aux.valorFrente());
        aux.desencolar();
    }
}

void mostrarCaja(Pila &caja) {
    if (caja.esVacia()) {
        cout << "[Aviso] La caja está vacía." << endl;
        return;
    }

    cout << "(cima)" << endl;
    Pila aux;
    while (!caja.esVacia()) {
        Pedido p = caja.valorCima();
        caja.desapilar();
        cout << p.id_pedido << " - " << p.tipo_pizza << endl;
        aux.apilar(p);
    }
    cout << "(fondo)" << endl;
    while (!aux.esVacia()) {
        caja.apilar(aux.valorCima());
        aux.desapilar();
    }
}

bool retirarPedido(Pila &caja, const string &idPedido, Cola &finalizados) {
    Pila aux;
    bool encontrado = false;

    while (!caja.esVacia() && !encontrado) {
        Pedido p = caja.valorCima();
        caja.desapilar();
        if (p.id_pedido == idPedido) {
            p.estado = "Retirado";
            finalizados.encolar(p);
            encontrado = true;
        } else {
            aux.apilar(p);
        }
    }
    while (!aux.esVacia()) {
        caja.apilar(aux.valorCima());
        aux.desapilar();
    }
    return encontrado;
}

void mostrarResumenCajas(Pila &cajaNorte, Pila &cajaSur, Pila &cajaEste, Pila &cajaOeste,
                         int cajasEnviadas[], int totalPedidosRetirados) {
    cout << "\n=== CAJAS TERMICAS ===" << endl;
    cout << "Zona Norte -> activa: " << contarCaja(cajaNorte) << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[0] << endl;
    cout << "Zona Sur   -> activa: " << contarCaja(cajaSur)   << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[1] << endl;
    cout << "Zona Este  -> activa: " << contarCaja(cajaEste)  << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[2] << endl;
    cout << "Zona Oeste -> activa: " << contarCaja(cajaOeste) << "/" << CAP_CAJA << "  enviadas: " << cajasEnviadas[3] << endl;

    int totalEnviadas = cajasEnviadas[0] + cajasEnviadas[1] + cajasEnviadas[2] + cajasEnviadas[3];
    cout << "Total de cajas enviadas: " << totalEnviadas << endl;
    cout << "Pedidos enviados o retirados: " << (totalEnviadas * CAP_CAJA) + totalPedidosRetirados << endl;
}

void mostrarEstadoRepartidores(Repartidor repartidores[], int numRepartidores, Cola &cajasPendientes) {
    cout << "\n=== ESTADO DE REPARTIDORES ===" << endl;
    cout << "Pedidos retenidos en cola intermedia: " << contarCola(cajasPendientes) << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < numRepartidores; i++) {
        cout << "Repartidor #" << repartidores[i].id_repartidor << " -> "
             << (repartidores[i].disponible ? "DISPONIBLE" : "OCUPADO (Pasos restantes: " + to_string(repartidores[i].pasos_restantes) + ")") 
             << endl;
    }
    cout << "--------------------------------------------------------" << endl;
}

void procesarCaja(Pila &caja, Cola &expedicionZona, int cajasEnviadas[], Cola &cajasPendientes, int zona) {
    int enCaja = contarCaja(caja);

    while (!expedicionZona.esVacia() && enCaja < CAP_CAJA) {
        Pedido p = expedicionZona.valorFrente();
        expedicionZona.desencolar();
        p.estado = "En caja";
        caja.apilar(p);
        enCaja++;
    }

    if (enCaja == CAP_CAJA) {
        while (!caja.esVacia()) {
            Pedido p = caja.valorCima();
            caja.desapilar();
            p.estado = "En espera de reparto"; 
            cajasPendientes.encolar(p); 
        }
        cajasEnviadas[zona]++;
    }
}

void actualizarEstadosRepartidores(Repartidor repartidores[], int numRepartidores, Cola &cajasPendientes, Cola &finalizados) {
    for (int i = 0; i < numRepartidores; i++) {
        if (!repartidores[i].disponible) {
            repartidores[i].pasos_restantes--;
            
            if (repartidores[i].pasos_restantes <= 0) {
                repartidores[i].disponible = true;
                
                for (int j = 0; j < CAP_CAJA; j++) {
                    if (!repartidores[i].ids_cargados[j].empty()) {
                        Pedido p_entregado;
                        p_entregado.id_pedido = repartidores[i].ids_cargados[j];
                        p_entregado.estado = "Entregado";
                        p_entregado.tipo_pizza = "Caja Completa";
                        finalizados.encolar(p_entregado);
                        repartidores[i].ids_cargados[j] = ""; 
                    }
                }
                cout << "[Simulación] Repartidor #" << repartidores[i].id_repartidor << " ha completado su entrega." << endl;
            }
        }
    }

    for (int i = 0; i < numRepartidores; i++) {
        if (repartidores[i].disponible && contarCola(cajasPendientes) >= CAP_CAJA) {
            repartidores[i].disponible = false;
            repartidores[i].pasos_restantes = 2 + calcularSecuenciaAleatoria(4); 
            
            cout << "[Simulación] Asignando caja al Repartidor #" << repartidores[i].id_repartidor 
                 << " (Tiempo estimado: " << repartidores[i].pasos_restantes << " ciclos)." << endl;

            for (int j = 0; j < CAP_CAJA; j++) {
                Pedido p = cajasPendientes.valorFrente();
                cajasPendientes.desencolar();
                p.estado = "En reparto";
                
                repartidores[i].ids_cargados[j] = p.id_pedido;
                // NOTA LOGICA: Se elimina la línea finalizados.encolar(p) aquí para evitar duplicidad
            }
        }
    }
}

void ejecutarPasos(Cola &recibidos, Cola &preparacionEspecial, Cola &cocina, Cola &expedicionNorte, Cola &expedicionSur, Cola &expedicionEste, Cola &expedicionOeste, Pila &cajaNorte, Pila &cajaSur, Pila &cajaEste, Pila &cajaOeste, int cajasEnviadas[], Cola &cajasPendientes, Repartidor repartidores[], int numRepartidores, Cola &finalizados) {
    
    procesarCaja(cajaNorte, expedicionNorte, cajasEnviadas, cajasPendientes, 0);
    procesarCaja(cajaSur,   expedicionSur,   cajasEnviadas, cajasPendientes, 1);
    procesarCaja(cajaEste,  expedicionEste,  cajasEnviadas, cajasPendientes, 2);
    procesarCaja(cajaOeste, expedicionOeste, cajasEnviadas, cajasPendientes, 3);
    
    for (int i = 0; i < N_PEDIDOS_PASO && !cocina.esVacia(); i++) {
        Pedido p = cocina.valorFrente();
        cocina.desencolar();
        p.estado = "En expedición";
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
    
    for (int i = 0; i < N_PEDIDOS_PASO && !preparacionEspecial.esVacia(); i++) {
        Pedido p = preparacionEspecial.valorFrente();
        preparacionEspecial.desencolar();
        p.estado = "En cocina";
        cocina.encolar(p);
    }
    
    for (int i = 0; i < N_PEDIDOS_PASO && !recibidos.esVacia(); i++) {
        Pedido p = recibidos.valorFrente();
        recibidos.desencolar();
        if (p.personalizada) {
            p.estado = "Prep. especial";
            preparacionEspecial.encolar(p);
        } else {
            p.estado = "En cocina";
            cocina.encolar(p);
        }
    }
    
    actualizarEstadosRepartidores(repartidores, numRepartidores, cajasPendientes, finalizados);
}