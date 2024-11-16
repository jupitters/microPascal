#include "include/tipos.h"
#include <string.h>

int tipo_p_int(const char* nome)
{
    int t = 0;
    size_t len = strlen(nome);

    for (unsigned int i = 0; i < len; i++)
        t += nome[i]; 

    return t;
}