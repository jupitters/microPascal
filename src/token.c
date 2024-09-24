#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

token_T* init_token(char* valor, int tipo)
{
    token_T* token = calloc(1, sizeof(struct TOKEN_STRUCT));
    token->valor = valor;
    token->tipo = tipo;

    return token;
}

static const char* tipo_token_to_str(int tipo)
{
    switch (tipo)
    {
        case OP_EQ: return "OP_EQ"; 
        case OP_GE: return "OP_GE"; 
        case OP_MUL: return "OP_MUL"; 
        case OP_NE: return "OP_NE";
        case OP_LE: return "OP_LE"; 
        case OP_DIV: return "OP_ DIV"; 
        case OP_GT: return "OP_GT";
        case OP_AD: return "OP_AD";
        case OP_DEC: return "OP_DEC";
        case OP_ASS: return "OP_ASS";
        case OP_LT: return "OP_LT";
        case OP_MIN: return "OP_MIN";
        case SMB_OBC: return "SMB_OBC";
        case SMB_COM: return "SMB_COM";
        case SMB_CBC: return "SMB_CBC";
        case SMB_SEM: return "SMB_SEM";
        case SMB_OPA: return "SMB_OPA";
        case SMB_CPA: return "SMB_CPA";
        case SMB_EOP: return "SMB_EOP";
        case NUM_INT: return "NUM_INT";
        case NUM_FLT: return "NUM_FLT";
        case PAL_RES: return "PAL_RES";
        case T_ID: return "T_ID";
        case T_UNK: return "T_UNK";
        case T_EOF: return "T_EOF"; 
    }

    return "Nao foi possivel converter para string.";
}

char* token_to_str(token_T* token)
{
    const char* tipo_str = tipo_token_to_str(token->tipo);
    // const char* template = "<tipo='%s', tipo_int='%d', valor='%s'>";
    const char* template = "<%s, %s>\n";

    char* str = calloc(strlen(tipo_str) + strlen(template) + 8, sizeof(char));
    //abaixo para o antigo template
    //sprintf(str, template, tipo_str, token->tipo, token->valor);
    sprintf(str, template, tipo_str, token->valor);

    return str;
}