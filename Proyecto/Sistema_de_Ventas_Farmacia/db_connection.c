#include <stdio.h>
#include <stdlib.h>
#include "db_connection.h"

// Función para conectar a la base de datos
DBConnection* db_connect(const char *host, const char *user, const char *password, const char *dbname, unsigned int port) {
    DBConnection *db = malloc(sizeof(DBConnection));
    db->conn = mysql_init(NULL);

    if (db->conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        free(db);
        return NULL;
    }

    // Usar los parámetros pasados en lugar de valores hardcodeados
    if (mysql_real_connect(db->conn, host, user, password, dbname, port, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(db->conn));
        mysql_close(db->conn);
        free(db);
        return NULL;
    }

    return db;
}

// Función para desconectar de la base de datos
void db_disconnect(DBConnection *db) {
    if (db != NULL) {
        if (db->conn != NULL) {
            mysql_close(db->conn);
        }
        free(db);
    }
}

// Función para ejecutar una consulta
MYSQL_RES* db_query(DBConnection *db, const char *query) {
    if (mysql_query(db->conn, query)) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(db->conn));
        return NULL;
    }

    return mysql_store_result(db->conn);
}

