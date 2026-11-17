#ifndef LISTAS_DOBLES_H
#define LISTAS_DOBLES_H

#include <iostream>

const int ASCENDENTE=0;
const int DESCENDENTE=1;

class Nodo
{
    private:
        int valor;
        Nodo *siguiente;
        Nodo *anterior;
    friend class Lista;

    public:
        Nodo(int v, Nodo *sig = NULL, Nodo *ant = NULL)
        {
            valor = v;
            siguiente = sig;
            anterior = ant;
        }
};
typedef Nodo *pnodo;

class Lista
{
    private:
        pnodo cabeza, final, actual;

    public:
        Lista() {cabeza=actual=final=NULL; }
        ~Lista();
        void insertarNodo(int v, char c);
        void borrarNodo(char c);
        bool listaVacia();
        void esCabeza();
        void esFinal();
        void esSiguiente();
        void esAnterior();
        bool esActual();
        int valorActual();
        void recorrerLista(int);
};

#endif
