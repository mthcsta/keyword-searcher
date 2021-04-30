#define TypeData char
#define MAXWORDSIZE 100
#include "word.h"
typedef struct AVL {
  Word_T *data;
  int BF;
  struct AVL *left;
  struct AVL *right;
} AVL_T;


AVL_T* avl_init();
AVL_T* avl_rotateleft(AVL_T *p);
AVL_T* avl_doublerotateleft(AVL_T *p);
AVL_T* avl_rotateright(AVL_T *p);
AVL_T* avl_doublerotateright(AVL_T* p);
void avl_insert(AVL_T **tree, char x[], Word_T **Word, int *stats_nodes, unsigned long int *stats_comparations, int *stats_rotations);
void avl_insertTR(AVL_T **tree, char x[], int *ok, Word_T **Word, int *stats_nodes, unsigned long int *stats_comparations, int *stats_rotations);
AVL_T* avl_rightrotation(AVL_T *a , int *ok);
AVL_T* avl_leftrotation(AVL_T *a , int *ok);
void avl_print(AVL_T *tree);

void avl_printwithlevelTR(AVL_T *tree, int level);
void avl_printwithlevel(AVL_T *tree);
