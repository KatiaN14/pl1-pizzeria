Implementa un sistema de gestión de repartidores motorizados con tiempos de entrega variables. Esto elimina el envío instantáneo actual e introduce restricciones logísticas reales en la simulación.

**Cambios estructurales**

* **Nueva entidad:** Crea un struct `Repartidor` con las variables `id_repartidor`, `disponible` (booleano) y `pasos_restantes` (entero).
* **Cola intermedia:** Añade una estructura `Cola cajasPendientes` en el programa principal para retener las cajas térmicas llenas.


* **Modificar el procesado:** Al alcanzar el límite `CAP_CAJA` dentro de la función `procesarCaja`, interrumpe el flujo actual. No envíes los pedidos directamente a la cola de `finalizados`. Transfiere la caja completa a `cajasPendientes`.



**Lógica de simulación en `ejecutarPasos**`

* **Actualizar estados:** Decrementa la variable `pasos_restantes` en los repartidores ocupados durante cada ciclo.
* **Finalizar entrega:** Cuando el tiempo llegue a 0, el repartidor queda disponible. Transfiere entonces los pedidos de su carga a la cola de finalizados.
* **Asignar entregas:** Si existen elementos en `cajasPendientes` y repartidores disponibles, emparéjalos. Marca al repartidor como ocupado y genera un tiempo de entrega aleatorio de 2 a 5 ciclos.

