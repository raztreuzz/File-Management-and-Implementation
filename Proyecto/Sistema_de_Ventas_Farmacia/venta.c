// ventas.c
#include "ventas.h"
#include <stdio.h>
#include <string.h>

void listar_ventas(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_query(conn, "SELECT * FROM Ventas"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    printf("ID Venta\tID Cliente\tFecha\t\t\tTotal\tForma de Pago\n");
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s\t%s\t%s\t%s\t%s\n", row[0], row[1], row[2], row[3], row[4]);
    }

    mysql_free_result(res);
}

void agregar_venta(MYSQL *conn, Venta venta)
{
    char query[512];
    sprintf(query, "INSERT INTO Ventas (id_cliente, fecha, total, forma_pago) VALUES (%d, '%s', %.2f, '%s')",
            venta.id_cliente, venta.fecha, venta.total, venta.forma_pago);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    else
    {
        printf("Venta agregada exitosamente.\n");
    }
}

void eliminar_venta(MYSQL *conn, int id_venta)
{
    char query[256];
    sprintf(query, "DELETE FROM Ventas WHERE id_venta = %d", id_venta);

    if (mysql_query(conn, query))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
    else
    {
        printf("Venta eliminada exitosamente.\n");
    }
}

void registrar_venta(MYSQL *conn, int id_cliente, Carrito *carrito) {
    // Verificar que el id_cliente no sea inválido
    if (id_cliente <= 0) {
        printf("Error: id_cliente inválido.\n");
        return;
    }

    // Query para insertar en la tabla Ventas
    const char *query = "INSERT INTO Ventas (id_cliente, total) VALUES (?, ?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);

    if (stmt == NULL) {
        printf("Error al inicializar la declaración.\n");
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
        printf("Error al preparar la consulta: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return;
    }

    // Llenar los parámetros de la consulta
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));  // Inicializar con ceros para evitar errores

    // Vinculando `id_cliente`
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].buffer = &id_cliente;

    // Vinculando `total`
    bind[1].buffer_type = MYSQL_TYPE_DOUBLE;
    double total = carrito->total;  // Asegúrate de que `total` esté calculado
    bind[1].buffer = &total;

    // Vincular parámetros a la declaración
    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        printf("Error al vincular los parámetros: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return;
    }

    // Ejecutar la consulta
    if (mysql_stmt_execute(stmt) != 0) {
        printf("Error al ejecutar la consulta: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return;
    }

    // Confirmación de éxito
    printf("Venta registrada con éxito.\n");

    // Obtener el ID de la venta registrada
    int id_venta = mysql_insert_id(conn);
    printf("ID de la venta registrada: %d\n", id_venta);

    // Cerrar la declaración
    mysql_stmt_close(stmt);
}
