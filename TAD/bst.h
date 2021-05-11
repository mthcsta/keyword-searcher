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
// instancia um novo nodo
BST_T* bst_newnode(char *word, BST_T *left, BST_T *right);
// percorre arvore BST(ABP) até uma das condições ser verdade:
// OU word existir arvore OU chegar ao final da arvore. Retorna o nodo
BST_T** bst_search(BST_T **tree, char word[], long unsigned int *stats_comparations);
// chama bst_search e retorna a palavra contida no nodo ou nulo
WORD_T* bst_get(BST_T *tree, char word[], long unsigned int *stats_comparations_query);
// chama bst_search, caso retorne nulo, então registra nova palavra na arvore
// retorna no ponteiro Word a palavra contida no parametro word.
void bst_insert(BST_T **tree, char *word, WORD_T **Word, STATISTICS_T *stats);
// encontra a altura da arvore de forma recursiva
int bst_height(BST_T *tree);
#endif // _BST_H_
