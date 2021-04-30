#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "avl.h"
#include "word.h"
#include "../helpers.h"


AVL_T* avl_init() {
    return NULL;
}

Word_T* avl_search(AVL_T *tree, char x[], int *stats_comparations) {
  int cmp;
  AVL_T *node = tree;
  while (node) {
    (*stats_comparations)++;
    cmp = strcmp(x, node->data->content);
    if (cmp == 0) {
      return node->data;
    }
    if (cmp == -1) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return NULL;
}

AVL_T* avl_rotateleft(AVL_T *p) {
  AVL_T *z;

  z = p->right;
  p->right = z->left;
  z->left = p;
  p->BF = 0;
  p = z;
  return p;
}

AVL_T* avl_doublerotateleft(AVL_T *p) {
  AVL_T *z, *y;

  z = p->right;
  y = z->left;
  z->left = y->right;
  y->right = z;
  p->right = y->left;
  y->left = p;
  p->BF = (y->BF == -1) ? 1 : 0;
  z->BF = (y->BF == 1) ? -1 : 0;
  p = y;
  return p;
}

AVL_T* avl_rotateright(AVL_T *p) {
  AVL_T *u;

  u = p->left;
  p->left = u->right;
  u->right = p;
  p->BF = 0;
  p = u;
  return p;
}

AVL_T* avl_doublerotateright(AVL_T* p) {
  AVL_T *u, *v;

  u = p->left;
  v = u->right;
  u->right = v->left;
  v->left = u;
  p->left = v->right;
  v->right = p;
  p->BF = (v->BF == 1) ? -1 : 0;
  u->BF = (v->BF == -1) ? 1 : 0;
  p = v;
  return p;
}
void avl_insert(AVL_T **tree, char x[], Word_T **Word, int *stats_nodes, unsigned long int *stats_comparations, int *stats_rotations) {
  int ok = 0;
  avl_insertTR(tree, x, &ok, Word, stats_nodes, stats_comparations, stats_rotations);
}
void avl_insertTR(AVL_T **tree, char x[], int *ok, Word_T **Word, int *stats_nodes, unsigned long int *stats_comparations, int *stats_rotations) {
  AVL_T *treeAux = *tree;
  if (!treeAux) {
    treeAux = (AVL_T*) malloc(sizeof(AVL_T));
    treeAux->data = word_init();
    word_set(&(treeAux->data), x);
    treeAux->left = NULL;
    treeAux->right = NULL;
    treeAux->BF = 0;
    *ok = 1;
    *Word = treeAux->data;
    (*stats_nodes)++;
    //return treeAux->data;
  } else if (strcmp(x, treeAux->data->content) == -1) {
    (*stats_comparations)++;
    avl_insertTR(&(treeAux->left), x, ok, Word, stats_nodes, stats_comparations, stats_rotations);
    if (*ok) {
      switch (treeAux->BF) {
        case -1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = 1; break;
        case 1: treeAux = avl_rightrotation(treeAux, ok); (*stats_rotations)++; break;
      }
    }
  } else if(strcmp(x, treeAux->data) == 0) {
    (*stats_comparations)++;
    *Word = treeAux->data;
    return;
  } else {
    (*stats_comparations)++;
    avl_insertTR(&(treeAux->right), x, ok, Word, stats_nodes, stats_comparations, stats_rotations);
    if (*ok) {
      switch (treeAux->BF) {
        case 1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = -1; break;
        case -1: treeAux = avl_leftrotation(treeAux, ok); (*stats_rotations)++; break;
      }
    }
  }
  *tree = treeAux;
}

AVL_T* avl_rightrotation(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->left;
  a = (z->BF == 1) ? avl_rotateright(a) : avl_doublerotateright(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

AVL_T* avl_leftrotation(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->right;
  a = (z->BF == -1) ? avl_rotateleft(a) : avl_doublerotateleft(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

// return tree AVL height
int avl_height(AVL_T *tree) {
  if (!tree) {
    return 0;
  }
  return 1 + max(avl_height(tree->left), avl_height(tree->right));
}

int avl_query(FILE *input, FILE *search, FILE *output) {
  AVL_T *tree = avl_init();
  int stats_nodes = 0, stats_rotations = 0, stats_comparations2 = 0;
  char *word, line[300], *id; // linhas a serem lidas do arquivo
  char sepparator[]= {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
  int id_number;
  Mention_T *Mentions;
  Word_T *Word;
  unsigned long int stats_comparations = 0;

  // each line of input file
  while (fgets(line,1000,input)) {
    id = strtok(line, ";"); // get tweet id
    id_number = atoi(id); // converts id in string to int

    word = strtok(NULL, sepparator); // get tweet first word

    // while find words on tweet...
    while (word != NULL) {
      wordtolowercase(word); // convert word to lowercase
      avl_insert(&tree, word, &Word, &stats_nodes, &stats_comparations, &stats_rotations);
      word_add_mention(&Word, id_number);
      word = strtok(NULL, sepparator); // tweet get the next word of tweet
    }
  }
  while (fgets(line,1000,search)) {
    word = strtok(line, sepparator);
    fprintf(output,"consulta: %s Palavra ", word);
    if (Word = avl_search(tree, word, &stats_comparations2)) {
      fprintf(output, "encontrada nos tweets");
      for (Mentions = mention_invert(Word->mentions); Mentions; Mentions = Mentions->next) {
        fprintf(output, " %d,", Mentions->id);
      }
    } else {
      fprintf(output, "não encontrada");
    }
    fprintf(output, "\n");
  }
  fprintf(output, "\n********** Estatísticas da Indexação **************\n");
  fprintf(output, "nodos = %d\ncomparações = %lu\nrotações = %d\naltura da árvore = %d", stats_nodes, stats_comparations, stats_rotations, avl_height(tree));
  fprintf(output, "\n********** Estatísticas das Consultas **************\n");
  fprintf(output, "comparações = %d", stats_comparations2);

  return EXIT_SUCCESS;
}
