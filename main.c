/*
*  PROYECTO 1
*  Alumno: Arturo Yepez 15-11551
*          Samuel Fagundez 15-10460

*  Descripcion: 
*/


/* LIBRERIAS QUE UTILIZA MAIN.C */
#include <stdio.h>
#include <ctype.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

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
        switch (c)
        {
        case 'n':
            nflag = 1;
            break;
        case 'c':
            cflag = 1;
            break;
        case 't':
            tflag = 1;
            break;
        case 'f':
            fvalue = optarg;
            printf ("outarg: '%s'\n", fvalue);
            break;
        case 'o':
            ovalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case 'z':
            zvalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case 'y':
            yvalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case 'v':
            vvalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case 'x':
            xvalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case 's':
            svalue = optarg;
            printf ("outarg: '%s'\n", optarg);
            break;
        case '?':
            if (optopt == 'f' || optopt == 'o' || optopt == 'z' || optopt == 'y'|| optopt == 'v' || optopt == 'x' || optopt == 's') {
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            }
            else if (isprint (optopt)) {
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            } else {
            fprintf (stderr,
                    "Unknown option character `\\x%x'.\n", optopt);
            return 1;
            }
        default:
            abort ();
        }

    /* printf ("aflag = %d, bflag = %d, cvalue = %s\n",
           aflag, bflag, cvalue); */

    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);
    return 0;
}