#include <stdio.h>
#include <string.h>

#define TAMANIO_TABLA 31

// Estructura para los elementos del inventario
typedef struct {
    char id[7]; // 6 caracteres + 1 para el terminador nulo
    char descripcion[30]; // 29 caracteres + 1 para el terminador nulo
    double costo;
} Elemento;

// Tabla hash para el inventario
Elemento inventario[TAMANIO_TABLA];

// Función hash para generar el índice a partir del ID
int obtenerCodigoHash(char *clave) {
    int hash = 0;
    for (int i = 0; i < strlen(clave); i++) {
        hash = 37 * hash + clave[i];
    }
    return hash % TAMANIO_TABLA;
}

// Función para agregar un nuevo producto al inventario
void agregarElemento(char *id, char *descripcion, double costo) {
    int indice = obtenerCodigoHash(id);
    // Resolución de colisiones (proceso de linearización)
    while (inventario[indice].id[0] != '\0') {
        indice = (indice + 1) % TAMANIO_TABLA;
    }
    strcpy(inventario[indice].id, id);
    strcpy(inventario[indice].descripcion, descripcion);
    inventario[indice].costo = costo;
}

// Función para buscar un producto en el inventario
int buscarElemento(char *id) {
    int indice = obtenerCodigoHash(id);
    int indiceOriginal = indice;
    while (strcmp(inventario[indice].id, id) != 0) {
        indice = (indice + 1) % TAMANIO_TABLA;
        if (indice == indiceOriginal) {
            return -1; // Producto no encontrado
        }
    }
    return indice;
}

int main() {
    // Inicialización de la tabla de inventario
    for (int i = 0; i < TAMANIO_TABLA; i++) {
        inventario[i].id[0] = '\0';
    }

    // Agregar productos al inventario
    agregarElemento("A12345", "Teclado Mecánico", 75.50);
    agregarElemento("B23456", "Auriculares Bluetooth", 120.99);
    agregarElemento("C34567", "Ratón Inalámbrico", 35.75);
    agregarElemento("D45678", "Monitor Curvo 27''", 320.00);

    // Solicitar al usuario el ID del producto a buscar
    char idBuscado[7]; // Espacio para el ID del producto (6 caracteres + terminador nulo)
    printf("Ingrese el ID del producto a buscar: ");
    scanf("%6s", idBuscado);  // Limitar a 6 caracteres para evitar desbordamientos

    // Buscar el producto y mostrar los resultados
    int indice = buscarElemento(idBuscado);
    if (indice != -1) {
        printf("Producto encontrado en la posición %d: %s, %s, %.2f\n", indice, inventario[indice].id, inventario[indice].descripcion, inventario[indice].costo);
    } else {
        printf("Producto no encontrado\n");
    }

    return 0;
}

