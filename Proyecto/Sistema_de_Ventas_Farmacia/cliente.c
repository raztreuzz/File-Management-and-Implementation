// clientes.c
#include "clientes.h"
#include <stdio.h>

void listar_clientes(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Clientes")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("ID\tNombre\tTelefono\n");
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\t%s\t%s\n", row[0], row[1], row[2]);
    }

    mysql_free_result(res);
}

void agregar_cliente(MYSQL *conn, const char *nombre, const char *telefono) {
    char query[256];
    sprintf(query, "INSERT INTO Clientes (nombre, telefono) VALUES ('%s', '%s')", nombre, telefono);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Cliente agregado exitosamente.\n");
    }
}

void actualizar_cliente(MYSQL *conn, int id_cliente, const char *nuevo_telefono) {
    char query[256];
    sprintf(query, "UPDATE Clientes SET telefono = '%s' WHERE id_cliente = %d", nuevo_telefono, id_cliente);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Cliente actualizado exitosamente.\n");
    }
}

void eliminar_cliente(MYSQL *conn, int id_cliente) {
    char query[256];
    sprintf(query, "DELETE FROM Clientes WHERE id_cliente = %d", id_cliente);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Cliente eliminado exitosamente.\n");
    }
}
