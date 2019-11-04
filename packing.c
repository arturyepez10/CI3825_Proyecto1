
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACKING.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>

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

void packing(char *basePath, char *filename, const int root, int n, int v)
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
    struct passwd *pws;
    struct group *grp;
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
            strcpy(str, basePath);

            /* Comienza el copiado del header en el archivo a empaquetar */
            addHeader("STARTHEADER", filename);

            /* Agrega direccion relativa del archivo o directorio */
            addHeader(str, filename);

            /* Agrega el modo del archivo */
            sprintf(buff, "%i", st.st_mode);
            addHeader(buff, filename);

            /* Agrega el username del dueño del archivo */
            pws = getpwuid(st.st_uid);
            sprintf(buff, "%s", pws->pw_name);
            addHeader(buff, filename);

            /* Agrega el id del grupo dueño */
            grp = getgrgid(st.st_gid);
            sprintf(buff, "%s", grp->gr_name);
            addHeader(buff, filename);

            /* Agrega el numero de bloques de 512 bytes guardados en memoria */
            sprintf(buff, "%li", st.st_blocks);
            addHeader(buff, filename);

            /* Agrega el tamaño del archivo en bytes */
            sprintf(buff, "%li", st.st_size);
            addHeader(buff, filename);
            addHeader("ENDHEADER", filename);
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

            /* Agrega el username del dueño del archivo */
            pws = getpwuid(st.st_uid);
            sprintf(buff, "%s", pws->pw_name);
            addHeader(buff, filename);

            /* Agrega el id del grupo dueño */
            grp = getgrgid(st.st_gid);
            sprintf(buff, "%s", grp->gr_name);
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
        }
        else if (n && S_ISLNK(mode))
        {
            /* Si es link */
            /* Copia la direccion del path en un string */
            strcpy(str, basePath);

            /* Comienza el copiado del header en el archivo a empaquetar */
            addHeader("STARTHEADER", filename);

            /* Agrega direccion relativa del archivo o directorio */
            addHeader(str, filename);

            /* Agrega el modo del archivo */
            sprintf(buff, "%i", st.st_mode);
            addHeader(buff, filename);

            /* Agrega el username del dueño del archivo */
            pws = getpwuid(st.st_uid);
            sprintf(buff, "%s", pws->pw_name);
            addHeader(buff, filename);

            /* Agrega el id del grupo dueño */
            grp = getgrgid(st.st_gid);
            sprintf(buff, "%s", grp->gr_name);
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
        }
        else if (n && (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISLNK(mode)))
        {
        }
        else if (fichero == NULL)
        {
            /* Si no existe ningun archivo o directorio con ese nombre */
        }

        fclose(fichero);

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
                packing(path, filename, root + 2, n, v);
            }
        }
        /* Cierra el actual directorio para liberar el espacio de memoria */
        closedir(dir);
    }
}