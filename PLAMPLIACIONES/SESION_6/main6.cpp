#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "pizzeria5.h"

int main() {
    srand(time(nullptr));

    int opcion;
    int opcion2;
    int opcion3;
    int contadorGlobal = 0;
    int totalPedidosRetirados = 0;

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
    
    // Estructuras para la logística de repartidores
    Cola cajasPendientes; 
    Repartidor repartidores[NUM_REPARTIDORES];
    
    // Inicializar repartidores
    for (int i = 0; i < NUM_REPARTIDORES; i++) {
        repartidores[i].id_repartidor = i + 1;
        repartidores[i].disponible = true;
        repartidores[i].pasos_restantes = 0;
        for (int j = 0; j < CAP_CAJA; j++) {
            repartidores[i].ids_cargados[j] = "";
        }
    }

    Cola finalizados;
    std::string idPedido;
    bool retirado = false;

    std::cout << "Bienvenidos a la pizzería, elija una opción:" << std::endl;

    do {
        std::cout << "\nOpción" << std::setw(15) << "Función" << std::endl;
        std::cout << std::setw(3) << "1" << "\t" << "Generar N pedidos" << std::endl;
        std::cout << std::setw(3) << "2" << "\t" << "Ejecutar un paso de simulación" << std::endl;
        std::cout << std::setw(3) << "3" << "\t" << "Mostrar el estado del sistema" << std::endl;
        std::cout << std::setw(3) << "4" << "\t" << "Ver la caja activa de una zona" << std::endl;
        std::cout << std::setw(3) << "5" << "\t" << "Retirar un pedido de una caja activa" << std::endl;
        std::cout << std::setw(3) << "6" << "\t" << "Mostrar pedidos finalizados" << std::endl;
        std::cout << std::setw(3) << "7" << "\t" << "Ver Estado de los Repartidores" << std::endl;
        std::cout << std::setw(3) << "0" << "\t" << "Salir" << std::endl;
        std::cout << "Opción: " << std::endl;
        
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            opcion = -1;
        }
        
        switch (opcion) {
            case 1: {
                int n;
                std::cout << "¿Cuántos pedidos desea generar?" << std::endl;
                if (!(std::cin >> n) || n <= 0) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Error: Tiene que ser un número entero positivo no nulo." << std::endl;
                    break;
                }
                if ((contadorGlobal + n) > MAX_PEDIDOS) {
                    std::cout << "Límite máximo de pedidos alcanzado." << std::endl;
                    break;
                }
                for (int i = 0; i < n; i++) {
                    Pedido nuevoPedido = generarPedidoAleatorio(contadorGlobal);
                    recibidos.encolar(nuevoPedido);
                }
                break;
            }
            case 2:
                ejecutarPasos(recibidos, preparacionEspecial, cocina, expedicionNorte, 
                              expedicionSur, expedicionEste, expedicionOeste, cajaNorte, 
                              cajaSur, cajaEste, cajaOeste, cajasEnviadas, cajasPendientes, 
                              repartidores, NUM_REPARTIDORES, finalizados);
                break;
            case 3:
                std::cout << "¿Qué cola quiere ver?" << std::endl;
                std::cout << "Opción" << std::setw(15) << "Cola" << std::endl;
                std::cout << std::setw(3) << "1" << "\t" << "Recibidos" << std::endl;
                std::cout << std::setw(3) << "2" << "\t" << "Preparación especial" << std::endl;
                std::cout << std::setw(3) << "3" << "\t" << "Cocina" << std::endl;
                std::cout << std::setw(3) << "4" << "\t" << "Expedición Norte" << std::endl;
                std::cout << std::setw(3) << "5" << "\t" << "Expedición Sur" << std::endl;
                std::cout << std::setw(3) << "6" << "\t" << "Expedición Este" << std::endl;
                std::cout << std::setw(3) << "7" << "\t" << "Expedición Oeste" << std::endl;
                std::cout << std::setw(3) << "8" << "\t" << "Información sobre cajas" << std::endl;
                std::cout << std::setw(3) << "9" << "\t" << "Todas las colas y cajas" << std::endl;
                std::cout << "Opción: " << std::endl;
                if (!(std::cin >> opcion2)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
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
                    case 8: mostrarResumenCajas(cajaNorte, cajaSur, cajaEste, cajaOeste, cajasEnviadas, totalPedidosRetirados); break;
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
                        std::cout << "Entrada inválida, solo se aceptan números entre 1 y 9" << std::endl;
                }
                break;
            case 4:
                std::cout << "¿Qué zona quiere ver?" << std::endl;
                std::cout << "Opción" << std::setw(15) << "Zona" << std::endl;
                std::cout << std::setw(3) << "1" << "\t" << "Norte" << std::endl;
                std::cout << std::setw(3) << "2" << "\t" << "Sur" << std::endl;
                std::cout << std::setw(3) << "3" << "\t" << "Este" << std::endl;
                std::cout << std::setw(3) << "4" << "\t" << "Oeste" << std::endl;
                std::cout << "Opción: " << std::endl;
                if (!(std::cin >> opcion3)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    opcion3 = -1;
                }
                switch (opcion3) {
                    case 1:
                        std::cout << "\n=== CAJA ACTIVA: ZONA Norte ===" << std::endl;
                        mostrarCaja(cajaNorte);
                        break;
                    case 2:
                        std::cout << "\n=== CAJA ACTIVA: ZONA Sur ===" << std::endl;
                        mostrarCaja(cajaSur);
                        break;
                    case 3:
                        std::cout << "\n=== CAJA ACTIVA: ZONA Este ===" << std::endl;
                        mostrarCaja(cajaEste);
                        break;
                    case 4:
                        std::cout << "\n=== CAJA ACTIVA: ZONA Oeste ===" << std::endl;
                        mostrarCaja(cajaOeste);
                        break;
                    default:
                        std::cout << "Entrada inválida, solo se aceptan números entre 1 y 4" << std::endl;
                }
                break;
            case 5:
                std::cout << "¿De cuál caja quiere retirar el pedido?" << std::endl;
                std::cout << "Opción" << std::setw(15) << "Caja de la zona" << std::endl;
                std::cout << std::setw(3) << "1" << "\t" << "Norte" << std::endl;
                std::cout << std::setw(3) << "2" << "\t" << "Sur" << std::endl;
                std::cout << std::setw(3) << "3" << "\t" << "Este" << std::endl;
                std::cout << std::setw(3) << "4" << "\t" << "Oeste" << std::endl;
                std::cout << "Opción: " << std::endl;
                
                if (!(std::cin >> opcion3) || opcion3 < 1 || opcion3 > 4) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Entrada inválida, solo se aceptan números entre 1 y 4" << std::endl;
                    break;
                }
                
                // Limpiamos el buffer antes de pedir un string
                std::cin.ignore(1000, '\n'); 
                
                if (opcion3 == 1) {
                    mostrarCaja(cajaNorte);
                    std::cout << "Ingrese el ID del pedido que desea retirar: " << std::endl;
                    std::cin >> idPedido;
                    retirado = retirarPedido(cajaNorte, idPedido, finalizados);
                } else if (opcion3 == 2) {
                    mostrarCaja(cajaSur);
                    std::cout << "Ingrese el ID del pedido que desea retirar: " << std::endl;
                    std::cin >> idPedido;
                    retirado = retirarPedido(cajaSur, idPedido, finalizados);
                } else if (opcion3 == 3) {
                    mostrarCaja(cajaEste);
                    std::cout << "Ingrese el ID del pedido que desea retirar: " << std::endl;
                    std::cin >> idPedido;
                    retirado = retirarPedido(cajaEste, idPedido, finalizados);
                } else {
                    mostrarCaja(cajaOeste);
                    std::cout << "Ingrese el ID del pedido que desea retirar: " << std::endl;
                    std::cin >> idPedido;
                    retirado = retirarPedido(cajaOeste, idPedido, finalizados);
                }
                
                if (retirado) {
                    std::cout << "Pedido " << idPedido << " retirado de la caja." << std::endl;
                    totalPedidosRetirados++;
                } else {
                    std::cout << "[Aviso] Pedido " << idPedido << " no encontrado en la caja." << std::endl;
                }
                break;
            case 6:
                std::cout << "\n=== PEDIDOS FINALIZADOS ===" << std::endl;
                mostrarCola(finalizados, "Finalizados");
                break;
            case 7:
                mostrarEstadoRepartidores(repartidores, NUM_REPARTIDORES, cajasPendientes);
                break;
            case 0:
                std::cout << "¡Hasta pronto!" << std::endl;
                break;
            default:
                std::cout << "Entrada inválida, introduzca una opción válida (de 0 a 7)" << std::endl;
        }
    } while (opcion != 0);
    
    return 0;
}