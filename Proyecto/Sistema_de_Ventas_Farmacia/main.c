#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "db_connection.h"
#include "producto.h"
#include "clientes.h"
#include "ventas.h"
#include "carrito.h"
#include "detalles.h"
#include "Login.h" // Incluimos el archivo con la función de verificación de login

// Función para mostrar el menú principal después del login
void mostrar_menu_Principal_After_Login()
{
    printf("\n----------------------------------------\n");
    printf("    --- Menú Principal ---\n");
    printf("1. Ventas\n");
    printf("2. Inventario\n");
    printf("3. Tareas\n");
    printf("4. Gestión de Clientes\n");
    printf("5. Salir\n");
    printf("----------------------------------------\n");
}

// Función para generar una fecha aleatoria dentro de un rango de fechas
void generar_fecha_aleatoria(char *fecha, int anio_inicio, int anio_fin)
{
    // Aseguramos que la semilla sea diferente cada vez
    srand(time(NULL));

    // Generamos un año aleatorio dentro del rango dado
    int anio = rand() % (anio_fin - anio_inicio + 1) + anio_inicio;

    // Generamos un mes aleatorio entre 1 y 12
    int mes = rand() % 12 + 1;

    // Generamos un día aleatorio, en función del mes
    int dia;
    if (mes == 2)
    {
        // Febrero (consideramos año no bisiesto por simplicidad)
        dia = rand() % 28 + 1;
    }
    else if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        // Meses con 30 días
        dia = rand() % 30 + 1;
    }
    else
    {
        // Meses con 31 días
        dia = rand() % 31 + 1;
    }

    // Formato de la fecha: YYYY-MM-DD
    sprintf(fecha, "%04d-%02d-%02d", anio, mes, dia);
}

void menu_gestion_clientes(MYSQL *conn)
{
    int opcion;
    char nombre[100], telefono[20];
    int id_cliente;

    while (1)
    {
        printf("\n--- Gestión de Clientes ---\n");
        printf("1. Agregar cliente\n");
        printf("2. Ver clientes\n");
        printf("3. Actualizar cliente\n");
        printf("4. Eliminar cliente\n");
        printf("5. Regresar al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            // Solicitar datos para agregar un cliente
            printf("Nombre del cliente: ");
            scanf("%s", nombre);
            printf("Teléfono: ");
            scanf("%s", telefono);
            agregar_cliente(conn, nombre, telefono); // Llamamos a la función para agregar cliente
            break;
        case 2:
            listar_clientes(conn); // Llamamos a la función para listar clientes
            break;
        case 3:
            // Solicitar datos para actualizar un cliente
            printf("ID del cliente a actualizar: ");
            scanf("%d", &id_cliente);
            printf("Nuevo teléfono: ");
            scanf("%s", telefono);
            actualizar_cliente(conn, id_cliente, telefono); // Llamamos a la función para actualizar cliente
            break;
        case 4:
            // Solicitar datos para eliminar un cliente
            printf("ID del cliente a eliminar: ");
            scanf("%d", &id_cliente);
            eliminar_cliente(conn, id_cliente); // Llamamos a la función para eliminar cliente
            break;
        case 5:
            return; // Regresar al menú principal
        default:
            printf("Opción no válida.\n");
        }
    }
}

// Función para mostrar el registro de ventas
void ver_registro_ventas(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Consulta para obtener todas las ventas registradas
    if (mysql_query(conn, "SELECT * FROM Ventas"))
    {
        fprintf(stderr, "Error al obtener las ventas: %s\n", mysql_error(conn));
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        fprintf(stderr, "Error al obtener el resultado de la consulta: %s\n", mysql_error(conn));
        return;
    }

    printf("\n--- Registro de Ventas ---\n");
    printf("%-10s | %-10s | %-20s | %-10s\n", "ID Venta", "Cliente", "Fecha y Hora", "Total");
    printf("----------------------------------------------\n");

    // Mostrar todas las ventas
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        // Aseguramos que cada columna esté alineada adecuadamente
        printf("%-10s | %-10s | %-20s | %-10s\n", row[0], row[1], row[2], row[3]);
    }

    mysql_free_result(res);
}

// Función para manejar las Tareas pendientes
void menu_tareas()
{
    int opcion;
    // Arreglo de tareas, donde 0 es "pendiente" y 1 es "completada"
    char *tareas[] = {
        "Revisar inventario de productos",
        "Realizar pedido de medicamentos",
        "Revisar estado de ventas",
        "Limpiar y organizar la bodega"};

    int estado_tareas[] = {0, 0, 0, 0}; // 0: pendiente, 1: completada

    while (1)
    {
        printf("\n--- Tareas Pendientes ---\n");

        // Imprimir las tareas pendientes
        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s", i + 1, tareas[i]);
            if (estado_tareas[i] == 1)
            {
                printf(" (Completada)");
            }
            printf("\n");
        }

        printf("Seleccione una opción para continuar (0 para salir): ");
        scanf("%d", &opcion);

        if (opcion == 0)
        {
            printf("Regresando al menú principal...\n");
            return; // Regresa al menú principal
        }

        // Validamos si la opción seleccionada es válida
        if (opcion < 1 || opcion > 4)
        {
            printf("Opción no válida.\n");
        }
        else
        {
            // Marcamos la tarea como completada
            int indice_tarea = opcion - 1;
            if (estado_tareas[indice_tarea] == 0)
            {
                estado_tareas[indice_tarea] = 1; // Cambiar el estado a completada
                printf("¡Tarea '%s' completada!\n", tareas[indice_tarea]);
            }
            else
            {
                printf("La tarea '%s' ya está completada.\n", tareas[indice_tarea]);
            }
        }
    }
}

// Función para solicitar el login
int solicitar_login(MYSQL *conn)
{
    char nombre_usuario[50];
    char contrasenia[50];

    // Solicitar nombre de usuario y contraseña
    printf("Ingrese nombre de usuario: ");
    scanf("%s", nombre_usuario);
    printf("Ingrese contraseña: ");
    scanf("%s", contrasenia);

    // Verificar las credenciales del usuario
    if (verificar_login(conn, nombre_usuario, contrasenia))
    {
        printf("Bienvenido %s.\n", nombre_usuario);
        return 1; // Login exitoso
    }
    else
    {
        printf("Inicio de sesión fallido.\n");
        return 0; // Login fallido
    }
}

// main.c (solo se muestra la parte de inventario)
void menu_inventario(MYSQL *conn)
{
    int opcion;
    Producto producto;

    while (1)
    {
        printf("\n--- Inventario ---\n");
        printf("1. Agregar producto\n");
        printf("2. Ver productos\n");
        printf("3. Editar producto\n");
        printf("4. Eliminar producto\n");
        printf("5. Regresar al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
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
            return; // Volver al menú principal
        default:
            printf("Opción no válida.\n");
        }
    }
}

void simular_compra(MYSQL *conn, int id_cliente)
{
    Carrito carrito = {0}; // Inicializar el carrito vacío

    int id_producto, cantidad;

    // Simulación de agregar productos al carrito
    printf("Simulación de compra para el cliente ID: %d\n", id_cliente);

    while (1)
    {
        printf("Ingrese el ID del producto que desea agregar al carrito (0 para terminar): ");
        scanf("%d", &id_producto);

        if (id_producto == 0)
        {
            break; // Si se ingresa 0, terminamos de agregar productos
        }

        // Obtener la información del producto desde la base de datos
        Producto producto = obtener_producto(conn, id_producto); // Obtiene los detalles del producto
        if (producto.id_producto == 0)
        {
            printf("Producto no encontrado.\n");
            continue;
        }

        printf("Producto seleccionado: %s, Precio: %.2f\n", producto.nombre, producto.precio);

        // Pedir la cantidad de productos
        printf("Ingrese la cantidad que desea comprar: ");
        scanf("%d", &cantidad);

        // Agregar el producto al carrito
        agregar_producto_carrito(conn, &carrito, id_producto, cantidad);

        // Mostrar el carrito actualizado
        mostrar_carrito(&carrito);
    }

    // Registrar la venta con el carrito acumulado
    registrar_venta(conn, id_cliente, &carrito);
}

// Función para obtener los detalles de un producto desde la base de datos
Producto obtener_producto(MYSQL *conn, int id_producto)
{
    Producto producto = {0}; // Inicializamos el producto vacío
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    snprintf(query, sizeof(query), "SELECT id_producto, nombre, precio FROM Productos WHERE id_producto = %d", id_producto);

    if (mysql_query(conn, query))
    {
        printf("Error al ejecutar la consulta: %s\n", mysql_error(conn));
        return producto; // Retorna un producto vacío en caso de error
    }

    res = mysql_store_result(conn);
    if (res == NULL)
    {
        printf("Error al obtener el resultado: %s\n", mysql_error(conn));
        return producto; // Retorna un producto vacío si no se obtiene el resultado
    }

    row = mysql_fetch_row(res);
    if (row)
    {
        producto.id_producto = atoi(row[0]);                              // Convierte el ID del producto
        snprintf(producto.nombre, sizeof(producto.nombre), "%s", row[1]); // Copia el nombre del producto
        producto.precio = atof(row[2]);                                   // Convierte el precio a float/double
    }

    mysql_free_result(res);
    return producto;
}

void menu_ventas(MYSQL *conn)
{
    int opcion;
    int id_cliente;

    do
    {
        printf("\n=== Menu de Ventas ===\n");
        printf("1. Simular Compra\n");
        printf("2. Listar Ventas\n");
        printf("3. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese el ID del cliente: ");
            scanf("%d", &id_cliente);
            simular_compra(conn, id_cliente);
            break;
        case 2:
            listar_ventas(conn); // Llamamos a listar_ventas para ver el registro de ventas
            break;
        case 3:
            printf("Saliendo del menú de ventas...\n");
            break;
        default:
            printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 3);
}

int main()
{
    // Conectar a la base de datos
    DBConnection *db = db_connect("localhost", "root", "4613", "Farmacia", 3306);

    if (db == NULL)
    {
        fprintf(stderr, "No se pudo conectar a la base de datos.\n");
        return 1;
    }

    int opcion;
    int login_exitoso = 0;

    // Solicitar login hasta que sea exitoso
    while (!login_exitoso)
    {
        login_exitoso = solicitar_login(db->conn); // Llamamos a la función de login
    }

    // Si el login es exitoso, mostramos el menú principal
    while (1)
    {
        mostrar_menu_Principal_After_Login(); // Mostrar el menú principal

        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menu_ventas(db->conn); // Llamamos a la función de ventas
            break;
        case 2:
            menu_inventario(db->conn); // Llamamos al submenú de inventario
            break;
        case 3:
            menu_tareas(); // Llamamos a la función de tareas
            break;
        case 4:
            menu_gestion_clientes(db->conn); // Llamamos al submenú de gestión de clientes
            break;
        case 5:
            printf("Saliendo del sistema...\n");
            db_disconnect(db); // Desconectar de la base de datos
            return 0;
        default:
            printf("Opción no válida.\n");
        }
    }

    // Desconectar de la base de datos en caso de que no se haya cerrado antes
    db_disconnect(db);
    return 0;
}
