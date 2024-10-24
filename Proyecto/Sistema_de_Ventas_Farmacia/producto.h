// productos.h
#ifndef PRODUCT_H
#define PRODUCTO_H

#include <mysql/mysql.h>

// Funciones para manipular la tabla de productos
void listar_productos(MYSQL *conn);
void agregar_producto(MYSQL *conn, const char *nombre, double precio, int cantidad);
void actualizar_producto(MYSQL *conn, int id_producto, double nuevo_precio, int nueva_cantidad);
void eliminar_producto(MYSQL *conn, int id_producto);

#endif // PRODUCTO_H
