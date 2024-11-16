#ifndef MP_PARSER_H
#define MP_PARSER_H
#include "lexer.h"
#include "AST.h"

typedef struct PARSER_STRUCT
{
    lexer_T* lexer;
    token_T* token;
} parser_T;

parser_T* init_parser(lexer_T* lexer);

token_T* parser_consome(parser_T* parser, int tipo);

AST_T* parser_parse(parser_T* parser);

AST_T* parser_parse_pr(parser_T* parser);

AST_T* parser_parse_var(parser_T* parser);

AST_T* parser_parse_dec(parser_T* parser);

AST_T* parser_parse_id(parser_T* parser);

AST_T* parser_parse_num(parser_T* parser);

AST_T* parser_parse_b(parser_T* parser);

AST_T* parser_expressao_alg(parser_T* parser);

AST_T* parser_expr_cond(parser_T* parser);

AST_T* parser_comando(parser_T* parser);

AST_T* parser_condicional(parser_T* parser);

AST_T* parser_repetitivo(parser_T* parser);

AST_T* parser_parse_bloco_P(parser_T* parser);

AST_T* parser_parse_bloco(parser_T* parser);

AST_T* parser_parse_expr(parser_T* parser);

AST_T* parser_parse_composicao(parser_T* parser);
#endif