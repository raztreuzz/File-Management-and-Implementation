// detalles.h
#ifndef DETALLES_H
#define DETALLES_H

#include <mysql/mysql.h>

// Funciones para manipular la tabla de detalles de ventas
void listar_detalles(MYSQL *conn);
void agregar_detalle(MYSQL *conn, int id_venta, int id_producto, int cantidad);
void eliminar_detalle(MYSQL *conn, int id_detalle);

#endif // DETALLES_H
