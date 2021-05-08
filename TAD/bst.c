#include <stdio.h>
#include <string.h>
#include "word.h"
#include "../helpers.h"
#include "bst.h"

BST_T* bst_init() {
  return NULL;
}
// função usada para percorrer a arvore BST(ABP) até ou chegar num nodo igual o buscado OU em um vazio
// usada tanto em consulta quanto para inserção
BST_T** bst_search(BST_T **tree, char word[], long unsigned int *stats_comparations) {
  int cmp;
  while (*tree) {
    (*stats_comparations)++;
    cmp = strcmp(word, (*tree)->data->content);
    if (cmp == 0) {
      return tree;
    }
    if (cmp == -1) {
      tree = &(*tree)->left;
    } else {
      tree = &(*tree)->right;
    }
  }
  return tree; // retorna um ponteiro para um filho de uma folha para inserção
}

WORD_T* bst_get(BST_T *tree, char word[], long unsigned int *stats_comparations_query) {
  if ((tree = *(bst_search(&tree, word, stats_comparations_query))) != NULL ) {
    return tree->data;
  }
  return NULL;
}
// recebe os parametros para um novo nodo, aloca um espaço para inserção deste novo nodo.
BST_T* bst_newnode(char *word, BST_T *left, BST_T *right) {
  BST_T* new_node = (BST_T*) malloc(sizeof(BST_T));
  new_node->data = word_init();
  word_insert(&(new_node->data), word);
  new_node->left = left;
  new_node->right = right;
  return new_node;
}
void bst_insert(BST_T **tree, char *word, WORD_T **Word, STATISTICS_T *stats) {
  if(*(tree = (bst_search(tree, word, &stats->comparations_index))) == NULL) { // NULL se não encontrou a palavra na arvore
    (stats->nodes)++;
    *tree = bst_newnode(word, bst_init(), bst_init()); // insere a palavra nova na arvore
  }
  *Word = (*tree)->data; // aponta para o ponteiro da palavra na arvore
  return;
}
int bst_height(BST_T *tree) {
  if (!tree) {
    return 0;
  }
  return 1 + max(bst_height(tree->left), bst_height(tree->right));
}
