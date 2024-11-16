#ifndef MP_AST_H
#define MP_AST_H
#include "lista.h"

typedef struct AST_STRUCT
{
    enum
    {
        AST_COMPOSICAO,
        AST_FUNC,
        AST_ASS,
        AST_DEF_TIPO,
        AST_VARIAVEL,
        AST_DECLARACAO,
        AST_INT,
        AST_NOOP,
    } tipo;

    lista_T* children;
    char* nome;
    struct AST_STRUCT* valor;
    int int_valor;
    int tipo_dado;
} AST_T;

AST_T* init_ast(int tipo);
#endif