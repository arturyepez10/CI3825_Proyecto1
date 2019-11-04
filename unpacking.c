
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define _POSIX_SOURCE

#define MAX1 100000

/*
* Funcion:
* --------------------------
* 
 
* basePath: 
* root:

* return: 
*/

int unpacking(char *filename)
{
    /* Inicializado archivo que se leera */
    FILE *fichero;
    FILE *fichero2;
    int data1;

    /* Variables de buffer */
    char buf[MAX1];
    char buf2[MAX1];

    /* Se inicializan variables que tendran la informacion del archivo */
    char *fileAddress;
    char *mode;
    int intMode;
    char *username;
    char *groupname;

    /* Contador de memoria total en bytes */

    /* Reserva de memoria para copiar archivos del buffer */
    fileAddress = malloc(100 * sizeof(char));
    mode = malloc(100 * sizeof(char));
    username = malloc(100 * sizeof(char));
    groupname = malloc(100 * sizeof(char));

    /* Abierto archivo empaquetado */
    fichero = fopen(filename, "r");

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

            /* Copia el username dueño del archivo */
            fscanf(fichero, "%s", buf);
            strcpy(username, buf);

            /* Copio el nombre del grupo del usuario */
            fscanf(fichero, "%s", buf);
            strcpy(groupname, buf);
        }
        creat(filename, S_IRWXU);
        fichero2 = fopen(filename, "w");
        data1 = 0;
        if (fichero2 != NULL)
        {
            while ((data1 = fgetc(fichero)) != EOF)
            {
                fputc(data1, fichero2);
            }
        }
        chmod(filename, intMode);
        fclose(fichero2);
    }

    /* Se libera la memoria guardada con malloc */
    free(fileAddress);
    free(mode);
    free(username);
    free(groupname);

    /* Se cierra archivo abierto */
    fclose(fichero);

    return 0;
}
