#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int codART;
    float precio;
    char descrip[50];

} Articulo;

int main()
{

    Articulo articulos[10] = {
        {1, 10.0, "Pelota de futbol"},
        {2, 20.0, "Raqueta de tenis"},
        {3, 30.0, "Pelota de baloncesto"},
        {4, 40.0, "Bicicleta"},
        {5, 50.0, "Guantes de boxeo"},
        {6, 60.0, "Gafas de natacion"},
        {7, 70.0, "Zapatillas de correr"},
        {8, 80.0, "Casco para ciclismo"},
        {7, 70.0, "Pelota de voleibol"},
        {7, 70.0, "Equipo de golf"},
    };

    FILE *pf = fopen("Articulos.dat", "rb"); // Abre el archivo binario "Articulos.dat" en modo de lectura ("rb") y asigna el puntero al archivo a la variable PF.
    if (pf == NULL)
    {                                            // Verifica si el archivo no se pudo abrir (es decir, si PF es NULL).
        printf("Error al abrir el archivo. \n"); // Si el archivo no se pudo abrir, imprime un mensaje de error.
    }
    Articulo aux;
    fread(&aux, sizeof(Articulo), 1, pf);  // Lee un registro de tamaño "sizeof(Articulo)" desde el archivo apuntado por PF y lo almacena en aux.
    printf("----------EL articulo solicitado es-----------    \n");
    printf("CODIGO_ARTICULO : %d \n", aux.codART);             // Imprime el código del artículo almacenado en aux.codART.
    printf("PRECIO_ARTICULO : %.2f \n", aux.precio);           // Imprime el precio del artículo almacenado en aux.precio, con dos decimales.
    printf("DESCRIPCION_ARTICULO : %-20s \n \n", aux.descrip); // Imprime la descripción del artículo con un ancho de campo de 20 caracteres, que debería estar almacenado en aux.descripcion

    return 0;
}