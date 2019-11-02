
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "packing.h"
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

int readTar(char *path)
{
    FILE *fichero;
    fichero = fopen("./empaquetado", "r");
    fclose(fichero);
    return 0;
}

int addHeader(char *data)
{
    FILE *fichero;
    fichero = fopen("./empaquetado", "a");
    fputs(data, fichero);
    fputs("\n", fichero);
    fclose(fichero);
    return 0;
}

int addContent(FILE *data)
{
    FILE *fichero;
    int data1;
    fichero = fopen("./empaquetado", "a");
    data1 = 0;
    if (data != NULL)
    {
        while ((data1 = fgetc(data)) != EOF)
        {
            fputc(data1, fichero);
        }
    }
    fputs("\n", fichero);
    fclose(data);
    fclose(fichero);
    return 0;
}

void recursive_tree(char *basePath, const int root, int n, int v)
{
    /* Se encarga de inicializar las variables que usaremos en el recorrido */
    int i;
    char path[1000];

    /* Crea un struct dirent que contiene informacion del directorio */
    struct dirent *dp;
    struct stat st;
    char str[255];
    char buff[10000];
    FILE *fichero;
    DIR *dir;
    mode_t mode;

    fichero = fopen(basePath, "r");
    if (fichero != NULL)
    {
        stat(basePath, &st);
        mode = st.st_mode;
        if (S_ISDIR(mode))
        {
        }
        else if (S_ISREG(mode) && strcmp(basePath, "./empaquetado"))
        {
            /*printf("header: %s &&& %i &&& %i &&& %i &&& %li &&& %li \n", basePath, st.st_mode, st.st_uid, st.st_gid, st.st_blocks, st.st_size);*/
            strcpy(str, basePath);
            addHeader("START HEADER");
            addHeader(str);
            sprintf(buff, "%i", st.st_mode);
            addHeader(buff);
            sprintf(buff, "%i", st.st_uid);
            addHeader(buff);
            sprintf(buff, "%i", st.st_gid);
            addHeader(buff);
            sprintf(buff, "%li", st.st_blocks);
            addHeader(buff);
            sprintf(buff, "%li", st.st_size);
            addHeader(buff);
            addHeader("END HEADER");
            addHeader("START PROGRAM");
            addContent(fichero);
            addHeader("END PROGRAM");
            return;

            fclose(fichero);
        }
        else if (n && (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISLNK(mode)))
        {
            return;
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
                        /*printf("|");*/
                    }
                    else
                    {
                        /* Espaciado para mejor identificacion */
                        /*printf(" ");*/
                    }
                }

                /* Imprime en pantalla el nombre del archivo actual */
                if (v)
                {
                    printf("packing... %s \n", dp->d_name);
                }

                /* Copia hacia la variable path el nuevo directorio base */
                strcpy(path, basePath);
                strcat(path, "/");
                strcat(path, dp->d_name);

                /* LLamada recursiva hacia el nuevo directorio hijo, trasladando el root por 2 unidades para */
                recursive_tree(path, root + 2, n, v);
            }
        }
        /* Cierra el actual directorio para liberar el espacio de memoria */
        closedir(dir);
    }
}