#ifndef MP_H
#define MP_H
#include "token.h"

void comp_microPascal(char* src);
void comp_microPascal_arquivo(const char* arquivo);
token_T *alloc_token();
token_T *token_add_lista(token_T *lista, token_T *token, int indice);
token_T *buscarToken(token_T *token, token_T *lista);
void liberar(token_T *lista);

#endif