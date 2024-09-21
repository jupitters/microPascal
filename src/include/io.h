#ifndef MP_IO_H
#define MP_IO_H
#include <stdio.h>
#include <stdlib.h>
size_t getline(char **lineptr, size_t *n, FILE *stream);
char* mp_ler_arquivo(const char* nomeArquivo);
#endif