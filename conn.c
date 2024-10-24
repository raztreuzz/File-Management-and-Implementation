// db_connection.c
#include "conn.h"
#include <stdio.h>
#include <stdlib.h>

// Función para inicializar la conexión a la base de datos
MYSQL* initialize_db() {
    MYSQL *conn = mysql_init(NULL);  // Inicializa el conector MySQL

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Conectar a la base de datos
    if (mysql_real_connect(conn, "localhost", "root", "password", "Farmacia", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    return conn;  // Retorna la conexión establecida
}

// Función para cerrar la conexión a la base de datos
void close_db(MYSQL *conn) {
    if (conn != NULL) {
        mysql_close(conn);  // Cierra la conexión
    }
}
