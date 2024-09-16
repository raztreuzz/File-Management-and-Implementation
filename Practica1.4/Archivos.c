#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int codART;
    float precio;
    char descrip[50];

}Articulo;

int main(){

    Articulo articulos[10]={
        {1,10.0, "Pelota de futbol"},
        {2,20.0, "Raqueta de tenis"},
        {3,30.0, "Pelota de baloncesto"},
        {4,40.0, "Bicicleta"},
        {5,50.0, "Guantes de boxeo"},
        {6,60.0, "Gafas de natacion"},
        {7,70.0, "Zapatillas de correr"},
        {8,80.0, "Casco para ciclismo"},
        {7,70.0, "Pelota de voleibol"},
        {7,70.0, "Equipo de golf"},
    };

    FILE*    PF = fopen("Articulos.dat","wb");
    if (PF == NULL)
    {
        fwrite(&articulos[0], sizeof(Articulo),10,PF);
        return 0;
    }
    
}
