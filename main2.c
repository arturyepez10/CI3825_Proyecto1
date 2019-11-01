/*
*  PROYECTO 1
*  Alumno: Arturo Yepez 15-11551
*          Samuel Fagundez 15-10460

*  Descripcion: 
*/


/* LIBRERIAS DEL SISTEMA QUE UTILIZA MAIN.C */
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

/* LIBRERIAS PERSONALES QUE UTILIZA MAIN.C */
#include "encrypted.h"
#include "packing.h"

/*
* Funcion: MAIN
* --------------------------
* Controla las llamadas principales del programa y que opera entre las opciones disponibles,
  para empaquetar/ desempaquetar un archivo, cifrarlo/ descifrarlo, etc [ARREGLAR xd]
 
* argc: La cantidad de argumentos pasados en la llamada realizada por linea
  de comandos.
* argv: Es un arreglo con todos los elementos que se pasaron en la llamada
  por linea de comandos.

* return: un entero, que significa la correcta terminacion del programa o no.
*/

int main (int argc, char **argv) {
    /* Inicializamos las variables que contendran la respuesta a si el flag
    fue invocado */
    int nflag = 0;
    int cflag = 0;
    int tflag = 0;

    /* Inicializamos los valores de los flags que lo requieren */
    char *fvalue = NULL;
    char *ovalue = NULL;
    char *zvalue = NULL;
    char *yvalue = NULL;
    char *vvalue = NULL;
    char *xvalue = NULL;  
    char *svalue = NULL;   
    
    /* Se inicializa la constante que alojara al OPT y su indice */
    int index;
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "nctf:o:z:y:v:x:s:")) != -1)
        switch (c) {
            /* Caso para el flag n - Ignora todo archivo o directorio que no sea regular */
            case 'n':
                nflag = 1;
                break;
            
            /* Caso para el flag c - permite crear el mytar, si existe lo sobreescribe */
            case 'c':
                cflag = 1;
                break;
            
            /* Caso para el flag t - muestra el contenido del mytar */
            case 't':
                tflag = 1;
                break;

            /* Caso para el flag f - Especifica el nombre del archivo mytar */
            case 'f':
                fvalue = optarg;
                printf ("outarg: '%s'\n", fvalue);
                break;
            
            /* Caso para el flag o - Directorio donde ira la salida de una extraccion */
            case 'o':
                ovalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;

            /* Caso para el flag z - Cifra el contenido del archivo */
            case 'z':
                zvalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;

            /* Caso para el flag y - Descifra el contenido del archivo */
            case 'y':
                yvalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;

            /* Caso para el flag v - Se escribe una descripcion de lo que va haciendo */
            case 'v':
                vvalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;
            
            /* Caso para el flag x - Extrae todos los archivos */
            case 'x':
                xvalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;

            /* Caso para el flag s - Extrae el archivo en caso de existir */
            case 's':
                svalue = optarg;
                printf ("outarg: '%s'\n", optarg);
                break;

            /* Cuando no es un caso atipico */
            case '?':
                if (optopt == 'f' || optopt == 'o' || optopt == 'z' || optopt == 'y'|| optopt == 'v' || optopt == 'x' || optopt == 's') {
                    /* Especifica que se necesita un argumento para ciertos flags */
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);

                } else if (isprint (optopt)) {
                    /* Si no es un flag conocido */
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);

                } else {
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                    return 1;

                }
            default:
                abort ();
        }

    /* Avisa en el caso que una opcion sin argumento lleva uno */
    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    return 0;
}