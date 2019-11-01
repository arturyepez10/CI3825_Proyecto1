#include <stdio.h>
#include <stdlib.h>
#include "encrypted.h"
#include "look.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    FILE *fichero;
    fichero = fopen("./empaquetado", "w+");
    fclose(fichero);
    recursive_tree(".", 0);
    return 0;
}