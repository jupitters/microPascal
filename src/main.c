#include "include/microPascal.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        printf("Coloque o arquivo de entrada.\n");
        return 1;
    }

    comp_microPascal_arquivo(argv[1]);

    return 0;
}