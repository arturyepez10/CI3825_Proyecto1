
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

/*
* Funcion:
* --------------------------
* 
 
* basePath: 
* root:

* return: 
*/

int packedInfo(char *filename)
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
    char *username;
    char *groupname;
    char *fileSize;

    /* Contador de memoria total en bytes */
    int counter;

    /* Reserva de memoria para copiar archivos del buffer */
    fileAddress = malloc(100 * sizeof(char));
    mode = malloc(100 * sizeof(char));
    permissions = malloc(100 * sizeof(char));
    username = malloc(100 * sizeof(char));
    groupname = malloc(100 * sizeof(char));
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
            strcpy(permissions, (S_ISDIR(intMode)) ? "d" : "-");
            strcat(permissions, (intMode & S_IRUSR) ? "r" : "-");
            strcat(permissions, (intMode & S_IWUSR) ? "w" : "-");
            strcat(permissions, (intMode & S_IXUSR) ? "x" : "-");
            strcat(permissions, (intMode & S_IRGRP) ? "r" : "-");
            strcat(permissions, (intMode & S_IWGRP) ? "w" : "-");
            strcat(permissions, (intMode & S_IXGRP) ? "x" : "-");
            strcat(permissions, (intMode & S_IROTH) ? "r" : "-");
            strcat(permissions, (intMode & S_IWOTH) ? "w" : "-");
            strcat(permissions, (intMode & S_IXOTH) ? "x" : "-");

            /* Verifica si el archivo es un link simbolico */
            strcat(permissions, " ");
            strcat(permissions, (S_ISLNK(intMode)) ? "l" : "-");

            /* Copia el username dueño del archivo */
            fscanf(fichero, "%s", buf);
            strcpy(username, buf);

            /* Copio el nombre del grupo del usuario */
            fscanf(fichero, "%s", buf);
            strcpy(groupname, buf);

            /* Copio el tamaño del archivo */
            fscanf(fichero, "%s", buf);
            fscanf(fichero, "%s", buf);
            strcpy(fileSize, buf);
            counter += atoi(fileSize);

            /* Al final, se agrega en un orden especifico al buffer 2 */
            strcat(buf2, " ");
            strcat(buf2, permissions);
            strcat(buf2, " ");
            strcat(buf2, username);
            strcat(buf2, " ");
            strcat(buf2, groupname);
            strcat(buf2, " ");
            strcat(buf2, fileSize);
            strcat(buf2, "      \t ");
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
    free(username);
    free(groupname);
    free(fileSize);

    /* Se cierra archivo abierto */
    fclose(fichero);

    return 0;
}
