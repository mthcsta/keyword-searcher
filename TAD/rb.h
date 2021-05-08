#ifndef _RB_H_
#define _RB_H_
#define RED 1
#define BLACK 0

typedef struct RB {
  int key;
  struct RB *left;
  struct RB *right;
  int color;
} RB_T;

RB_T* rb_init();
RB_T* rb_newnode(int key, int color, RB_T *left, RB_T *right);
void rb_insert(RB_T **tree, int key);

#endif
