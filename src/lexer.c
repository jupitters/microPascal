 #include "include/macros.h"
 #include "include/lexer.h"
 #include "include/token.h"
 #include <string.h>
 #include <stdlib.h>
 #include <ctype.h>

 lexer_T* init_lexer(char* src)
 {
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_tam = strlen(src);
    lexer->i = 0;
    lexer->c = src[lexer->i];
    lexer->lin = 1;
    lexer->col = 1;

    return lexer;
 }

 void lexer_avanco(lexer_T* lexer)
 {
    if(lexer->i < lexer->src_tam && lexer->c != '\0')
    {
        lexer->i += 1;
        lexer->c = lexer->src[lexer->i];
    }
 }

 char lexer_peek(lexer_T* lexer, int offset)
 {
    return lexer->src[MIN(lexer->i + offset, lexer->src_tam)];
 }

 token_T* lexer_avanco_com(lexer_T* lexer, token_T* token)
 {
    lexer_avanco(lexer);
    return token;
 }

 token_T* lexer_avanco_momento(lexer_T* lexer, int tipo)
 {
    char* valor = calloc(2, sizeof(char));
    valor[0] = lexer->c;
    valor[1] = '\0';

    token_T* token = init_token(valor, tipo);
    lexer_avanco(lexer);

    return token;
}

 void lexer_espaco(lexer_T* lexer)
 {

    while(lexer->c == 13 ||lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
        {
            if (lexer->c == 13)
            {
                lexer->lin += 1;
                lexer->col = 1;
            }
            if (lexer->c == ' ')
            {
                lexer->col += 1;
            }
            if (lexer->c == '\t')
            {
                lexer->col += 4;
            }
            lexer_avanco(lexer);
        }
 }

token_T* lexer_parse_id(lexer_T* lexer)
{
    char* reservadas[11] = {"program", "var", "integer", "real", "begin", "end", "if", "then", "else", "while","do"};
    char* valor = calloc(1, sizeof(char));

    while(isalpha(lexer->c))
    {
        valor = realloc(valor, (strlen(valor) + 1) * sizeof(char));
        strcat(valor, (char[]){lexer->c, 0});
        lexer_avanco(lexer);
    }

    for (int i = 0; i < 11; i++)
    {
        if (strcmp(reservadas[i], valor) == 0)
        {   
            lexer->i -= 1;
            lexer->c = lexer->src[lexer->i];
            lexer->col += strlen(valor);

            return init_token(valor, PAL_RES);
        }
    }

    lexer->i -= 1;
    lexer->c = lexer->src[lexer->i];
    lexer->col += strlen(valor);

    return init_token(valor, T_ID);
}


token_T* lexer_parse_duploSinal(lexer_T* lexer, int tipo)
{
    char* valor = calloc(1, sizeof(char));

    while(lexer->c != ' ' && !isalnum(lexer->c))
    {
        valor = realloc(valor, (strlen(valor) + 1) * sizeof(char));
        strcat(valor, (char[]){lexer->c, 0});
        lexer_avanco(lexer);
    }

    lexer->i -= 1;
    lexer->c = lexer->src[lexer->i];
    lexer->col += strlen(valor);

    switch(tipo)
    {
        case 1: return init_token(valor, OP_ASS);
        case 2: return init_token(valor, OP_GE);
        case 3: return init_token(valor, OP_LE);
        case 4: return init_token(valor, OP_NE);
    }
}

token_T* lexer_parse_numero(lexer_T* lexer)
{
    char* valor = calloc(1, sizeof(char));
    while(isdigit(lexer->c))
    {
        valor = realloc(valor, (strlen(valor) + 2) * sizeof(char));
        strcat(valor, (char[]){lexer->c, 0});
        lexer_avanco(lexer);
    }

    if (lexer->c == '.')
    {
        valor = realloc(valor, (strlen(valor) + 2) * sizeof(char));
        strcat(valor, (char[]){lexer->c, 0});
        lexer_avanco(lexer);

        while(isdigit(lexer->c))
        {
            valor = realloc(valor, (strlen(valor) + 2) * sizeof(char));
            strcat(valor, (char[]){lexer->c, 0});
            lexer_avanco(lexer);
        }

        lexer->i -= 1;
        lexer->c = lexer->src[lexer->i];
        lexer->col += strlen(valor);

        return init_token(valor, NUM_FLT);
    }

    lexer->i -= 1;
    lexer->c = lexer->src[lexer->i];
    lexer->col += strlen(valor);

    return init_token(valor, NUM_INT);
}

token_T* lexer_prox_token(lexer_T* lexer)
{
    while(lexer->c != '\0')
    {
        lexer_espaco(lexer);

        if(isalpha(lexer->c))
            return lexer_avanco_com(lexer, lexer_parse_id(lexer));
        if(isdigit(lexer->c))
            return lexer_avanco_com(lexer, lexer_parse_numero(lexer));
        if(lexer->c == ':' && lexer_peek(lexer, 1) ==  '=') // tipo 1 assign :=
            return lexer_avanco_com(lexer, lexer_parse_duploSinal(lexer, 1));
        if(lexer->c == '>' && lexer_peek(lexer, 1) ==  '=') // tipo 2 greater equal >=
             return lexer_avanco_com(lexer, lexer_parse_duploSinal(lexer, 2));
        if(lexer->c == '<')
        {
            if (lexer_peek(lexer, 1) ==  '=') // tipo 3 lesser equal <=
                return lexer_avanco_com(lexer, lexer_parse_duploSinal(lexer, 3));
            if (lexer_peek(lexer, 1) == '>') // tipo 4 not equal <>
                return lexer_avanco_com(lexer, lexer_parse_duploSinal(lexer, 4));
        }   

        lexer->col += 1;

        switch (lexer->c)
        {
            case '=': return lexer_avanco_momento(lexer, OP_EQ);
            case '*': return lexer_avanco_momento(lexer, OP_MUL);
            case '/': return lexer_avanco_momento(lexer, OP_DIV);
            case '>': return lexer_avanco_momento(lexer, OP_GT);
            case '+': return lexer_avanco_momento(lexer, OP_AD);
            case ':': return lexer_avanco_momento(lexer, OP_DEC);
            case '<': return lexer_avanco_momento(lexer, OP_LT);
            case '-': return lexer_avanco_momento(lexer, OP_MIN);
            case '{': return lexer_avanco_momento(lexer, SMB_OBC);
            case ',': return lexer_avanco_momento(lexer, SMB_COM);
            case '}': return lexer_avanco_momento(lexer, SMB_CBC);
            case ';': return lexer_avanco_momento(lexer, SMB_SEM);
            case '(': return lexer_avanco_momento(lexer, SMB_OPA);
            case ')': return lexer_avanco_momento(lexer, SMB_CPA);
            case '.': return lexer_avanco_momento(lexer, SMB_EOP);
            case '\0': break;
            default: 
                printf("[Lexer]: Caractere desconhecido '%c' em: Linha %d | Coluna: %d\n", lexer->c, lexer->lin, (lexer->col - 1));
                //exit(1);
                return lexer_avanco_momento(lexer, T_UNK);
                break; 
        }
    }

    return init_token(0, T_EOF);
}