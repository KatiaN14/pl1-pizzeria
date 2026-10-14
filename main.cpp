#include <iostream>
#include <iomanip>

#include "pizzeria.h"

using namespace std;

int main() 
{
    int opcion;
    int contadorGlobal = 1;

    cout << "Bienvenidos a la pizzería, elija una opción:" << endl;
    cout << "Opción" << setw(15) << "Función" << endl;
    cout << setw(3) << "1" << "\t" << "Generar N pedidos" << endl;
    cout << setw(3) << "2" << "\t" << "Mostrar pedidos recibidos" << endl;
    cout << setw(3) << "0" << "\t" << "Salir" << endl;

    do {
        cout << "Opción: " << endl;
        if(!(cin >> opcion)) { 
            cin.clear(); 
            cin.ignore(1000,'\n'); 
            opcion = -1;
        }
        switch (opcion) {
            case 1:
                generarPedidoAleatorio(contadorGlobal);
                break;
            case 2:
                mostrarPedidosRecibidos();
                break;
            case 0:
                cout << "opcion 0 elegida" << endl;
                break;
            default:
                cout << "Entrada inválida, introduzca una opción válida (1, 2 o 0)" << endl;
        }
    } while (opcion != 1 && opcion != 2 && opcion != 0);

    return 0;
}