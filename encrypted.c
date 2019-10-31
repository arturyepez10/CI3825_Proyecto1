
/* LIBRERIAS QUE UTILIZA ENCRYPTED.C */
#include <stdio.h>

/* CONSTANTES DEFINIDA PARA EL MAXIMO ARREGLO DE BITS */
#define INT_BITS 32 
  
/*
* Funcion: rotarIzquierda
* --------------------------
* Es la funcion encargada de rotar una cadena de bytes y sus respectivos bits, la rotacion esta
  destinada hacia el lado izquierdo. Usada para cifrar/descifrar un archivo. Este planteamiento
  asegura que la operacion sera realizada de forma circular, de manera que si algun elemento
  se sale de la cantidad maxima permitida de bits, sera asignado hacia el otro lado de la cadena.
 
* n: Es el numero entero para el que se rotara en una cantidad dada por nuestra otra
  variable.
* rotacion: Es el numero entero que representa la cantidad de bits que rodaran hacia la izquierda.

* return: un entero, cuya cadena de bits fue rotada en una cantidad dada por el argumento rotacion 
  hacia la izquierda.
*/

int rotarIzquierda(int n, unsigned int rotacion) { 
   /* 
      En el caso de n << rotacion los numeros son rotados hacia la izquierda en una cantidad dada por
      rotacion, luego los bits que se salieron del maximo permitido son reinsertados hacia
      con una rotacion hacia la derecha con n >> (INT_BITS - rotacion)
    */
    return (n << rotacion)|(n >> (INT_BITS - rotacion)); 
} 

/*
* Funcion: rotarDerecha
* --------------------------
* Es la funcion encargada de rotar una cadena de bytes y sus respectivos bits, la rotacion esta
  destinada hacia el lado derecha. Usada para cifrar/descifrar un archivo. Este planteamiento
  asegura que la operacion sera realizada de forma circular, de manera que si algun elemento
  se sale de la cantidad maxima permitida de bits, sera asignado hacia el otro lado de la cadena.
 
* n: Es el numero entero para el que se rotara en una cantidad dada por nuestra otra
  variable.
* rotacion: Es el numero entero que representa la cantidad de bits que rodaran hacia la derecha.

* return: un entero, cuya cadena de bits fue rotada en una cantidad dada por el argumento rotacion 
  hacia la derecha.11
*/

int rotarDerecha(int n, unsigned int rotacion) { 
    /* 
      En el caso de n >> rotacion los numeros son rotados hacia la derecha en una cantidad dada por
      rotacion, luego los bits que se salieron del maximo permitido son reinsertados hacia
      con una rotacion hacia la izquierda con n << (INT_BITS - rotacion)
    */
    return (n >> rotacion)|(n << (INT_BITS - rotacion)); 
}