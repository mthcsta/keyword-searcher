#ifndef _ABP_H_
#define _ABP_H_
#include "word.h"
#include "../helpers.h"

typedef struct ABP {
  struct ABP *left;
  WORD_T *data;
  struct ABP *right;
} ABP_T;

ABP_T* abp_init();
ABP_T** abp_search(ABP_T **tree, char word[], long unsigned int *stats_comparations2);
WORD_T* abp_get(ABP_T *tree, char word[], long unsigned int *stats_comparations2);
ABP_T* abp_newnode(char *word, ABP_T *left, ABP_T *right);
void abp_insert(ABP_T **tree, char *word, WORD_T **Word, int *stats_nodes, long unsigned int *stats_comparations);
int abp_query(FILE *input, FILE *search, FILE *output);
void abp_print(ABP_T *tree);
int abp_height(ABP_T *tree);

#endif // _ABP_H_
