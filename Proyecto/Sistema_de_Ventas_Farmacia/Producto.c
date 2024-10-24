// productos.c
#include "productos.h"
#include <stdio.h>

void listar_productos(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Productos")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("ID\tNombre\tPrecio\tCantidad\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);
}

void agregar_producto(MYSQL *conn, const char *nombre, double precio, int cantidad) {
    char query[256];
    sprintf(query, "INSERT INTO Productos (nombre, precio, cantidad) VALUES ('%s', %.2f, %d)", nombre, precio, cantidad);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Producto agregado exitosamente.\n");
    }
}

void actualizar_producto(MYSQL *conn, int id_producto, double nuevo_precio, int nueva_cantidad) {
    char query[256];
    sprintf(query, "UPDATE Productos SET precio = %.2f, cantidad = %d WHERE id_producto = %d", nuevo_precio, nueva_cantidad, id_producto);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Producto actualizado exitosamente.\n");
    }
}

void eliminar_producto(MYSQL *conn, int id_producto) {
    char query[256];
    sprintf(query, "DELETE FROM Productos WHERE id_producto = %d", id_producto);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Producto eliminado exitosamente.\n");
    }
}
