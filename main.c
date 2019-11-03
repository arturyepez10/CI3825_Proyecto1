#include <stdio.h>
#include <stdlib.h>
#include "encrypted.h"
#include <stdbool.h>
#include "look.h"

int main(int argc, char *argv[])
{  
    /* Se inicializa fichero que se usara para crear el archivo a empaquetar*/
    FILE *fichero;

    /* Variable que contiene nombre de  */
    char filename[100];

    /* Recupera la respuesta del usuario */
    printf( "Enter a value: ");
    scanf("%s", filename);

    printf( "\nYou entered: %s \n", filename);

    /* Abre y crea el archivo */
    fichero = fopen(filename, "w+");
    fclose(fichero);

    /* Empaqueta el archivo */
    recursive_tree(".", filename, 1, 0, 1);

    readTar(".", filename);
    return 0;
}