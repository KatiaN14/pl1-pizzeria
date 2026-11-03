#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "pizzeria3.h"

using namespace std;

int main()
{
    srand(time(nullptr));  

    int opcion;
    int opcion2;
    int opcion3;
    int contadorGlobal = 0;
    int totalPedidosRetirados = 0;

    // orden de cajasEnviadas: Norte, Sur, Este, Oeste
    int cajasEnviadas[4] = {0, 0, 0, 0};

    Pila cajaNorte;
    Pila cajaSur;
    Pila cajaEste;
    Pila cajaOeste;

    Cola recibidos;
    Cola preparacionEspecial;
    Cola cocina;
    Cola expedicionNorte;
    Cola expedicionSur;
    Cola expedicionOeste;
    Cola expedicionEste;
    Cola finalizados;

    string idPedido;
    bool retirado = false;

    cout << "Bienvenidos a la pizzería, elija una opción:" << endl;

    do {
        cout << "Opción" << setw(15) << "Función" << endl;
        cout << setw(3) << "1" << "\t" << "Generar N pedidos" << endl;
        cout << setw(3) << "2" << "\t" << "Ejecutar un paso de simulación" << endl;
        cout << setw(3) << "3" << "\t" << "Mostrar el estado del sistema" << endl;
        cout << setw(3) << "4" << "\t" << "Ver la caja activa de una zona" << endl;
        cout << setw(3) << "5" << "\t" << "Retirar un pedido de una caja activa" << endl;
        cout << setw(3) << "6" << "\t" << "Mostrar pedidos finalizados" << endl;
        cout << setw(3) << "0" << "\t" << "Salir" << endl;
        cout << "Opción: " << endl;
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        }
        switch (opcion) {
            case 1: {
                int n;
                cout << "Cuántos pedidos desea generar?" << endl;
                if (!(cin >> n)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Tiene que ser un número entero positivo no nulo." << endl;
                    break;
                }
                if (n <= 0) {
                    cout << "Tiene que ser un número entero positivo no nulo." << endl;
                    break;
                }
                if ((contadorGlobal + n) > MAX_PEDIDOS) {
                    cout << "Límite máximo de pedidos alcanzado." << endl;
                    break;
                }
                for (int i = 0; i < n; i++) {
                    Pedido nuevoPedido = generarPedidoAleatorio(contadorGlobal);
                    recibidos.encolar(nuevoPedido);
                }
                break;
            }
            case 2:
                ejecutarPasos(recibidos, preparacionEspecial, cocina, expedicionNorte, expedicionSur, expedicionEste, expedicionOeste, cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, finalizados);
                break;
            case 3:
                cout << "Qué cola quiere ver?" << endl;
                cout << "Opción" << setw(15) << "Cola" << endl;
                cout << setw(3) << "1" << "\t" << "Recibidos" << endl;
                cout << setw(3) << "2" << "\t" << "Preparación especial" << endl;
                cout << setw(3) << "3" << "\t" << "Cocina" << endl;
                cout << setw(3) << "4" << "\t" << "Expedición Norte" << endl;
                cout << setw(3) << "5" << "\t" << "Expedición Sur" << endl;
                cout << setw(3) << "6" << "\t" << "Expedición Este" << endl;
                cout << setw(3) << "7" << "\t" << "Expedición Oeste" << endl;
                cout << setw(3) << "8" << "\t" << "Información sobre cajas" << endl;
                cout << setw(3) << "9" << "\t" << "Todas las colas y cajas" << endl;
                cout << "Opción: " << endl;
                if (!(cin >> opcion2)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    opcion2 = -1;
                }
                switch (opcion2) {
                    case 1: mostrarCola(recibidos, "Recibidos"); break;
                    case 2: mostrarCola(preparacionEspecial, "Preparación especial"); break;
                    case 3: mostrarCola(cocina, "Cocina"); break;
                    case 4: mostrarCola(expedicionNorte, "Expedición Norte"); break;
                    case 5: mostrarCola(expedicionSur, "Expedición Sur"); break;
                    case 6: mostrarCola(expedicionEste, "Expedición Este"); break;
                    case 7: mostrarCola(expedicionOeste, "Expedición Oeste"); break;
                    case 8:
                        mostrarResumenCajas(cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, totalPedidosRetirados);
                        break;
                    case 9:
                        mostrarCola(recibidos, "Recibidos");
                        mostrarCola(preparacionEspecial, "Preparación especial");
                        mostrarCola(cocina, "Cocina");
                        mostrarCola(expedicionNorte, "Expedición Norte");
                        mostrarCola(expedicionSur, "Expedición Sur");
                        mostrarCola(expedicionEste, "Expedición Este");
                        mostrarCola(expedicionOeste, "Expedición Oeste");
                        mostrarCola(finalizados, "Finalizados");
                        mostrarResumenCajas(cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, totalPedidosRetirados);
                        break;
                    default:
                        cout << "Entrada inválida, solo se aceptan números entre 1 y 9" << endl;
                }
                break;
            case 4:
                cout << "Qué zona quiere ver?" << endl;
                cout << "Opción" << setw(15) << "Zona" << endl;
                cout << setw(3) << "1" << "\t" << "Norte" << endl;
                cout << setw(3) << "2" << "\t" << "Sur" << endl;
                cout << setw(3) << "3" << "\t" << "Este" << endl;
                cout << setw(3) << "4" << "\t" << "Oeste" << endl;
                cout << "Opción: " << endl;
                if (!(cin >> opcion3)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    opcion3 = -1;
                }
                switch (opcion3) {
                    case 1:
                        cout << "\n=== CAJA ACTIVA: ZONA Norte ===" << endl;
                        mostrarCaja(cajaNorte);
                        break;
                    case 2:
                        cout << "\n=== CAJA ACTIVA: ZONA Sur ===" << endl;
                        mostrarCaja(cajaSur);
                        break;
                    case 3:
                        cout << "\n=== CAJA ACTIVA: ZONA Este ===" << endl;
                        mostrarCaja(cajaEste);
                        break;
                    case 4:
                        cout << "\n=== CAJA ACTIVA: ZONA Oeste ===" << endl;
                        mostrarCaja(cajaOeste);
                        break;
                    default:
                        cout << "Entrada inválida, solo se aceptan números entre 1 y 4" << endl;
                }
                break;
            case 5:
                cout << "De cuál caja quiere retirar el pedido?" << endl;
                cout << "Opción" << setw(15) << "Caja de la zona" << endl;
                cout << setw(3) << "1" << "\t" << "Norte" << endl;
                cout << setw(3) << "2" << "\t" << "Sur" << endl;
                cout << setw(3) << "3" << "\t" << "Este" << endl;
                cout << setw(3) << "4" << "\t" << "Oeste" << endl;
                cout << "Opción: " << endl;
                if(!(cin >> opcion3)) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    opcion3 = -1;
                }
                if (opcion3 < 1 || opcion3 > 4) {
                    cout << "Entrada inválida, solo se aceptan números entre 1 y 4" << endl;
                    break;
                }
                if (opcion3 == 1) {
                    mostrarCaja(cajaNorte);
                    cout << "Ingrese el ID del pedido que desea retirar: " << endl;
                    cin >> idPedido;
                    retirado = retirarPedido(cajaNorte, idPedido, finalizados);
                } else if (opcion3 == 2) {
                    mostrarCaja(cajaSur);
                    cout << "Ingrese el ID del pedido que desea retirar: " << endl;
                    cin >> idPedido;
                    retirado = retirarPedido(cajaSur, idPedido, finalizados);
                } else if (opcion3 == 3) {
                    mostrarCaja(cajaEste);
                    cout << "Ingrese el ID del pedido que desea retirar: " << endl;
                    cin >> idPedido;
                    retirado = retirarPedido(cajaEste, idPedido, finalizados);
                } else {
                    mostrarCaja(cajaOeste);
                    cout << "Ingrese el ID del pedido que desea retirar: " << endl;
                    cin >> idPedido;
                    retirado = retirarPedido(cajaOeste, idPedido, finalizados);
                }
                if (retirado) {
                    cout << "Pedido " << idPedido << " retirado de la caja." << endl;
                    totalPedidosRetirados++;
                } else {
                    cout << "[Aviso] Pedido " << idPedido << " no encontrado en la caja." << endl;
                }
                break;
            case 6:
                cout << "=== PEDIDOS FINALIZADOS ===" << endl;
                mostrarCola(finalizados, "Finalizados");
                break;
            case 0:
                cout << "Hasta pronto!" << endl;
                break;
            default:
                cout << "Entrada inválida, introduzca una opción válida (de 0 a 6)" << endl;
        }
    } while (opcion != 0);

    return 0;
}