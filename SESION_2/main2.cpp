#include <iostream>
#include <iomanip>

#include "pizzeria2.h"

using namespace std;

int main()
{
    int opcion;
    int opcion2;
    int contadorGlobal = 0;

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
                        recibidos.mostrarCola("Recibidos");
                        preparacionEspecial.mostrarCola("Preparación especial");
                        cocina.mostrarCola("Cocina");
                        expedicionNorte.mostrarCola("Expedición Norte");
                        expedicionSur.mostrarCola("Expedición Sur");
                        expedicionEste.mostrarCola("Expedición Este");
                        expedicionOeste.mostrarCola("Expedición Oeste");
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