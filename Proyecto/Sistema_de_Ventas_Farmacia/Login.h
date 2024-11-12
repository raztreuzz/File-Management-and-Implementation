#ifndef LOGIN_H
#define LOGIN_H

#include <mysql/mysql.h>

// Función para verificar las credenciales de un usuario
int verificar_login(MYSQL *conn, const char *nombre_usuario, const char *contrasenia);

#endif // LOGIN_H
