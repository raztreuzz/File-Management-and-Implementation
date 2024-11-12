// producto.h
#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <mysql/mysql.h>

typedef struct {
    int id_producto;
    char nombre[50];
    double precio;
    int cantidad;
}Producto;

// Funciones de inventario
void listar_productos(MYSQL *conn);
void agregar_producto(MYSQL *conn, Producto producto);
void actualizar_producto(MYSQL *conn, Producto producto);
void eliminar_producto(MYSQL *conn, int id_producto);

// Declarar la función buscar_producto
int buscar_producto(MYSQL *conn, int id_producto, Producto *producto);
void actualizar_producto_inventario(MYSQL *conn, int id_producto, int cantidad);
Producto obtener_producto(MYSQL *conn, int id_producto);





#endif
