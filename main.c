#include <stdio.h>
#include <stdlib.h>
#include "encrypted.h"
#include <stdbool.h>
#include "look.h"

int main(int argc, char *argv[])
{
    FILE *fichero;
    fichero = fopen("./empaquetado", "w+");
    fclose(fichero);
    recursive_tree(1, ".", 0);
    return 0;
}