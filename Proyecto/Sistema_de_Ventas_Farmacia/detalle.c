// detalles.c
#include "detalles.h"
#include <stdio.h>

void listar_detalles(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Detalles_Venta")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("ID Detalle\tID Venta\tID Producto\tCantidad\tPrecio Unitario\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(res);
}

void agregar_detalle(MYSQL *conn, DetalleVenta detalle) {
    char query[256];
    sprintf(query, "INSERT INTO Detalles_Venta (id_venta, id_producto, cantidad, precio_unitario) VALUES (%d, %d, %d, %.2f)",
            detalle.id_venta, detalle.id_producto, detalle.cantidad, detalle.precio_unitario);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Detalle de venta agregado exitosamente.\n");
    }
}

void eliminar_detalle(MYSQL *conn, int id_detalle) {
    char query[256];
    sprintf(query, "DELETE FROM Detalles_Venta WHERE id_detalle = %d", id_detalle);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Detalle de venta eliminado exitosamente.\n");
    }
}
