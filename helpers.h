#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "TAD/word.h"
// um tweet tem como limite de 280 caracteres + 20 espaços livres para id e separador
#define LINE_SIZE 300
#define MILLISEC 1000

typedef struct STATISTICS {
  int nodes, rotations, height;
  unsigned long int comparations_index, comparations_query;
  double elapsed_index, elapsed_query, elapsed_query_average;
} STATISTICS_T;

// passa uma palavra para minuscula
void wordtolowercase(char *s);
// retorna o maximo entre a e b
int max(int a, int b);
// fopen com mensagens personalizadas de erro
int loadfile(FILE **file, char *filename, char *mode);
// itera TOKEN indo para próxima palavra contida nele.
int nextword(char **word, char *text);
// carrega uma lista de palavras
int lineofwords(char line[], int size, FILE *input, int *id_number);
// coloca uma palavra contida no arquivo de query para consulta no ponteiro word
int wordtoquery(char line[], int size, FILE *query, char **word);
// coloca palavra consultada no arquivo de saída e percorre por suas menções caso exista.
void wordtooutput(FILE *output, WORD_T **Word, char *word);
// indexa e consulta em uma arvore AVL
STATISTICS_T indexandqueryAVL(FILE *input, FILE *query, FILE *output, int times);
// indexa e consulta em uma arvore BST(ABP)
STATISTICS_T indexandqueryBST(FILE *input, FILE *query, FILE *output, int times);
// coloca estatisticas no arquivo de saída
void putstats(FILE *output, STATISTICS_T *stats);
// coloca quantas vezes executou o arquivo de consulta
void putstattimes(FILE *output, int times);
// calcula o tempo decorrido comparando o tempo atual com o dado pelo parâmetro
double clock_diff(clock_t clock_start);

#endif // HELPERS_H
