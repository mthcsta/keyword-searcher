#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "word.h"
#include "../helpers.h"


AVL_T* avl_init() {
    return NULL;
}

AVL_T* avl_newnode(WORD_T *Word, AVL_T *left, AVL_T *right, int BF) {
  AVL_T *node = avl_init();
  node = (AVL_T*) malloc(sizeof(AVL_T));
  node->data = Word;
  node->left = left;
  node->right = right;
  node->BF = BF;
  return node;
}

WORD_T* avl_search(AVL_T *tree, char word[], unsigned long int *stats_comparations) {
  int cmp;

  while (tree) {
    (*stats_comparations)++;
    cmp = strcmp(word, word_content(tree->data)); // compara palavra com contida no nodo atual
    if (cmp == 0) {
      return tree->data;
    }
    if (cmp == -1) {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }
  return NULL;
}
void avl_insert(AVL_T **tree, char word[], WORD_T **Word, STATISTICS_T *stats) {
  int changed = 0;
  avl_insertTR(tree, word, &changed, Word, stats); // chama auxiliar para inserção em AVL
}
// recursão chamada por avl_insert
void avl_insertTR(AVL_T **tree, char word[], int *changed, WORD_T **Word, STATISTICS_T *stats) {
  int cmp;
  AVL_T *node = *tree;
  (stats->comparations_index)++;
  if (!node) { // insere nodo
    node = avl_newnode(word_init(), avl_init(), avl_init(), 0);
    word_insert(&(node->data), word);
    *Word = node->data;
    *changed = 1;
    (stats->nodes)++;
  } else if ((cmp = strcmp(word, word_content(node->data))) == 0) { // caso a palavra seja a buscada, para de percorrer a arvore.
    *Word = node->data;
    return;
  } else if (cmp == -1) { // caso a palavra seja menor na ordem lexicográfica
    avl_insertTR(&(node->left), word, changed, Word, stats);
    if (*changed) {
      switch (node->BF) {
        case -1: node->BF = 0; *changed = 0; break;
        case 0: node->BF = 1; break;
        case 1: node = avl_caseright(node, changed, &stats->rotations); break;
      }
    }
  } else { // caso seja maior na ordem lexicográfica
    avl_insertTR(&(node->right), word, changed, Word, stats);
    if (*changed) {
      switch (node->BF) {
        case 1: node->BF = 0; *changed = 0; break;
        case 0: node->BF = -1; break;
        case -1: node = avl_caseleft(node, changed, &stats->rotations); break;
      }
    }
  }
  *tree = node;
}
int avl_height(AVL_T *tree) {
  if (!tree) {
    return 0;
  }
  return 1 + max(avl_height(tree->left), avl_height(tree->right));
}


/*
  ROTAÇÕES
  abaixo apenas rotações e funções de CASO,
  funções que fazem as chamadas das rotações.
*/

AVL_T* avl_rotateleft(AVL_T *tree) {
  AVL_T *z;

  z = tree->right;
  tree->right = z->left;
  z->left = tree;
  tree->BF = 0;
  tree = z;
  return tree;
}
AVL_T* avl_doublerotateleft(AVL_T *tree) {
  AVL_T *z, *y;

  z = tree->right;
  y = z->left;
  z->left = y->right;
  y->right = z;
  tree->right = y->left;
  y->left = tree;
  tree->BF = (y->BF == -1) ? 1 : 0;
  z->BF = (y->BF == 1) ? -1 : 0;
  tree = y;
  return tree;
}
AVL_T* avl_rotateright(AVL_T *tree) {
  AVL_T *u;

  u = tree->left;
  tree->left = u->right;
  u->right = tree;
  tree->BF = 0;
  tree = u;
  return tree;
}
AVL_T* avl_doublerotateright(AVL_T* tree) {
  AVL_T *u, *v;

  u = tree->left;
  v = u->right;
  u->right = v->left;
  v->left = u;
  tree->left = v->right;
  v->right = tree;
  tree->BF = (v->BF == 1) ? -1 : 0;
  u->BF = (v->BF == -1) ? 1 : 0;
  tree = v;
  return tree;
}
AVL_T* avl_caseright(AVL_T *tree, int *changed, int *stats_rotations) {
  AVL_T *z;
  z = tree->left;
  if (z->BF == 1) {
    tree = avl_rotateright(tree);
    (*stats_rotations) += 1;
  } else {
    tree = avl_doublerotateright(tree);
    (*stats_rotations) += 2;
  }
  tree->BF = 0;
  *changed = 0;
  return tree;
}
AVL_T* avl_caseleft(AVL_T *tree, int *changed, int *stats_rotations) {
  AVL_T *z;
  z = tree->right;
  if (z->BF == -1) {
    tree = avl_rotateleft(tree);
    (*stats_rotations) += 1;
  } else {
    tree = avl_doublerotateleft(tree);
    (*stats_rotations) += 2;
  }
  tree->BF = 0;
  *changed = 0;
  return tree;
}
