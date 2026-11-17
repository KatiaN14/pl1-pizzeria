#include "listas_dobles.h"
#include <iostream>

using namespace std;

int main() {
    Lista lista;

    cout << "Insertamos nodo 20 al final" << endl;
    lista.insertarNodo(20,'f');
    lista.recorrerLista(0); //Podemos usar ASCENDENTE en lugar de 0

    cout << endl;
    cout << "Insertamos nodo 10 al final" << endl;
    lista.insertarNodo(10,'f');
    lista.recorrerLista(0);

    cout << endl;
    cout << "Insertamos nodo 40 al principio" << endl;
    lista.insertarNodo(40,'p');
    lista.recorrerLista(0);

    cout << endl;
    cout << "Insertamos nodo 30 al principio" << endl;
    lista.insertarNodo(30,'p');
    lista.recorrerLista(0);

    cout << endl;
    cout << "recorrer lista hacia adelante" << endl;
    lista.recorrerLista(ASCENDENTE);

    cout << endl;
    cout << "recorrer lista hacia atras" << endl;
    lista.recorrerLista(DESCENDENTE);  //Podemos escribir 1 en lugar de DESCENDENTE

    cout << endl;
    cout << "Borramos por el final" << endl;
    lista.borrarNodo('f');
    lista.recorrerLista(0);

    cout << endl;
    cout << "Borramos por el principio" << endl;
    lista.borrarNodo('p');
    lista.recorrerLista(0);

return 0;
}
