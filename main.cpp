#include <iostream>
#include <iomanip>

#include "pizzeria.h"

using namespace std;

int main()
{
    int opcion;
    int contadorGlobal = 0;

    Cola recibidos;

    cout << "Bienvenidos a la pizzería, elija una opción:" << endl;

    do {
        cout << "Opción" << setw(15) << "Función" << endl;
        cout << setw(3) << "1" << "\t" << "Generar N pedidos" << endl;
        cout << setw(3) << "2" << "\t" << "Mostrar pedidos recibidos" << endl;
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
                recibidos.mostrarCola();
                break;
            case 0:
                cout << "Hasta pronto!" << endl;
                break;
            default:
                cout << "Entrada inválida, introduzca una opción válida (1, 2 o 0)" << endl;
        }
    } while (opcion != 0);

    return 0;
}