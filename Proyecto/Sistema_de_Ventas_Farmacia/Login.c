#include "Login.h"
#include <stdio.h>
#include <string.h>

// Función para verificar el login del personal
int verificar_login(MYSQL *conn, const char *nombre_usuario, const char *contrasenia) {
    char query[256];
    sprintf(query, "SELECT * FROM Login_Personal WHERE nombre_usuario = '%s' AND contrasenia = '%s'", nombre_usuario, contrasenia);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error en la consulta: %s\n", mysql_error(conn));
        return 0;  // No se pudo realizar la consulta
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error al obtener el resultado: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        // Si no encontramos el usuario, es porque las credenciales son incorrectas
        printf("Credenciales incorrectas.\n");
        mysql_free_result(res);
        return 0;
    }

    // Si encontramos el usuario, entonces la verificación fue exitosa
    printf("Inicio de sesión exitoso.\n");
    mysql_free_result(res);
    return 1;  // Login correcto
}
