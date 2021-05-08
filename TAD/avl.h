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
AVL_T* avl_newnode(WORD_T *Word, AVL_T *left, AVL_T *right, int BF);
WORD_T* avl_search(AVL_T *tree, char word[], unsigned long int *stats_comparations);
AVL_T* avl_rotateleft(AVL_T *p);
AVL_T* avl_doublerotateleft(AVL_T *p);
AVL_T* avl_rotateright(AVL_T *p);
AVL_T* avl_doublerotateright(AVL_T* p);
void avl_insert(AVL_T **tree, char word[], WORD_T **Word, STATISTICS_T *stats);
void avl_insertTR(AVL_T **tree, char word[], int *changed, WORD_T **Word, STATISTICS_T *stats);
AVL_T* avl_caseright(AVL_T *tree, int *changed, int *stats_rotations);
AVL_T* avl_caseleft(AVL_T *tree, int *changed, int *stats_rotations);
int avl_height(AVL_T *tree);

#endif // _AVL_H_
