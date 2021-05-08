#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

RB_T* rb_init() {
  return NULL;
}

RB_T* rb_newnode(int key, int color, RB_T *left, RB_T *right) {
  RB_T *new_node;

  new_node = (RB_T*) malloc(sizeof(RB_T));
  new_node->key = key;
  new_node->color = color;
  new_node->left = left;
  new_node->right = right;

  return new_node;
}

void rb_insert(RB_T **tree, int key) {
  int color = BLACK;
  RB_T **p, **q;

  if (!(*tree)) {
    *tree = rb_newnode(key, color, NULL, NULL);
    return;
  }
  p = tree;
  q = tree;
  do {
    p = q;
    if ((*q)->key == key) {
      return;
    }
    if ((*q)->key < key) {
      q = &(*q)->left;
    } else {
      q = &(*q)->right;
    }
  } while(*q);

  if ((*p)->color == BLACK){
    color = RED;
  }
  *q = rb_newnode(key, color, NULL, NULL);
}

void rb_print(RB_T *tree) {
  if (!tree) return;
  printf("%d : %c \n", tree->key, tree->color == BLACK ? 'B' : 'R');
  rb_print(tree->left);
  rb_print(tree->right);
}
void rb_printwithheight(RB_T *tree, int height, int dir) {
  int i;
  if (!tree) return;
  for (i = 0; i < height; i++) {
    printf("=");
  }
  if (dir == 1) {
    printf("<");
  } else if(dir == 2) {
    printf(">");
  }
  printf("%d : %c \n", tree->key, tree->color == BLACK ? 'B' : 'R');
  rb_printwithheight(tree->left, height+1, 1);
  rb_printwithheight(tree->right, height+1, 2);
}

