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
        {9, 90.0, "Pelota de voleibol"},
        {10, 100.0, "Equipo de golf"},
    };

    FILE *pf = fopen("Articulos.dat", "wb");
    if (pf == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    // Escribir los artículos en el archivo
    fwrite(articulos, sizeof(Articulo), 10, pf);

    // Cerrar el archivo
    fclose(pf);

    printf("Datos guardados correctamente en Articulos.dat.\n");

    return 0;
}
