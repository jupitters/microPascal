#ifndef MP_LISTA_H
#define MP_LISTA_H
#include <stdlib.h>

typedef struct LISTA_STRUCT
{
    void** itens;
    size_t tam;
    size_t tam_item;
} lista_T;

lista_T* init_lista(size_t tam_item);

void lista_coloca(lista_T* lista, void* item);
#endif