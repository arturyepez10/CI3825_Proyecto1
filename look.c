
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

/* LIBRERIAS PERSONALES QUE UTILIZA LOOK.C */
#include "packing.h"

/*
* Funcion:
* --------------------------
* 
 
* basePath: 
* root:

* return: 
*/

int readTar(char *path, char *filename)
{
    /* Inicializado archivo que se leera */
    FILE *fichero;

    /* Variables de buffer */
    char buf[10000];
    char buf2[10000];

    /* Se inicializan variables que tendran la informacion del archivo */
    char *fileAddress;
    char *mode;
    int intMode;
    char *permissions;
    char *userId;
    char *fileSize;

    /* Contador de memoria total en bytes */
    int counter;

    /* Reserva de memoria para copiar archivos del buffer */
    fileAddress = malloc(100 * sizeof(char));
    mode = malloc(100 * sizeof(char));
    permissions = malloc(100 * sizeof(char));
    userId = malloc(100 * sizeof(char));
    fileSize = malloc(100 * sizeof(char));

    /* Abierto archivo empaquetado */
    fichero = fopen(filename, "r");

    counter = 0;

    /* Ciclo que se encarga de recorre todo el archivo abierto */
    while (fscanf(fichero, "%s", buf) != -1)
    {
        /* Vacia todo el buffer 2 */
        strcpy(buf2, "");

        if (strcmp(buf, "STARTHEADER") == 0)
        {
            /* Si encuentra el comienzo de un header */

            /* Copio la variable del nombre de la direccion y la manipulo */
            fscanf(fichero, "%s", buf);
            strcpy(fileAddress, buf);

            /* Copio la variable del mode y luego la pasa a entero*/
            fscanf(fichero, "%s", buf);     
            strcpy(mode, buf);
            intMode = atoi(mode);

            /* Todos los datos de permisologia extraidos del mode los agrega a la variable de permisos */
            strcpy(permissions ,(S_ISDIR(intMode)) ? "d" : "-");
            strcat(permissions ,(intMode & S_IRUSR) ? "r" : "-");
            strcat(permissions ,(intMode & S_IWUSR) ? "w" : "-");
            strcat(permissions ,(intMode & S_IXUSR) ? "x" : "-");
            strcat(permissions ,(intMode & S_IRGRP) ? "r" : "-");
            strcat(permissions ,(intMode & S_IWGRP) ? "w" : "-");
            strcat(permissions ,(intMode & S_IXGRP) ? "x" : "-");
            strcat(permissions ,(intMode & S_IROTH) ? "r" : "-");
            strcat(permissions ,(intMode & S_IWOTH) ? "w" : "-");
            strcat(permissions ,(intMode & S_IXOTH) ? "x" : "-");

            /* Verifica si el archivo es un link simbolico */
            strcat(permissions, " ");
            strcat(permissions, (S_ISLNK(intMode)) ? "l" : "-");

            /* Copia el user id del usuario */
            fscanf(fichero, "%s", buf);
            strcpy(userId, buf);

            /* Copio el tamaño del archivo */
            fscanf(fichero, "%s", buf); 
            fscanf(fichero, "%s", buf); 
            fscanf(fichero, "%s", buf); 
            strcpy(fileSize, buf);
            counter += atoi(fileSize);

            /* Al final, se agrega en un orden especifico al buffer 2 */
            strcat(buf2, " ");
            strcat(buf2, permissions);
            strcat(buf2, " ");
            strcat(buf2, userId);
            strcat(buf2, " ");
            strcat(buf2, fileSize);
            strcat(buf2, "     \t ");
            strcat(buf2, fileAddress);
            strcat(buf2, "\n");        
        }
        /* Imprime todo el buffer2 antes de reiniciar el ciclo */
        printf("%s", buf2);
    }
    printf("\nTotal bytes of files packed: %i\n", counter);

    /* Se libera la memoria guardada con malloc */
    free(fileAddress);
    free(mode);
    free(userId);
    free(fileSize);

    /* Se cierra archivo abierto */
    fclose(fichero);

    return 0;
}

/*
* Funcion:
* --------------------------
* 
 
* basePath: 
* root:

* return: 
*/

int addHeader(char *data, char *filename)
{
    FILE *fichero;
    fichero = fopen(filename, "a");
    fputs(data, fichero);
    fputs("\n", fichero);
    fclose(fichero);
    return 0;
}

/*
* Funcion:
* --------------------------
* 
 
* basePath: 
* root:

* return: 
*/

int addContent(FILE *data, char *filename)
{
    FILE *fichero;
    int data1;
    fichero = fopen(filename, "a");
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

/*
* Funcion: recursiveTree
* --------------------------
* Encargada de hacer un recorrido por todo el arbol de directorio y de archivos, es decir,
  pasando por cada archivo/directorio dentro de una direccion en especifico.
 
* basePath: La direccion base por la que comenzara el recorrido del arbol
* filename
* root: Un entero que representa el nivel del arbol.
* n: Es el identificador del flag n
* v: Es el identificador del flag v

* return: nada.
*/

void recursive_tree(char *basePath, char *filename,const int root, int n, int v)
{
    /* Se encarga de inicializar las variables que usaremos en el recorrido */
    int i;
    char path[1000];
    char str[255];
    char buff[10000];

    /* Crea un struct dirent que contiene informacion del directorio */
    struct dirent *dp;

    /* Inicializan variables para poder conocer informacion del archivo */
    struct stat st;
    mode_t mode;

    /* Se crea variable que contendra el archivo a empaquetar */
    FILE *fichero;

    /* Inicializa directorios a recorrer */
    DIR *dir;

    /* Abre lo que se encuentre en la direccion que se pasa por argumento */
    fichero = fopen(basePath, "r");
    if (fichero != NULL)
    {   
        /* Consigue el stat de lo que pasamos como argumento y lo linkea a nuestra variable personal creada para el caso */
        stat(basePath, &st);

        /* Encuentra el mode, para verificar que tipo de archivo tenemos a la mano */
        mode = st.st_mode;

        if (S_ISDIR(mode))
        {
            /* Si es directorio */
        }
        else if (S_ISREG(mode) && strcmp(basePath, filename))
        {
            /* Si es archivo regular y si el archivo a empaquetar no es una version de si mismo */

            /* Copia la direccion del path en un string */
            strcpy(str, basePath);

            /* Comienza el copiado del header en el archivo a empaquetar */
            addHeader("STARTHEADER", filename);

            /* Agrega direccion relativa del archivo o directorio */
            addHeader(str, filename);

            /* Agrega el modo del archivo */
            sprintf(buff, "%i", st.st_mode);
            addHeader(buff, filename);

            /* Agrega el id de usuario dueño */
            sprintf(buff, "%i", st.st_uid);
            addHeader(buff, filename);

            /* Agrega el id del grupo dueño */
            sprintf(buff, "%i", st.st_gid);
            addHeader(buff, filename);

            /* Agrega el numero de bloques de 512 bytes guardados en memoria */
            sprintf(buff, "%li", st.st_blocks);
            addHeader(buff, filename);

            /* Agrega el tamaño del archivo en bytes */
            sprintf(buff, "%li", st.st_size);
            addHeader(buff, filename);
            addHeader("ENDHEADER", filename);

            /* Copia toda la data del archivo en el paquete */
            addHeader("STARTPROGRAM", filename);
            addContent(fichero, filename);
            addHeader("ENDPROGRAM", filename);
            return;

            fclose(fichero);
            return;
        }
        else if (n && (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISLNK(mode)))
        {
            /* Si es */
            return;
        }
        else if (fichero == NULL)
        {   
            /* Si no existe ningun archivo o directorio con ese nombre */
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

                /* LLamada recursiva hacia el nuevo directorio hijo, trasladando el root por 2 */
                recursive_tree(path, filename,root + 2, n, v);
            }
        }
        /* Cierra el actual directorio para liberar el espacio de memoria */
        closedir(dir);
    }
}