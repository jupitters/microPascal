#include "include/microPascal.h"
#include "include/lexer.h"
#include "include/io.h"
#include <stdlib.h>

void comp_microPascal(char* src)
{
    lexer_T* lexer = init_lexer(src);
    token_T* tok = 0;

    while((tok = lexer_prox_token(lexer))->tipo != T_EOF)
    {
        if(tok->tipo == T_UNK)
        {
            continue;
        }
        printf("%s\n", token_to_str(tok));
    }
}

void comp_microPascal_arquivo(const char* arquivo)
{
    char* src = mp_ler_arquivo(arquivo);
    comp_microPascal(src);
    free(src);
}