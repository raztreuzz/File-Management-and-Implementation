// ventas.h
#ifndef VENTAS_H
#define VENTAS_H

#include <mysql/mysql.h>

// Funciones para manipular la tabla de ventas
void listar_ventas(MYSQL *conn);
void agregar_venta(MYSQL *conn, int id_cliente, const char *fecha);
void eliminar_venta(MYSQL *conn, int id_venta);

#endif // VENTAS_H
