
// main.c
#include <stdio.h>
#include <stdlib.h>
#include "conn.h"
#include "productos.h"

void mostrar_menu() {
    printf("1. Listar productos\n");
    printf("2. Agregar producto\n");
    printf("3. Actualizar producto\n");
    printf("4. Eliminar producto\n");
    printf("5. Salir\n");
}

int main() {
    MYSQL *conn = initialize_db();
    int opcion;

    do {
        mostrar_menu();
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                listar_productos(conn);
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
                agregar_producto(conn, nombre, precio, cantidad);
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
                actualizar_producto(conn, id, nuevo_precio, nueva_cantidad);
                break;
            }
            case 4: {
                int id;
                printf("ID del producto a eliminar: ");
                scanf("%d", &id);
                eliminar_producto(conn, id);
                break;
            }
            case 5:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
        }

    } while (opcion != 5);

    close_db(conn);
    return 0;
}
