#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{

    int codArt;
    float precio;
    char descrip[50];

} Articulo;

void mostrarArticulo(void *dato);
void mostrarArchivo(const char *nombre);
int generarArchivo(const char *nombre);

void actualizarPrecios(const char *nombre, int cantRegistros)
{
    FILE *arch = fopen(nombre, "r+b");

    if (arch == NULL)
    {
        printf("Error al abrir el archivo.\n", nombre);
        return;
    }

    Articulo aux;
    int i;
    unsigned tam = sizeof(Articulo);

    for (i = 0; i < cantRegistros; i++)
    {
        fflush(arch);
        fread(&aux, tam, 1, arch);
        aux.precio *= 1.10;
        fseek(arch, -tam, SEEK_CUR);
        fwrite(&aux, tam, 1, arch);
    }

    fclose(arch);
}

int main(){

    int cantRegistros;
    cantRegistros = generarArchivo("Articulos2.dat");
    mostrarArchivo("Articulos2.dat");
    actualizarPrecios("Articulos2.dat", cantRegistros);
    mostrarArchivo("Articulos2.dat");
    return 0;
}
