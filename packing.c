
/* LIBRERIAS DEL SISTEMA QUE UTILIZA PACK.C */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>


/*
* Funcion: recursiveTree
* --------------------------
* Encargada de hacer un recorrido por todo el arbol de directorio y de archivos, es decir,
  pasando por cada archivo/directorio dentro de una direccion en especifico.
 
* basePath: La direccion base por la que comenzara el recorrido del arbol
* root: Un entero que representa el nivel del arbol.

* return: nada.
*/

void recursive_tree(char *basePath, const int root) {
    /* Se encarga de inicializar las variables que usaremos en el recorrido */
    int i;
    char path[1000];

    /* Crea un struct dirent que contiene informacion del directorio */
    struct dirent *dp;

    /* Abre el directorio con la direccion especifica */
    DIR *dir = opendir(basePath);

    /* Si no existe tal directorio entonces se sale de la funcion */
    if (!dir) {
        return;
    }

    /* Mientras existe un apuntador que devuelva readdir(), se seguira en el ciclo */
    while ((dp = readdir(dir)) != NULL) {
        /* Mientras el directorio no sea el base, realiza unas actividades especiales para una correcta impresion */
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            for (i = 0; i < root; i++) {
                if ( i%2 == 0 || i == 0) {
                    /* Identificador de que entra en una carpeta */
                    printf("|");
                } else {
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


/* SOLO CON MOTIVOS DE PRUEBAS */
int test_main() {
    /* Variable donde se almacenara el input del usuario */
    char path[100];

    /* Se recolecta respuesta del usuario */
    printf("Direccion del directorio: ");
    scanf("%s", path);

    /* Llamada a la funcion */
    recursive_tree(path, 0);

    return 0;
}
