#ifndef _BST_H_
#define _BST_H_
#include <stdio.h>
#include <string.h>
#include "word.h"
#include "../helpers.h"

typedef struct BST {
  struct BST *left, *right;
  WORD_T *data;
} BST_T;

BST_T* bst_init();
BST_T** bst_search(BST_T **tree, char word[], long unsigned int *stats_comparations);
WORD_T* bst_get(BST_T *tree, char word[], long unsigned int *stats_comparations_query);
BST_T* bst_newnode(char *word, BST_T *left, BST_T *right);
void bst_insert(BST_T **tree, char *word, WORD_T **Word, STATISTICS_T *stats);
int bst_height(BST_T *tree);
#endif // _BST_H_
