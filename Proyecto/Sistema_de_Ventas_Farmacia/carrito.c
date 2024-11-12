#include "carrito.h"
#include <stdio.h>
#include <string.h>


// Función para agregar un producto al carrito
int agregar_producto_carrito(MYSQL *conn, Carrito *carrito, int id_producto, int cantidad) {
    if (carrito->num_productos < 100) {  // Verificar que no haya más de 100 productos en el carrito
        CarritoProducto producto;
        // Asigna valores a producto (nombre, precio, etc.)

        carrito->productos[carrito->num_productos] = producto;
        carrito->num_productos++;
        carrito->total += producto.precio * cantidad;
        return 1;
    } else {
        printf("El carrito está lleno.\n");
        return 0;
    }
}

void mostrar_carrito(Carrito *carrito) {
    for (int i = 0; i < carrito->num_productos; i++) {
        printf("Producto: %s, Precio: %.2f, Cantidad: %d\n", carrito->productos[i].nombre, carrito->productos[i].precio, carrito->productos[i].cantidad);
    }
    printf("\nTotal del carrito: %.2f\n", carrito->total);
}

void vaciar_carrito(Carrito *carrito) {
    carrito->num_productos = 0;
    carrito->total = 0.0;
}

