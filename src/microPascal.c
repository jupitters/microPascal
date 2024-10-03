#include "include/microPascal.h"
#include "include/lexer.h"
#include "include/io.h"
#include <stdlib.h>

void comp_microPascal(char* src)
{
    lexer_T* lexer = init_lexer(src);
    token_T* tok = 0;
    token_T* lista = NULL;
    int indice = 0;
    FILE *fp = fopen("examples/tokens.lex", "w");

    while((tok = lexer_prox_token(lexer))->tipo != T_EOF)
    {
        if(tok->tipo == T_UNK)
        {
            continue;
        }

        if(tok->tipo == T_ID)
        {
            lista = token_add_lista(lista, tok, indice);

            token_T *id = buscarToken(tok, lista);

            mp_escrita_var(id, lexer);

            indice += 1;
        }
        else
        {
            mp_escrita_tokens(tok, lexer);
        }
        // printf("%s\n", token_to_str(tok));

        
    }

    liberar(lista);
}

void comp_microPascal_arquivo(const char* arquivo)
{
    char* src = mp_ler_arquivo(arquivo);
    comp_microPascal(src);
    free(src);
}

token_T *aloc_token()
{
    token_T *novoToken = (token_T*) malloc(sizeof(token_T));
    if(novoToken == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }

    return novoToken;
}

token_T *token_add_lista(token_T *lista, token_T *token, int indice)
{
    token_T *addToken = aloc_token();

    addToken->proximo = NULL;
    addToken->tipo = token->tipo;
    addToken->valor = token->valor;
    addToken->variavel = indice;

    if (lista == NULL)
    {
        return addToken;
    }
    else
    {
        token_T *ptr = lista;
        while (ptr->proximo != NULL)
        {
            ptr = ptr->proximo;
        }
        ptr->proximo = addToken;

        return lista;
    }
}

token_T *buscarToken(token_T *token, token_T *lista)
{
    for(token_T *ptr = lista; ptr != NULL; ptr = ptr->proximo)
    {
        if (ptr->valor == token->valor)
        {
            return ptr;
        }
    }
}

void liberar(token_T *lista)
{
    token_T *atual = lista;
    token_T *prox;
    while(atual != NULL)
    {
        prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}