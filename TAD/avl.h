#ifndef _AVL_H_
#define _AVL_H_
#include <stdio.h>
#include <string.h>
#include "word.h"
#include "../helpers.h"

typedef struct AVL {
  WORD_T *data;
  int BF;
  struct AVL *left;
  struct AVL *right;
} AVL_T;


AVL_T* avl_init();
// instancia um novo nodo
AVL_T* avl_newnode(WORD_T *Word, AVL_T *left, AVL_T *right, int BF);
// percorre arvore AVL e retorna a palavra contida no nodo ou nulo caso não exista
WORD_T* avl_search(AVL_T *tree, char word[], unsigned long int *stats_comparations);
/*
  ROTAÇÕES DA ARVORE AVL
*/
AVL_T* avl_rotateleft(AVL_T *tree);
AVL_T* avl_doublerotateleft(AVL_T *tree);
AVL_T* avl_rotateright(AVL_T *tree);
AVL_T* avl_doublerotateright(AVL_T *tree);
/*
  CASOS DE QUANDO DEVE ROTACIONA-LA
  As funções de rotação são chamadas por estas
*/
AVL_T* avl_caseright(AVL_T *tree, int *changed, int *stats_rotations);
AVL_T* avl_caseleft(AVL_T *tree, int *changed, int *stats_rotations);

/*
  INSERE NOVO NODO
  a função avl_insertTR não deve ser chamada. Ela é auxiliar para a função
  avl_insert, sendo passada a avl_insertTR um ponteiro *changed com valor 0.
  O ponteiro changed é util somente para a pilha de chamadas.
  Retorna no ponteiro Word a palavra passada no vetor "word"
*/
void avl_insert(AVL_T **tree, char word[], WORD_T **Word, STATISTICS_T *stats);
void avl_insertTR(AVL_T **tree, char word[], int *changed, WORD_T **Word, STATISTICS_T *stats);
// calcula de forma recursiva a altura da arvore AVL
int avl_height(AVL_T *tree);

#endif // _AVL_H_
