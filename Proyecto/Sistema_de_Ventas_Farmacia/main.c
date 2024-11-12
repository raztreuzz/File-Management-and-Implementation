#include <stdio.h>
#include <stdlib.h>

#include "db_connection.h"
#include "producto.h"
#include "clientes.h"
#include "ventas.h"
#include "detalles.h"
#include "Login.h"  // Incluimos el archivo con la función de verificación de login

// Función para mostrar el menú principal después del login
void mostrar_menu_Principal_After_Login() {
    printf("\n----------------------------------------\n");
    printf("    --- Menú Principal ---\n");
    printf("1. Ventas\n");
    printf("2. Inventario\n");
    printf("3. Tareas\n");
    printf("4. Salir\n");
    printf("----------------------------------------\n");
}

// Función para mostrar el registro de ventas
void ver_registro_ventas(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    // Consulta para obtener todas las ventas registradas
    if (mysql_query(conn, "SELECT * FROM Ventas")) {
        fprintf(stderr, "Error al obtener las ventas: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Registro de Ventas ---\n");
    printf("%-10s | %-10s | %-20s | %-10s\n", "ID Venta", "Cliente", "Fecha y Hora", "Total");
    printf("----------------------------------------------\n");

    // Mostrar todas las ventas
    while ((row = mysql_fetch_row(res)) != NULL) {
        // Aseguramos que cada columna esté alineada adecuadamente
        printf("%-10s | %-10s | %-20s | %-10s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);
}

// Función para manejar las opciones de Ventas
void menu_ventas(MYSQL *conn) {
    int opcion;
    while (1) {
        printf("\n--- Ventas ---\n");
        printf("1. Simular compra\n");
        printf("2. Ver registro de ventas\n");
        printf("3. Regresar al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Simulando compra de cliente...\n");
                // Aquí iría la lógica para simular una compra
                break;
            case 2:
                ver_registro_ventas(conn);  // Mostrar el registro de ventas
                break;
            case 3:
                return;  // Regresar al menú principal
            default:
                printf("Opción no válida.\n");
        }
    }
}

// Función para manejar las Tareas pendientes
void menu_tareas() {
    int opcion;
    // Arreglo de tareas, donde 0 es "pendiente" y 1 es "completada"
    char *tareas[] = {
        "Revisar inventario de productos", 
        "Realizar pedido de medicamentos", 
        "Revisar estado de ventas", 
        "Limpiar y organizar la bodega"
    };
    
    int estado_tareas[] = {0, 0, 0, 0};  // 0: pendiente, 1: completada

    while (1) {
        printf("\n--- Tareas Pendientes ---\n");

        // Imprimir las tareas pendientes
        for (int i = 0; i < 4; i++) {
            printf("%d. %s", i + 1, tareas[i]);
            if (estado_tareas[i] == 1) {
                printf(" (Completada)");
            }
            printf("\n");
        }
        
        printf("Seleccione una opción para continuar (0 para salir): ");
        scanf("%d", &opcion);

        if (opcion == 0) {
            printf("Regresando al menú principal...\n");
            return;  // Regresa al menú principal
        }

        // Validamos si la opción seleccionada es válida
        if (opcion < 1 || opcion > 4) {
            printf("Opción no válida.\n");
        } else {
            // Marcamos la tarea como completada
            int indice_tarea = opcion - 1;
            if (estado_tareas[indice_tarea] == 0) {
                estado_tareas[indice_tarea] = 1;  // Cambiar el estado a completada
                printf("¡Tarea '%s' completada!\n", tareas[indice_tarea]);
            } else {
                printf("La tarea '%s' ya está completada.\n", tareas[indice_tarea]);
            }
        }
    }
}



// Función para solicitar el login
int solicitar_login(MYSQL *conn) {
    char nombre_usuario[50];
    char contrasenia[50];

    // Solicitar nombre de usuario y contraseña
    printf("Ingrese nombre de usuario: ");
    scanf("%s", nombre_usuario);
    printf("Ingrese contraseña: ");
    scanf("%s", contrasenia);

    // Verificar las credenciales del usuario
    if (verificar_login(conn, nombre_usuario, contrasenia)) {
        printf("Bienvenido %s.\n", nombre_usuario);
        return 1;  // Login exitoso
    } else {
        printf("Inicio de sesión fallido.\n");
        return 0;  // Login fallido
    }
}

// main.c (solo se muestra la parte de inventario)
void menu_inventario(MYSQL *conn) {
    int opcion;
    Producto producto;

    while (1) {
        printf("\n--- Inventario ---\n");
        printf("1. Agregar producto\n");
        printf("2. Ver productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Regresar al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                // Datos para agregar un producto
                printf("Nombre del producto: ");
                scanf("%s", producto.nombre);
                printf("Precio: ");
                scanf("%lf", &producto.precio);
                printf("Cantidad: ");
                scanf("%d", &producto.cantidad);
                agregar_producto(conn, producto);
                break;
            case 2:
                listar_productos(conn);
                break;
            case 3:
                // Datos para actualizar un producto
                printf("ID del producto a actualizar: ");
                scanf("%d", &producto.id_producto);
                printf("Nuevo precio: ");
                scanf("%lf", &producto.precio);
                printf("Nueva cantidad: ");
                scanf("%d", &producto.cantidad);
                actualizar_producto(conn, producto);
                break;
            case 4:
                // Eliminar producto
                printf("ID del producto a eliminar: ");
                scanf("%d", &producto.id_producto);
                eliminar_producto(conn, producto.id_producto);
                break;
            case 5:
                return;  // Volver al menú principal
            default:
                printf("Opción no válida.\n");
        }
    }
}


int main() {
    // Conectar a la base de datos
    DBConnection *db = db_connect("localhost", "root", "4613", "Farmacia", 3306); 

    if (db == NULL) {
        fprintf(stderr, "No se pudo conectar a la base de datos.\n");
        return 1;
    }

    int opcion;
    int login_exitoso = 0;

    // Solicitar login hasta que sea exitoso
    while (!login_exitoso) {
        login_exitoso = solicitar_login(db->conn);  // Llamamos a la función de login
    }

    // Si el login es exitoso, mostramos el menú principal
    while (1) {
        mostrar_menu_Principal_After_Login();  // Mostrar el menú principal

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menu_ventas(db->conn);  // Llamamos a la función de ventas, pasando la conexión
                break;
            case 2:
                
                menu_inventario(db->conn);  // Llamamos al submenú de inventario
                break;
            case 3:
                menu_tareas();  // Llamamos a la función de tareas
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                db_disconnect(db);  // Desconectar de la base de datos
                return 0;
            default:
                printf("Opción no válida.\n");
        }
    }

    // Desconectar de la base de datos en caso de que no se haya cerrado antes
    db_disconnect(db);  
    return 0;
}
