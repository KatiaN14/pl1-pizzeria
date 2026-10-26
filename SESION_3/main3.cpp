#include <iostream>
#include <iomanip>

#include "pizzeria3.h"

using namespace std;

int main()
{
    int opcion;
    int opcion2;
    int opcion3;
    int contadorGlobal = 0;
    int totalPedidosRetirados = 0; //Para el resumen

    //Creo q así es mejor y no hay que ponerlo así, mejor un array
    int cajasEnviadas[4] = {0, 0, 0, 0};

    //Pilas nuevas
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

    cout << "Bienvenidos a la pizzería, elija una opción:" << endl;

    do {
        cout << "Opción" << setw(15) << "Función" << endl;
        cout << setw(3) << "1" << "\t" << "Generar N pedidos" << endl;
        cout << setw(3) << "2" << "\t" << "Ejecutar un paso de simulación" << endl;
        cout << setw(3) << "3" << "\t" << "Mostrar el estado del sistema" << endl;
        cout << setw(3) << "4" << "\t" << "Ver la caja activa de una zona" << endl;
        cout << setw(3) << "5" << "\t" << "Retirar un pedido de una caja activa" << endl;
        cout << setw(3) << "0" << "\t" << "Salir" << endl;
        cout << "Opción: " << endl;
        if(!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000,'\n');
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
                if ((contadorGlobal + n) > 9999){
                    cout << "Límite máximo de pedidos alcanzado." << endl;
                    break;
                }
                for (int i = 0; i<n; i++){
                    Pedido nuevoPedido = generarPedidoAleatorio(contadorGlobal);
                    recibidos.encolar(nuevoPedido);
                }
                break;
            }
            case 2:
                ejecutarPasos(recibidos, preparacionEspecial, cocina, expedicionNorte, expedicionSur, expedicionEste, expedicionOeste);
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
                if(!(cin >> opcion2)) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    opcion2 = -1;
                }
                switch(opcion2) {
                    case 1:
                        recibidos.mostrarCola("Recibidos");
                        break;
                    case 2:
                        preparacionEspecial.mostrarCola("Preparación especial");
                        break;
                    case 3:
                        cocina.mostrarCola("Cocina");
                        break;
                    case 4:
                        expedicionNorte.mostrarCola("Expedición Norte");
                        break;
                    case 5:
                        expedicionSur.mostrarCola("Expedición Sur");
                        break;
                    case 6:
                        expedicionEste.mostrarCola("Expedición Este");
                        break;
                    case 7:
                        expedicionOeste.mostrarCola("Expedición Oeste");
                        break;
                    case 8:
                        mostrarResumenCajas(cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, totalPedidosRetirados);
                        break;
                    case 9:
                        recibidos.mostrarCola("Recibidos");
                        preparacionEspecial.mostrarCola("Preparación especial");
                        cocina.mostrarCola("Cocina");
                        expedicionNorte.mostrarCola("Expedición Norte");
                        expedicionSur.mostrarCola("Expedición Sur");
                        expedicionEste.mostrarCola("Expedición Este");
                        expedicionOeste.mostrarCola("Expedición Oeste");
                        mostrarResumenCajas(cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, totalPedidosRetirados);
                        break;
                    default:
                        cout << "Entrada inválida, solo se aceptan números entre 1 y 7" << endl;
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
                if(!(cin >> opcion3)) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    opcion3 = -1;
                }
                switch(opcion3) {
                    case 1:
                        cajaNorte.mostrarCaja();
                        break;
                    case 2:
                        cajaSur.mostrarCaja();
                        break;
                    case 3:
                        cajaEste.mostrarCaja();
                        break;
                    case 4:
                        cajaOeste.mostrarCaja();
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
                switch(opcion3) {
                    case 1:
                        cajaNorte.retirarPedido();
                        break;
                    case 2:
                        cajaSur.retirarPedido();
                        break;
                    case 3:
                        cajaEste.retirarPedido();
                        break;
                    case 4:
                        cajaOeste.retirarPedido();
                        break;
                    default:
                        cout << "Entrada inválida, solo se aceptan números entre 1 y 4" << endl;
                }
                break;
            case 0:
                cout << "Hasta pronto!" << endl;
                break;
            default:
                cout << "Entrada inválida, introduzca una opción válida (1, 2, 3 o 0)" << endl;
        }
    } while (opcion != 0);

    return 0;
}
