/* CÓDIGO HECHO CON IA (CAMBIAR A MEJOR)
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "pizzeria2.h"

using namespace std;

void mostrarMenu();

int main() {
    srand(time(nullptr));

    // 1. Nuevas fases del sistema (Según guion)
    // Implementadas mediante el TAD Cola dinámico
    Cola recibidos;
    Cola prep_especial;
    Cola cocina;

    // Uso de Vector de Objetos basado en el ejemplo del profesor: Persona listaPer[N2];
    Cola expedicion[ZONAS];

    // Vectores auxiliares para asociar las 4 zonas de reparto a los índices del vector expedicion
    string nombresZonas[ZONAS] = {"Norte", "Sur", "Este", "Oeste"};
    string nombresMayus[ZONAS] = {"NORTE", "SUR", "ESTE", "OESTE"};

    int opcion = 0;
    int contadorPedidos = 0;

    // 6. Menú de esta versión
    do {
        mostrarMenu();

        // Limpieza del buffer de entrada en caso de introducir un carácter no válido
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nError: Ingrese una opcion numerica valida.\n" << endl;
            continue;
        }

        switch (opcion) {
            case 1: {
                // Generar N pedidos
                int n;
                cout << "\nIndique cuantos pedidos desea generar: ";
                if (!(cin >> n) || n <= 0) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Cantidad no valida.\n" << endl;
                    break;
                }

                for (int i = 0; i < n; i++) {
                    // Generamos el pedido y se almacena en la cola Recibidos
                    // Pasamos el contadorGlobal por referencia para que se incremente dentro de la función
                    Pedido nuevoP = generarPedidoAleatorio(contadorPedidos);
                    recibidos.encolar(nuevoP);
                }
                cout << "\nSe han generado e insertado " << n << " pedidos correctamente.\n" << endl;
                break;
            }
            case 2: {
                // 3. Ejecutar un paso de simulación
                // IMPORTANTE (Regla del guion): Un pedido avanzará como máximo una fase en cada ejecución.
                // Para cumplir esta restricción, procesamos las colas en orden inverso.

                int procesados = 0;

                // FASE 3: De Cocina a Expedición
                // "se procesará como máximo N_PEDIDOS_PASO elementos"
                while (!cocina.esVacia() && procesados < N_PEDIDOS_PASO) {
                    Pedido p = cocina.valorFrente();
                    cocina.desencolar();

                    // 4. Actualización del estado
                    p.estado = "Expedicion";

                    // 2. Recorrido de los pedidos:
                    // "Cuando un pedido termina en Cocina, se incorporará únicamente
                    // a la cola de Expedición correspondiente a su zona de reparto."
                    for (int i = 0; i < ZONAS; i++) {
                        if (p.zona_reparto == nombresZonas[i]) {
                            expedicion[i].encolar(p);
                            break;
                        }
                    }
                    procesados++;
                }

                // FASE 2: De Preparación Especial a Cocina
                procesados = 0;
                while (!prep_especial.esVacia() && procesados < N_PEDIDOS_PASO) {
                    Pedido p = prep_especial.valorFrente();
                    prep_especial.desencolar();

                    // 4. Actualización del estado
                    p.estado = "Cocina";
                    cocina.encolar(p);
                    procesados++;
                }

                // FASE 1: De Recibidos a Preparación Especial o Cocina
                procesados = 0;
                while (!recibidos.esVacia() && procesados < N_PEDIDOS_PASO) {
                    Pedido p = recibidos.valorFrente();
                    recibidos.desencolar();

                    // 2. Recorrido de los pedidos: El recorrido dependerá del valor del campo personalizada.
                    // La condición de pedido personalizado se utiliza con el valor almacenado desde su creación.
                    if (p.personalizada) {
                        // Pedido personalizado: Recibido -> Preparación especial
                        p.estado = "Prep. especial"; // 4. Actualización del estado
                        prep_especial.encolar(p);
                    } else {
                        // Pedido ordinario: Recibido -> Cocina
                        p.estado = "Cocina"; // 4. Actualización del estado
                        cocina.encolar(p);
                    }
                    procesados++;
                }
                cout << "\nPaso de simulacion completado.\n" << endl;
                break;
            }
            case 3: {
                // 5. Mostrar el estado del sistema
                // "La consulta no deberá alterar el orden de ninguna cola."
                recibidos.mostrarCola("RECIBIDOS");
                prep_especial.mostrarCola("PREPARACION ESPECIAL");
                cocina.mostrarCola("COCINA");

                // Mostramos el contenido de todas las colas de expedición
                for (int i = 0; i < ZONAS; i++) {
                    expedicion[i].mostrarCola("EXPEDICION " + nombresMayus[i]);
                }
                break;
            }
            case 0:
                cout << "\nHasta pronto!\n" << endl;
                break;
            default:
                cout << "\nError: Opcion incorrecta.\n" << endl;
        }

    } while (opcion != 0);

    return 0;
}

// Organización del programa: Extracción de los prints del menú para mayor claridad en el bucle principal
void mostrarMenu() {
    cout << "\nSimulacion: pedidos a una pizzeria" << endl;
    cout << "=== MENU ===" << endl;
    cout << "1) Generar N pedidos" << endl;
    cout << "2) Ejecutar paso de simulacion" << endl;
    cout << "3) Mostrar estado del sistema" << endl;
    cout << "0) Salir" << endl;
    cout << "Opcion: ";
}
*/