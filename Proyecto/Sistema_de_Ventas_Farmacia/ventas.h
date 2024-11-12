// ventas.h
#ifndef VENTAS_H
#define VENTAS_H

#include <mysql/mysql.h>
#include "carrito.h"
#include "producto.h"
#include "detalles.h"


// Estructura para una venta
typedef struct {
    int id_venta;
    int id_cliente;
    char fecha[20];  // Suponiendo que la fecha es un string con formato 'YYYY-MM-DD'
    float total;
    char forma_pago[20];
} Venta;

// Funciones para manejar las ventas
void listar_ventas(MYSQL *conn);
void agregar_venta(MYSQL *conn, Venta venta);
void eliminar_venta(MYSQL *conn, int id_venta);

// Declarar la función ver_registro_ventas
void ver_registro_ventas(MYSQL *conn);

void registrar_venta(MYSQL *conn, int id_cliente, Carrito *carrito);


#endif

