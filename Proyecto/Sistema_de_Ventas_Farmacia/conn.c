#include "conn.h"
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

// Función para inicializar la conexión a la base de datos
MYSQL* initialize_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() falló\n");
        exit(EXIT_FAILURE);
    }

    // Conexión a la base de datos
    if (mysql_real_connect(conn, "localhost", "usuario", "contraseña", "nombre_base_de_datos", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Error de conexión: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return conn;
}

// Función para cerrar la conexión
void close_db(MYSQL *conn) {
    mysql_close(conn);
}