
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "packing.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*
* Funcion: recursiveTree
* --------------------------
* Encargada de hacer un recorrido por todo el arbol de directorio y de archivos, es decir,
  pasando por cada archivo/directorio dentro de una direccion en especifico.
 
* basePath: La direccion base por la que comenzara el recorrido del arbol
* root: Un entero que representa el nivel del arbol.

* return: nada.
*/

int addContent(char *data)
{
    FILE *fichero;
    fichero = fopen("./empaquetado", "a");
    fwrite(data, sizeof(data), 1, fichero);
    fclose(fichero);
}

void recursive_tree(char *basePath, const int root)
{
    /* Se encarga de inicializar las variables que usaremos en el recorrido */
    int i;
    char path[1000];

    /* Crea un struct dirent que contiene informacion del directorio */
    struct dirent *dp;
    struct stat st;
    char *cpy;
    char *cpy2;
    FILE *fichero;
    DIR *dir;
    mode_t mode;

    struct header
    {
        char *path;
        long int perms;
        int type;
        char *owner;
        char *group;
        int blocks;
    };
    typedef struct header Header;
    Header *newHeader;
    newHeader = NULL;
    fichero = fopen(basePath, "r");
    if (fichero != NULL)
    {
        stat(basePath, &st);
        mode = st.st_mode;
        if (S_ISDIR(mode))
        {
            printf("Es carpeta, continuemos \n");
        }
        else if (S_ISREG(mode))
        {
            printf("Es archivo hagamos algo diferente \n");
            newHeader = (Header *)malloc(sizeof(Header));
            strcpy(newHeader->path, basePath);
            addContent(newHeader->path);
            return;
        }
        fclose(fichero);
    }
    else if (fichero == NULL)
    {
        return;
    }

    /* Abre el directorio con la direccion especifica */
    dir = opendir(basePath);

    /* Si no existe tal directorio entonces se sale de la funcion */
    if (dir == NULL)
    {
        return;
    }

    /* Mientras existe un apuntador que devuelva readdir(), se seguira en el ciclo */
    while ((dp = readdir(dir)) != NULL)
    {
        /* Mientras el directorio no sea el base, realiza unas actividades especiales para una correcta impresion */
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            for (i = 0; i < root; i++)
            {
                if (i % 2 == 0 || i == 0)
                {
                    /* Identificador de que entra en una carpeta */
                    printf("|");
                }
                else
                {
                    /* Espaciado para mejor identificacion */
                    printf(" ");
                }
            }

            /* Imprime en pantalla el nombre del archivo actual */
            printf("|- %s\n", dp->d_name);

            /* Copia hacia la variable path el nuevo directorio base */
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            /* LLamada recursiva hacia el nuevo directorio hijo, trasladando el root por 2 unidades para */
            recursive_tree(path, root + 2);
        }
    }
    /* Cierra el actual directorio para liberar el espacio de memoria */
    closedir(dir);
}