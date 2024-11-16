#include "include/lista.h"

lista_T* init_lista(size_t tam_item)
{
    lista_T* lista = calloc(1, sizeof(struct LISTA_STRUCT));
    lista->tam = 0;
    lista->tam_item = tam_item;
    lista->itens = 0;

    return lista;
}

void lista_coloca(lista_T* lista, void* item)
{
    lista->tam += 1;

    if (!lista->itens)
        lista->itens = calloc(1, lista->tam_item);
    else
        lista->itens = realloc(lista->itens, (lista->tam * lista->tam_item));

    lista->itens[lista->tam] = item;

}