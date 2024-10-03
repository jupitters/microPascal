#include "include/io.h"
#include "include/lexer.h"
#include <string.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

char* mp_ler_arquivo(const char* nomeArquivo)
{
    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    fp = fopen(nomeArquivo, "rb");
    if (fp == NULL)
    {
        printf("Nao pode ler o arquivo '%s'\n", nomeArquivo);
        exit(1);
    }

    char *buffer = (char*) calloc(1,sizeof(char));
    buffer[0] = '\0';

    while ((read = getline(&line, &len, fp)) != -1)
    {
        buffer = (char*) realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
        strcat(buffer, line);
    }

    fclose(fp);
    if (line)
    {
        free(line);
    }

    return buffer;
}

void mp_escrita_tokens(token_T* token, lexer_T* lexer)
{
    FILE *fp = fopen("examples/tokens.lex", "a");

    int coluna = lexer->col;
    coluna -= strlen(token->valor);

    fprintf(fp, "Linha:%d | Coluna:%d %s", lexer->lin, coluna, token_to_str(token));

    fclose(fp);
}

void mp_escrita_var(token_T* token, lexer_T* lexer)
{
    FILE *fp = fopen("examples/tokens.lex", "a");

    int coluna = lexer->col;
    coluna -= strlen(token->valor);

    fprintf(fp, "Linha:%d | Coluna:%d %s", lexer->lin, coluna, token_to_var(token));

    fclose(fp);
}