#ifndef MP_IO_H
#define MP_IO_H
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "lexer.h"
size_t getline(char **lineptr, size_t *n, FILE *stream);
char* mp_ler_arquivo(const char* nomeArquivo);
void mp_escrita_tokens(token_T* token, lexer_T* lexer);
#endif