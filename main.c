#include <stdio.h>
#include <stdlib.h>
#include "encrypted.h"
#include <stdbool.h>
#include "look.h"
#include <string.h>

int main(int argc, char *argv[])
{
    /* Se inicializa fichero que se usara para crear el archivo a empaquetar*/
    char newPath[300];
    char buf[10];
    char buf2[10];

    /* Manipula los argumentos y asigna valores correspondientes */
    strcpy(buf, " ");
    buf[0] = argv[1][0];
    
    strcpy(buf2, " ");
    buf2[0] = argv[1][1];

    if (strcmp(buf2, "/") != 0 && strcmp(buf2, ".") != 0 && strcmp(buf, "/") != 0)
    {
        strcpy(newPath, "./");
        strcat(newPath, argv[1]);
    }

    else if (strcmp(buf, "/") == 0)
    {
        strcpy(newPath, argv[1]);
    }
    else if (strcmp(buf, ".") == 0 && strcmp(buf2, "/") == 0)
    {
        strcpy(newPath, argv[1]);
    }

    printf("%s \n", newPath);

    recursive_tree(".", newPath, 1, 0, 1);

    /* readTar(".", newPath); */
    return 0;
}