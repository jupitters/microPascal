#include "include/AST.h"
#include <stdlib.h>

AST_T* init_ast(int tipo)
{
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->tipo = tipo;

    if (tipo == AST_COMPOSICAO)
        ast->children = init_lista(sizeof(struct AST_STRUCT*));

    if (tipo == AST_VARIAVEL)
        ast->children = init_lista(sizeof(struct AST_STRUCT*));

    return ast;
}