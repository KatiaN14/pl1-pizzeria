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
            //no deberiamos poner lo de imprimir menus como funciones dentro de pizzeria.cpp y solo llamarlas aqui?
                cout << "Qué cola quiere ver?" << endl;
                cout << "Opción" << setw(15) << "Cola" << endl;
                cout << setw(3) << "1" << "\t" << "Recibidos" << endl;
                cout << setw(3) << "2" << "\t" << "Preparación especial" << endl;
                cout << setw(3) << "3" << "\t" << "Cocina" << endl;
                cout << setw(3) << "4" << "\t" << "Expedición Norte" << endl;
                cout << setw(3) << "5" << "\t" << "Expedición Sur" << endl;
                cout << setw(3) << "6" << "\t" << "Expedición Este" << endl;
                cout << setw(3) << "7" << "\t" << "Expedición Oeste" << endl;
                cout << "Opción: " << endl;
                if(!(cin >> opcion2)) {
                    cin.clear();
                    cin.ignore(1000,'\n');
                    opcion2 = -1;
                }
                switch(opcion2) {
                    case 1:
                        recibidos.mostrarCola("Recibidos");
                    case 2:
                        preparacionEspecial.mostrarCola("Preparación especial");
                    case 3:
                        cocina.mostrarCola("Cocina");
                    case 4:
                        expedicionNorte.mostrarCola("Expedición Norte");
                    case 5:
                        expedicionSur.mostrarCola("Expedición Sur");
                    case 6:
                        expedicionEste.mostrarCola("Expedición Este");
                    case 7:
                        expedicionOeste.mostrarCola("Expedición Oeste");
                    default:
                        cout << "Entrada inválida, introduzca una opción válida (1-7)" << endl;
                }
            case 0:
                cout << "Hasta pronto!" << endl;
                break;
            default:
                cout << "Entrada inválida, introduzca una opción válida (1, 2, 3 o 0)" << endl;
        }
    } while (opcion != 0);

    return 0;
}