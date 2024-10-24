// ventas.c
#include "ventas.h"
#include <stdio.h>

void listar_ventas(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Ventas")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("ID Venta\tID Cliente\tFecha\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }

    mysql_free_result(res);
}

void agregar_venta(MYSQL *conn, int id_cliente, const char *fecha) {
    char query[256];
    sprintf(query, "INSERT INTO Ventas (id_cliente, fecha) VALUES (%d, '%s')", id_cliente, fecha);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Venta agregada exitosamente.\n");
    }
}

void eliminar_venta(MYSQL *conn, int id_venta) {
    char query[256];
    sprintf(query, "DELETE FROM Ventas WHERE id_venta = %d", id_venta);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Venta eliminada exitosamente.\n");
    }
}
