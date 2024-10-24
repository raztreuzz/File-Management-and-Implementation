// clientes.h
#ifndef CLIENTES_H
#define CLIENTES_H

#include <mysql/mysql.h>

// Funciones para manipular la tabla de clientes
void listar_clientes(MYSQL *conn);
void agregar_cliente(MYSQL *conn, const char *nombre, const char *telefono);
void actualizar_cliente(MYSQL *conn, int id_cliente, const char *nuevo_telefono);
void eliminar_cliente(MYSQL *conn, int id_cliente);

#endif // CLIENTES_H
