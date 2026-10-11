# Simulación del sistema de pedidos de una pizzaría

Una pizzería que realiza entregas a domicilio necesita una aplicación sencilla para registrar los pedidos que va
recibiendo. En esta primera versión del programa se implementará exclusivamente la recepción y
almacenamiento de pedidos. Los pedidos deberán conservarse en el mismo orden en que son recibidos.
Para ello se utilizará un TAD Cola dinámico implementado mediante nodos enlazados y memoria dinámica.

## Datos de un pedido 
Para simplificar la simulación, cada pedido contendrá una única pizza en su propia caja. Si un cliente desea
varias pizzas, realizará varios pedidos

Cada pedido se modelará mediante un struct con los siguientes campos:
- id_pedido: identificador único del pedido.
- id_cliente: identificador del cliente.
- tipo_pizza: variedad solicitada.
- tamano: tamaño de la pizza.
- zona_reparto: zona a la que deberá enviarse posteriormente.
- personalizada: indica si el cliente ha solicitado cambios en la receta.
- estado: situación actual del pedido.

En esta versión inicial, todos los pedidos tendrán el estado Recibido.

## TAD Cola de pedidos
Se implementará un TAD Cola que permita almacenar los pedidos realizados.
La cola se implementará mediante nodos enlazados y memoria dinámica y deberá disponer, al menos, de las
operaciones básicas estudiadas en las sesiones de Laboratorio.
Los pedidos se insertarán y procesarán respetando el orden de llegada.
No podrán utilizarse estructuras de datos no estudiadas en Laboratorio, como vectores, tablas hash, stack,
queue, plantillas u otras estructuras de la biblioteca estándar que sustituyan a las estructuras y tipos de datos
derivados tratados en clase.

## Generación de pedidos
El usuario podrá indicar cuántos pedidos desea generar. Los datos se obtendrán aleatoriamente respetando
las siguientes restricciones:
- id_pedido: letra P seguida de cinco cifras. Será único durante toda la ejecución.
- id_cliente: entero comprendido entre 100 y 999. Un cliente podrá realizar más de un pedido.
- tipo_pizza: Margarita, Barbacoa, Vegetal, Hawaiana, Romana o Cuatro quesos.
- tamano: Mediana o Grande.
- zona_reparto: Norte, Sur, Este u Oeste.
- personalizada: valor lógico generado aleatoriamente.
- estado: Recibido.

La probabilidad de que un pedido sea personalizado se definirá mediante la constante: #define PROB_PERSONALIZACION 20

Dicha constante se interpretará como un porcentaje, de modo que, con el valor propuesto, aproximadamente
el 20 % de los pedidos generados serán personalizados.

Todos los pedidos generados se insertarán en una cola denominada Recibidos.

## Menú de esta versión

Opción      Función 
    1   Generar N pedidos
    2   Mostrar pedidos recibidos
    0   Salir 

### Opción 1
El usuario indicará cuántos pedidos desea generar. Los pedidos se crearán con las restricciones anteriores y
se introducirán en la cola Recibidos. 

La generación de nuevos pedidos no eliminará los pedidos que ya estuvieran almacenados.

### Opción 2
Se mostrarán todos los pedidos existentes en la cola Recibidos en formato tabular. La visualización no deberá
modificar su orden en la cola.

VER (ejemplos_pedidos_recibidos.png)

## Organización del proyecto
El proyecto se distribuirá, al menos, en los siguientes archivos:

- pizzeria.h
- pizzeria.cpp
- main.cpp

En ellos se separarán adecuadamente la definición de estructuras y clases, los prototipos, la implementación
de métodos y funciones y el programa principal con el menú, respectivamente.

## Comprobaciones
Antes de finalizar la sesión deberá comprobarse que:
- pueden generarse varios pedidos;
- todos se almacenan en Recibidos;
- los identificadores son únicos;
- todos comienzan con estado Recibido;
- la proporción de pedidos personalizados se controla mediante PROB_PERSONALIZACION;
- generar una segunda tanda mantiene los pedidos anteriores;
- la visualización respeta el orden de llegada;
- el programa funciona correctamente cuando la cola está vacía