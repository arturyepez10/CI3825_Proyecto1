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
#include "look.h"
#include "packing.h"

/*
* Funcion: MAIN
* --------------------------
* Controla las llamadas principales del programa y que opera entre las opciones disponibles,
  para empaquetar/ desempaquetar un archivo, cifrarlo/ descifrarlo, etc. Funciona como parser para
  todos los posibles casos del uso de las funciones y operaciones.
 
* argc: La cantidad de argumentos pasados en la llamada realizada por linea
  de comandos.
* argv: Es un arreglo con todos los elementos que se pasaron en la llamada
  por linea de comandos.

* return: un entero, que significa la correcta terminacion del programa o no.
*/

int main(int argc, char **argv)
{
    /* Inicializada variable para verificar si ya existe el archivo a empaquetar */
    FILE *fichero;

    /* Se inicializan variables que se usara para crear el archivo a empaquetar */
    char newPathFile[300];
    char newPackingPathFile[300];
    char buf[10];
    char buf2[10];
    char buf3[10];
    char buf4[10];

    /* Inicializamos las variables que contendran la respuesta a si el flag
    fue invocado */
    int nflag;
    int cflag;
    int tflag;
    char vflag;

    /* Inicializamos los valores de los flags que lo requieren */
    char *fvalue;
    char *ovalue;
    char *zvalue;
    char *yvalue;
    char *xvalue;
    char *svalue;

    char *fcvalue;

    /* Se inicializa la constante que alojara al OPT y su indice */
    int index;
    int c;

    /* Valores por defecto de los flags */
    nflag = 0;
    cflag = 0;
    tflag = 0;
    vflag = 0;

    fvalue = NULL;
    ovalue = NULL;
    zvalue = NULL;
    yvalue = NULL;
    xvalue = NULL;
    svalue = NULL;

    opterr = 0;

    while ((c = getopt(argc, argv, "nctf:o:z:y:vx:s:")) != -1)
        switch (c)
        {
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

        /* Caso para el flag v - Se escribe una descripcion de lo que va haciendo */
        case 'v':
            vflag = 1;
            break;

        /* Caso para el flag f - Especifica el nombre del archivo mytar */
        case 'f':
            fvalue = optarg;
            break;

        /* Caso para el flag o - Directorio donde ira la salida de una extraccion */
        case 'o':
            ovalue = optarg;
            break;

        /* Caso para el flag z - Cifra el contenido del archivo */
        case 'z':
            zvalue = optarg;
            break;

        /* Caso para el flag y - Descifra el contenido del archivo */
        case 'y':
            yvalue = optarg;
            break;

        /* Caso para el flag x - Extrae todos los archivos */
        case 'x':
            xvalue = optarg;
            break;

        /* Caso para el flag s - Extrae el archivo en caso de existir */
        case 's':
            svalue = optarg;
            break;

        /* Cuando no es un caso atipico */
        case '?':
            if (optopt == 'f' || optopt == 'o' || optopt == 'z' || optopt == 'y' || optopt == 'x' || optopt == 's')
            {
                /* Especifica que se necesita un argumento para ciertos flags */
                fprintf(stderr, "La opcion -%c requiere un argumento.\n", optopt);
                return 1;
            }
            else if (isprint(optopt))
            {
                /* Si no es un flag conocido */
                fprintf(stderr, "Opcion desconocida `-%c'.\n", optopt);
            }
            else
            {
                fprintf(stderr, "Caracter de una opcion desconocida `\\x%x'.\n", optopt);
                return 1;
            }
        default:
            abort();
        }

    /* Avisa en el caso que una opcion sin argumento lleva uno */
    for (index = optind; index < argc; index++) 
    {
        printf("Non-option argument %s\n", argv[index]);
    }

    /* VERIFICACION DE CASO DE OPCIONES ILEGALES DE IMPLEMENTACION */
    if (cflag != 0 && xvalue != NULL)
    {
        printf("ERROR: No es valido extraer un archivo/directorio en especifico de un archivo/directorio por empaquetar.");
    }
    else if (svalue != NULL && xvalue != NULL)
    {
        printf("ERROR: No se puede extraer un archivo/directorio en especifico y a su vez todo el archivo empaquetado.");
    }
    else if (cflag != 0 && svalue != NULL)
    {
        printf("ERROR: No se puede extraer un archivo/directorio que no se ha empaquetado.");
    }
    else if (zvalue != NULL && svalue != NULL)
    {
        printf("ERROR: No se puede extraer un archivo/directorio cifrado.");
    }
    else if (cflag != 0 && ovalue != NULL)
    {
        printf("ERROR: No se puede colocar la salida de extraccion a un archivo/directorio que se va a comprimir");
    }
    else if (cflag != 0 && yvalue != NULL)
    {
        printf("ERROR: No se puede descifrar un archivo/directorio por empaquetar, que no esta cifrado.");
    }
    else if (zvalue != NULL && yvalue != NULL && zvalue == yvalue)
    {
        printf("ERROR: Desplazar izquierda y derecha en mismas cantidades resulta en un archivo/directorio no cifrado.");
    }
    else if (tflag != 0 && zvalue != NULL)
    {
        printf("ERROR: No se puede mostrar el contenido de un archivo cifrado.");
    }

    /* IMPLEMENTACION DE OPCIONES */
    
    /* En el caso donde la opcion 'f' sea pase como argumento */
    if (fvalue != NULL) {

        /* Manipula el valor de f y asigna la direccion correspondiente del archivo donde se empaquetara */
        strcpy(buf, " ");
        buf[0] = fvalue[0];
        strcpy(buf2, " ");
        buf2[0] = fvalue[1];

        /* Se encarga de separar el argumento de f y luego chequea si lo tiene */
        fcvalue = strtok(fvalue, "_");
        fcvalue = strtok(NULL, "_");
        

        /* Manipula el 2do valor de f y asigna la direccion correspondiente del archivo donde se empaquetara
           en caso de contar si quiera con un 2do argumento */
        if (fcvalue != NULL)
        {
            strcpy(buf3, " ");
            buf3[0] = fcvalue[0];
                
            strcpy(buf4, " ");
            buf4[0] = fcvalue[1];
        }

        /* Manipula el argumento del valor de f para identificar si es una direccion absoluta o relativa y 
           hacer asignaciones correspondientes segun sea el caso */
        if (strcmp(buf2, "/") != 0 && strcmp(buf, ".") != 0 && strcmp(buf, "/") != 0)
        {
            strcpy(newPathFile, "./");
            strcat(newPathFile, fvalue);
        }
        else if (strcmp(buf, "/") == 0)
        {
            strcpy(newPathFile, fvalue);
        }
        else if (strcmp(buf, ".") == 0 && strcmp(buf2, "/") == 0)
        {
            strcpy(newPathFile, fvalue);
        }

        /* Manipula el argumento del valor del segundo argumento de f (en caso de tenerlo) para identificar 
           si es una direccion absoluta o relativa y hacer asignaciones correspondientes segun sea el caso */
        if (strcmp(buf4, "/") != 0 && strcmp(buf3, ".") != 0 && strcmp(buf3, "/") != 0 && fcvalue != NULL)
        {
            strcpy(newPackingPathFile, "./");
            strcat(newPackingPathFile, fcvalue);
        }
        else if (strcmp(buf3, "/") == 0 && fcvalue != NULL)
        {
            strcpy(newPackingPathFile, fcvalue);
        }
        else if (strcmp(buf3, ".") == 0 && fcvalue != NULL)
        {
            strcpy(newPackingPathFile, fcvalue);
        }

        /* Si no posee un 2do argumento, simplemente asigna a la variable del archivo a empaquetar como el directorio
           raiz */
        if (fcvalue == NULL)
        {
            strcpy(newPackingPathFile, ".");
        }

        /* Se abre el archivo fichero para verificar si existe */
        fichero = fopen(newPathFile, "r");
        
        /* SEGUN LA MEZCLA CON OTROS FLAGS */
        if (cflag != 0)
        {   
            /* Verifica que el archivo que se desea empaquetar no exista, y si existe lo sobreescribe */
            if (fichero != NULL) {
                fichero = fopen(newPathFile, "w+");
            }

            /* Empaqueta el archivo/directorio en cuestion sin especificar por terminal que se realiza */
            packing(newPackingPathFile, newPathFile, 1, 0, vflag); 
        }
        
        else if (tflag != 0)
        {   
            /* */
            packedInfo(newPathFile);
        }
    }

    return 0;
}