#include "include/parser.h"
#include "include/tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->token = lexer_prox_token(lexer);

    if (!parser) {
        fprintf(stderr, "[Parser]: Falha ao alocar memória para parser.\n");
        exit(1);
    }

    if (!parser->token) {
        fprintf(stderr, "[Parser]: Erro ao obter primeiro token.\n");
        free(parser);
        exit(1);
    }

    return parser;
}

token_T* parser_consome(parser_T* parser, int tipo)
{
    if (parser->token->tipo != tipo)
    {
        printf("[Parser]: Token nao esperado: '%s', token esperado: '%s'\n", token_to_str(parser->token), tipo_token_to_str(tipo));
        exit(1);
    }

    parser->token = lexer_prox_token(parser->lexer);
    return parser->token;
}

AST_T* parser_parse(parser_T* parser)
{
    return parser_parse_composicao(parser);
}

AST_T* parser_parse_pr(parser_T* parser)
{
    if (strcmp(parser->token->valor, "var") == 0)
    {   
        parser_consome(parser, PAL_RES);
        while(strcmp(parser->token->valor, "begin") != 0)
        {
            parser_parse_dec(parser);
        }
        parser_parse_b(parser);
    }

    if (strcmp(parser->token->valor, "begin") == 0)   
    {
        return parser_parse_bloco_P(parser);
    }

}

AST_T* parser_parse_var(parser_T* parser)
{
    if (strcmp(parser->token->valor, "var") != 0)
    {
        printf("[Parser]: Esperado inicializador 'var'.\n");
        exit(1);
    }
}

AST_T* parser_parse_dec(parser_T* parser)
{
    parser_consome(parser, T_ID);

    while (parser->token->tipo == SMB_COM)
    {
        parser_consome(parser, SMB_COM);
        parser_consome(parser, T_ID);
    }

    if (parser->token->tipo != OP_DEC)
    {
        printf("[Parser]: Esperado simbolo ':'\n");
    }
    else
    {
        parser_consome(parser, OP_DEC);
        if (strcmp(parser->token->valor, "integer") != 0 && strcmp(parser->token->valor, "real") != 0)
        {
            printf("[Parser]: Tipo de variavel desconhecido.\n");
            exit(1);
        }
        else
        {
            parser_consome(parser, PAL_RES);
            parser_consome(parser, SMB_SEM);
        }
    }
}
/*
AST_T* parser_parse_id(parser_T* parser)
{
    parser_consome(parser, T_ID);
    
    AST_T* ast = init_ast(AST_VARIAVEL);

    return ast;
}
*/
AST_T* parser_parse_num(parser_T* parser)
{
    if (parser->token->tipo == NUM_INT)
    {
        int int_valor = atoi(parser->token->valor);
        parser_consome(parser, NUM_INT);

        AST_T* ast = init_ast(AST_ASS);
        ast->int_valor = int_valor;

        return ast;
    }
    if (parser->token->tipo == NUM_FLT)
    {
        float int_valor = atof(parser->token->valor);
        parser_consome(parser, NUM_FLT);

        AST_T* ast = init_ast(AST_ASS);
        ast->int_valor = int_valor;

        return ast;
    }
}

AST_T* parser_parse_b(parser_T* parser)
{
    if (strcmp(parser->token->valor, "begin") != 0)
    {
        printf("[Parser]: Esperado inicializador 'begin'.\n");
        exit(1);
    }
}

AST_T* parser_expressao_alg(parser_T* parser)
{
    while (parser->token->tipo != SMB_SEM && strcmp(parser->token->valor, "end") != 0)
    {       
        if (parser->token->tipo == T_ID)
        {
            parser_consome(parser, T_ID);
            if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
            {
                printf("[Parser]: Variavel ou numero no local incorreto.\n");
                exit(1);
            }
        }
        if (parser->token->tipo != NUM_INT && parser->token->tipo != NUM_FLT && parser->token->tipo != T_ID)
        {
            printf("[Parser]: Esperado uma expressao.\n");
            exit(1);
        }

        if (parser->token->tipo == NUM_INT)
        {
            parser_consome(parser, NUM_INT);
            if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
            {
                printf("[Parser]: Variavel ou numero no local incorreto.\n");
                exit(1);
            }
        }
        else if (parser->token->tipo == NUM_FLT)
        {
            parser_consome(parser, NUM_FLT);
            if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
            {
                printf("[Parser]: Variavel ou numero no local incorreto.\n");
            }
        }
         

        if (parser->token->tipo == OP_AD)
        {
            parser_consome(parser, OP_AD);
            if (parser->token->tipo == OP_AD || parser->token->tipo == OP_MIN|| parser->token->tipo == OP_DIV || parser->token->tipo == OP_MUL)
            {
                printf("[Parser]: Operador no local incorreto.\n");
                exit(1);
            }
        }
        else if (parser->token->tipo == OP_MIN)
        {
            parser_consome(parser, OP_MIN);
            if (parser->token->tipo == OP_AD || parser->token->tipo == OP_MIN|| parser->token->tipo == OP_DIV || parser->token->tipo == OP_MUL)
            {
                printf("[Parser]: Operador no local incorreto.\n");
                exit(1);
            }
        }
        else if (parser->token->tipo == OP_DIV)
        {
            parser_consome(parser, OP_DIV);
            if (parser->token->tipo == OP_AD || parser->token->tipo == OP_MIN|| parser->token->tipo == OP_DIV || parser->token->tipo == OP_MUL)
            {
                printf("[Parser]: Operador no local incorreto.\n");
                exit(1);
            }
        }
        else if (parser->token->tipo == OP_MUL)
        {
            parser_consome(parser, OP_MUL);
            if (parser->token->tipo == OP_AD || parser->token->tipo == OP_MIN|| parser->token->tipo == OP_DIV || parser->token->tipo == OP_MUL)
            {
                printf("[Parser]: Operador no local incorreto.\n");
                exit(1);
            }
        }
    }
}

AST_T* parser_expr_cond(parser_T* parser)
{
    if (parser->token->tipo != NUM_INT && parser->token->tipo != NUM_FLT && parser->token->tipo != T_ID)
    {
        printf("[Parser]: Esperado uma expressao.\n");
        exit(1);
    }

    if (parser->token->tipo == NUM_INT)
    {
        parser_consome(parser, NUM_INT);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == NUM_FLT)
    {
        parser_consome(parser, NUM_FLT);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == T_ID)
    {
        parser_consome(parser, T_ID);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }

    if (parser->token->tipo == OP_EQ)
    {
        parser_consome(parser, OP_EQ);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == OP_NE)
    {
        parser_consome(parser, OP_NE);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == OP_LT)
    {
        parser_consome(parser, OP_LT);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == OP_LE)
    {
        parser_consome(parser, OP_LE);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == OP_GE)
    {
        parser_consome(parser, OP_GE);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == OP_GT)
    {
        parser_consome(parser, OP_GT);
        if (parser->token->tipo == OP_EQ || parser->token->tipo == OP_NE|| parser->token->tipo == OP_LT || parser->token->tipo == OP_LE || parser->token->tipo == OP_GE || parser->token->tipo == OP_GT)
        {
            printf("[Parser]: Relacao no local incorreto.\n");
            exit(1);
        }
    }

    if (parser->token->tipo == NUM_INT)
    {
        parser_consome(parser, NUM_INT);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == NUM_FLT)
    {
        parser_consome(parser, NUM_FLT);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }
    else if (parser->token->tipo == T_ID)
    {
        parser_consome(parser, T_ID);
        if (parser->token->tipo == NUM_INT || parser->token->tipo == NUM_FLT || parser->token->tipo == T_ID)
        {
            printf("[Parser]: Variavel ou numero no local incorreto.\n");
            exit(1);
        }
    }
}

AST_T* parser_comando(parser_T* parser)
{
    parser_consome(parser, T_ID);

    if (parser->token->tipo != OP_ASS)
    {
        printf("[Parser]: Esperado o operador ':='.\n");
        exit(1);
    }
    parser_consome(parser, OP_ASS);

    parser_expressao_alg(parser);

    if (parser->token->tipo == SMB_SEM)
    {
        parser_consome(parser, SMB_SEM);
    }
}

AST_T* parser_condicional(parser_T* parser)
{
    parser_consome(parser, PAL_RES); // if

    parser_expr_cond(parser);

    parser_consome(parser,PAL_RES); // then

    parser_comando(parser);

    if (strcmp(parser->token->valor, "else") == 0)
    {
        parser_consome(parser, PAL_RES);
        parser_comando(parser);
    }
}

AST_T* parser_repetitivo(parser_T* parser)
{
    parser_consome(parser, PAL_RES); //while
    
    parser_expr_cond(parser);

    parser_consome(parser, PAL_RES); //do
    
    if(parser->token->tipo == T_ID)
    {
        parser_comando(parser);
    }
    else if (strcmp(parser->token->valor, "begin") == 0)
    {
        parser_parse_bloco_P(parser);
    }
}

AST_T* parser_parse_bloco_P(parser_T* parser)
{
    parser_consome(parser, PAL_RES); // begin principal
    parser_parse_bloco(parser);
    parser_consome(parser, PAL_RES); //end principal
}

AST_T* parser_parse_bloco(parser_T* parser)
{

    AST_T* ast = init_ast(AST_COMPOSICAO);

    while (strcmp(parser->token->valor, "end") != 0)
    {
        if (parser->token->tipo != T_ID && parser->token->tipo != PAL_RES)
        {
            printf("[Parser]: Esperado uma variavel ou comando condicional/repetitivo.\n");
            exit(1);
        }

        if (parser->token->tipo == T_ID)
        {
            parser_comando(parser);            
        }
        
        if (parser->token->tipo == PAL_RES)
        {
            if (strcmp(parser->token->valor, "if") == 0)
            {
                parser_condicional(parser);
            }
            else if (strcmp(parser->token->valor, "while") == 0)
            {
                parser_repetitivo(parser);
            }
            else if (strcmp(parser->token->valor, "begin") == 0)
            {
                parser_parse_bloco_P(parser);
            }
            
        }
    }

    return ast;
}

AST_T* parser_parse_expr(parser_T* parser)
{
    switch (parser->token->tipo)
    {
        case PAL_RES: return parser_parse_pr(parser);
        //case T_ID: return parser_parse_id(parser);
        //case NUM_INT: return parser_parse_num(parser);
        //case NUM_FLT: return parser_parse_num(parser);
        //case SMB_EOP: return parser_parse_bloco(parser);
        default: { printf("[Parser]: Token nao esperado '%s'\n", token_to_str(parser->token));
        exit(1); 
        };
    }
}

AST_T* parser_parse_composicao(parser_T* parser)
{
    unsigned int fechamento = 0;

    if (strcmp(parser->token->valor, "program") == 0)
    {
        parser_consome(parser, PAL_RES);
        fechamento = 1;
    }
    else
    {
        printf("[Parser]: inicializador 'program' nao identificado no inicio do codigo.\n");
        exit(1);
    }

    if (parser->token->tipo != T_ID)
    {
        printf("[Parser]: Esperado um identificador como nome do programa.\n");
        exit(1);
    }

    char* valor = calloc(strlen(parser->token->valor) + 1, sizeof(char));
    strcpy(valor, parser->token->valor);
    parser_consome(parser, T_ID);

    AST_T* ast = init_ast(AST_COMPOSICAO);
    ast->nome = valor;
    parser_consome(parser, SMB_SEM);

    parser_parse_var(parser);

    AST_T* composicao = init_ast(AST_COMPOSICAO);

    while (parser->token->tipo != T_EOF && parser->token->tipo != SMB_EOP)
    {
        lista_coloca(composicao->children, parser_parse_expr(parser));
    }

    if (fechamento)
    {
        parser_consome(parser, SMB_EOP);
    }

    return composicao;
}

