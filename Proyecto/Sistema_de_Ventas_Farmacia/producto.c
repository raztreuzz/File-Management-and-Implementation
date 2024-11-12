// producto.c
#include "producto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void listar_productos(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Productos"))
    {
        fprintf(stderr, "Error al listar productos: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "Error al obtener resultados: %s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Lista de Productos ---\n");
    printf("--------------------------------------------------------\n");
    printf("%-12s | %-20s | %-7s | %-8s\n", "ID Producto", "Nombre", "Precio", "Cantidad");
    printf("--------------------------------------------------------\n");

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%-12s | %-20s | %-7s | %-8s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);
}


void agregar_producto(MYSQL *conn, Producto producto)
{
    char query[256];
    sprintf(query, "INSERT INTO Productos (nombre, precio, cantidad) VALUES ('%s', %.2f, %d)",
            producto.nombre, producto.precio, producto.cantidad);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error al agregar producto: %s\n", mysql_error(conn));
    }
    else
    {
        printf("Producto agregado exitosamente.\n");
    }
}

void actualizar_producto(MYSQL *conn, Producto producto)
{
    char query[256];
    sprintf(query, "UPDATE Productos SET precio = %.2f, cantidad = %d WHERE id_producto = %d",
            producto.precio, producto.cantidad, producto.id_producto);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error al actualizar producto: %s\n", mysql_error(conn));
    }
    else
    {
        printf("Producto actualizado exitosamente.\n");
    }
}

void eliminar_producto(MYSQL *conn, int id_producto)
{
    char query[256];
    sprintf(query, "DELETE FROM Productos WHERE id_producto = %d", id_producto);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "Error al eliminar producto: %s\n", mysql_error(conn));
    }
    else
    {
        printf("Producto eliminado exitosamente.\n");
    }
}

