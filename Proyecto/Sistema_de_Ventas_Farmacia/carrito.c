#include "carrito.h"
#include "producto.h"
#include <stdio.h>
#include <string.h>

// Función para agregar un producto al carrito
void agregar_producto_carrito(MYSQL *conn, Carrito *carrito, int id_producto, int cantidad) {
    Producto producto = obtener_producto(conn, id_producto);  // Obtener el producto desde la base de datos

    if (carrito->num_productos < MAX_PRODUCTOS) {
        CarritoProducto carrito_producto;
        carrito_producto.id_producto = producto.id_producto;
        strcpy(carrito_producto.nombre, producto.nombre);
        carrito_producto.precio = producto.precio;
        carrito_producto.cantidad = cantidad;

        // Agregar el producto al carrito
        carrito->productos[carrito->num_productos] = carrito_producto;
        carrito->num_productos++;

        // Calcular el total
        carrito->total += carrito_producto.precio * carrito_producto.cantidad;
    } else {
        printf("Carrito lleno, no se puede agregar más productos.\n");
    }
}

// Función para mostrar los productos en el carrito
void mostrar_carrito(Carrito *carrito) {
    printf("Productos en el carrito:\n");
    for (int i = 0; i < carrito->num_productos; i++) {
        printf("ID: %d, Nombre: %s, Precio: %.2f, Cantidad: %d\n",
                carrito->productos[i].id_producto,
                carrito->productos[i].nombre,
                carrito->productos[i].precio,
                carrito->productos[i].cantidad);
    }
    printf("Total: %.2f\n", carrito->total);
}

// Función para vaciar el carrito
void vaciar_carrito(Carrito *carrito) {
    carrito->num_productos = 0;
    carrito->total = 0.0;  // Resetear el total
}

