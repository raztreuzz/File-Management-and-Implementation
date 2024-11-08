#include <stdio.h>
#include <stdlib.h>
#include "db_connection.h"
#include "producto.h"
#include "clientes.h"
#include "ventas.h"
#include "detalles.h"

void mostrar_menu() {
    printf("----------------------------------------\n"); //
    printf("--- Sistema de Ventas Farmacia ---\n");
    printf("1. Listar productos\n");
    printf("2. Agregar producto\n");
    printf("3. Actualizar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Salir\n");
}

int main() {
    // Conectar a la base de datos
    DBConnection *db = db_connect("localhost", "root", "4613", "Farmacia", 3306); 

    if (db == NULL) {
        fprintf(stderr, "No se pudo conectar a la base de datos.\n");
        return 1;
    }

    int opcion;

    do {
        mostrar_menu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                listar_productos(db->conn);  // Pasar db->conn a las funciones
                break;
            case 2: {
                char nombre[100];
                double precio;
                int cantidad;
                printf("Nombre del producto: ");
                scanf("%s", nombre);
                printf("Precio del producto: ");
                scanf("%lf", &precio);
                printf("Cantidad del producto: ");
                scanf("%d", &cantidad);
                agregar_producto(db->conn, nombre, precio, cantidad);
                break;
            }
            case 3: {
                int id;
                double nuevo_precio;
                int nueva_cantidad;
                printf("ID del producto a actualizar: ");
                scanf("%d", &id);
                printf("Nuevo precio: ");
                scanf("%lf", &nuevo_precio);
                printf("Nueva cantidad: ");
                scanf("%d", &nueva_cantidad);
                actualizar_producto(db->conn, id, nuevo_precio, nueva_cantidad);
                break;
            }
            case 4: {
                int id;
                printf("ID del producto a eliminar: ");
                scanf("%d", &id);
                eliminar_producto(db->conn, id);
                break;
            }
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 5);

    // Desconectar de la base de datos
    db_disconnect(db);  
    return 0;
}
