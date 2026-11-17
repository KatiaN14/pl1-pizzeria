#include "listas_dobles.h"

using namespace std;

Lista::~Lista()
{
    pnodo aux;
    esCabeza();
    while(cabeza)
    {
        aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
    cabeza=NULL;
    actual=NULL;
    final=NULL;
}

void Lista::insertarNodo(int v, char c)
{
    pnodo aux;
    char tipoInsercion;
    tipoInsercion=c;

    if(listaVacia())   // Si la lista está vacía
    {
        aux = new Nodo(v,NULL,NULL);
        final=cabeza=aux;
    }
    else if (tipoInsercion=='f')  //Inserción por el final
    {
        aux= new Nodo(v,NULL,NULL);
        aux->anterior=final;
        final->siguiente=aux;
        final=aux;
    }
    else if (tipoInsercion=='p')  //Inserción por el principio
    {
        aux= new Nodo(v,NULL,NULL);
        aux->siguiente=cabeza;
        cabeza->anterior=aux;
        cabeza=aux;
    }
}

void Lista::borrarNodo(char c)
{
    char tipoBorrado;
    tipoBorrado=c;

    if(tipoBorrado=='f')  //Eliminación por el final
    {
        pnodo aux=NULL;
        if((cabeza==final))   //Sólo hay 1 elemento
        {
            aux=final;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=final;
            final=final->anterior;
            aux->anterior=NULL;
            final->siguiente=NULL;
            delete aux;
        }
    }
    else if(tipoBorrado=='p')  //Eliminación por el Principio
    {
        pnodo aux=NULL;
        if((cabeza==final))  //Sólo hay 1 elemento
        {
            aux=cabeza;
            cabeza = final = NULL;
            aux=NULL;
            delete aux;
        }
        else
        {
            aux=cabeza;
            cabeza=cabeza->siguiente;
            aux->siguiente=NULL;
            cabeza->anterior=NULL;
            delete aux;
        }
    }
}

void Lista::recorrerLista(int orden)
{
    pnodo aux;

    if (orden == ASCENDENTE)
    {
        esCabeza();
        aux = cabeza;
        while(aux)
        {
            cout << aux->valor << "-> ";
            aux = aux->siguiente;
        }
    }
    else
    {
        esFinal();
        aux = final;
        while(aux)
        {
            cout << aux->valor << "-> ";
            aux = aux->anterior;
        }
    }
    cout << endl;
}

bool Lista::listaVacia()
{
    return cabeza == NULL;
}

void Lista::esSiguiente()
{
    if(actual) actual = actual->siguiente;
}

void Lista::esAnterior()
{
    if(actual) actual = actual->anterior;
}

void Lista::esCabeza()
{
    actual=cabeza;
}

void Lista::esFinal()
{
    actual=final;
}

bool Lista::esActual()
{
    return actual != NULL;
}

int Lista::valorActual()
{
    if (!listaVacia()) return actual->valor;
    else return 0;
}


