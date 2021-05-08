#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

// um tweet tem como limite de 280 caracteres + 20 espaços livres para id e separador
#define LINE_SIZE 300

typedef struct statistics {
  int nodes, rotations, height;
  unsigned long int comparations_index, comparations_query;
  clock_t elapsed_index, elapsed_query;
} STATISTICS_T;

void wordtolowercase(char *s);
int max(int a, int b);
int loadfile(FILE **file, char *filename, char *mode);
int nextword(char **word, char *text);
int lineofwords(char line[], int size, FILE *input, int *id_number);
int wordtoquery(char line[], int size, FILE *query, char **word);
STATISTICS_T indexandqueryAVL(FILE *input, FILE *query, FILE *output);
STATISTICS_T indexandqueryBST(FILE *input, FILE *query, FILE *output);
void putstats(FILE *output, STATISTICS_T *stats);
clock_t clock_diff(clock_t clock_start);

#endif // HELPERS_H
