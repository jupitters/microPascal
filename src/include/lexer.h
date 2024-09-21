#ifndef MP_LEXER_H
#define MP_LEXER_H
#include "token.h"
#include <stdio.h>

typedef struct LEXER_STRUCT
{
    char* src;
    size_t src_tam;
    char c;
    unsigned int i;
    int lin;
    int col;
} lexer_T;

lexer_T* init_lexer(char* src);

void lexer_avanco(lexer_T* lexer);

char lexer_peek(lexer_T* lexer, int offset);

token_T* lexer_avanco_com(lexer_T* lexer, token_T* token);

token_T* lexer_avanco_momento(lexer_T* lexer, int tipo);

void lexer_espaco(lexer_T* lexer);

token_T* lexer_parse_id(lexer_T* lexer);

token_T* lexer_parse_duploSinal(lexer_T* lexer, int tipo);

token_T* lexer_parse_numero(lexer_T* lexer);

token_T* lexer_prox_token(lexer_T* lexer);
#endif