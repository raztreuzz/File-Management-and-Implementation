// db_connection.h
#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H
#include <mysql/mysql.h>

// Función para inicializar la conexión a la base de datos
MYSQL* initialize_db();

// Función para cerrar la conexión
void close_db(MYSQL *conn);

#endif // DB_CONNECTION_H
