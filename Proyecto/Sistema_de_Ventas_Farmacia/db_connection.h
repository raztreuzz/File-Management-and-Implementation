#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <mysql/mysql.h>

// Estructura que contiene la conexión
typedef struct {
    MYSQL *conn;
} DBConnection;

// Función para inicializar la conexión
DBConnection* db_connect(const char *host, const char *user, const char *password, const char *dbname, unsigned int port);

// Función para cerrar la conexión
void db_disconnect(DBConnection *db);

// Función para ejecutar una consulta
MYSQL_RES* db_query(DBConnection *db, const char *query);

#endif // DB_CONNECTION_H
