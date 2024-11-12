#ifndef CARRITO_H
#define CARRITO_H

#include <mysql/mysql.h>
#include "producto.h"  // Incluye la definición de Producto

#define MAX_PRODUCTOS 100

// Definición de la estructura para representar un producto en el carrito
typedef struct {
    int id_producto;
    char nombre[100];
    float precio;
    int cantidad;
} CarritoProducto;

// Definición de la estructura para representar el carrito
typedef struct {
    CarritoProducto productos[MAX_PRODUCTOS];  // Productos en el carrito
    int num_productos;               // Número de productos en el carrito
    float total;                     // Total de la compra
} Carrito;

// Declaración de las funciones
void agregar_producto_carrito(MYSQL *conn, Carrito *carrito, int id_producto, int cantidad);
void mostrar_carrito(Carrito *carrito);
void vaciar_carrito(Carrito *carrito);

#endif // CARRITO_H

