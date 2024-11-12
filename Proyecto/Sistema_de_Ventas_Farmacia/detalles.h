// detalles.h
#ifndef DETALLES_H
#define DETALLES_H

#include <mysql/mysql.h>

// Estructura para los detalles de una venta
typedef struct {
    int id_detalle;
    int id_venta;
    int id_producto;
    int cantidad;
    float precio_unitario;
} DetalleVenta;

// Funciones para manejar los detalles de venta
void listar_detalles(MYSQL *conn);
void agregar_detalle(MYSQL *conn, DetalleVenta detalle);
void eliminar_detalle(MYSQL *conn, int id_detalle);

#endif
