#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "word.h"
#include <unistd.h>


AVL_T* avl_init() {
    return NULL;
}
Word_T* avl_search(AVL_T *tree, char x[]) {
//  printf("[%s | %s]", x, tree->data->content);
  if (!tree) {
    return NULL;
  } else if (strcmp(x, tree->data->content) == 0) {
    return (tree->data);
  } else if (strcmp(x, tree->data->content) == -1) {
    return avl_search(tree->left, x);
  }
  return avl_search(tree->right, x);
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

void avl_insert(AVL_T **tree, char x[], int *ok, Word_T **Word) {
  /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
  x, a chave a ser inserida e h a altura da árvore */
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
    //return treeAux->data;
  } else if (strcmp(x, treeAux->data->content) == -1) {
    avl_insert(&(treeAux->left), x, ok, Word);
    if (*ok) {
      switch (treeAux->BF) {
        case -1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = 1; break;
        case 1: treeAux = avl_Caso1(treeAux, ok); break;
      }
    }
  } else if(strcmp(x, treeAux->data) == 0) {
    *Word = treeAux->data;
    return;
  } else {
    avl_insert(&(treeAux->right), x, ok, Word);
    if (*ok) {
      switch (treeAux->BF) {
        case 1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = -1; break;
        case -1: treeAux = avl_Caso2(treeAux, ok); break;
      }
    }
  }
  *tree = treeAux;
}

AVL_T* avl_Caso1(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->left;
  a = (z->BF == 1) ? avl_rotateright(a) : avl_doublerotateright(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

AVL_T* avl_Caso2(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->right;
  a = (z->BF == -1) ? avl_rotateleft(a) : avl_doublerotateleft(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

void avl_print(AVL_T *tree) {
  if (!tree) {
    return;
  }
  printf("%s\n", tree->data->content);
  avl_print(tree->left);
  avl_print(tree->right);
  return;
}
void avl_printwithlevelTR(AVL_T *tree, int level) {
  int i;
  Mention_T* mentions;
  if (!tree) {
    return;
  }
  for(i = level; i > 0; i--) {
    printf("=");
  }
  printf("%s [", tree->data->content);
  for (mentions = tree->data->mentions; mentions != NULL; mentions = mentions->next) {
    printf(" %d ", mentions->id);
  }
  printf(" ]\n");
  usleep(30000);
  avl_printwithlevelTR(tree->left, level+1);
  avl_printwithlevelTR(tree->right, level+1);
}
void avl_printwithlevel(AVL_T *tree) {
  avl_printwithlevelTR(tree, 1);
}


/*
pNode* consultaABP2(pNodoA *a, int chave) {
    if (a==NULL) {
        return NULL;
    }
    if (a->info == chave) {
        return a;
    }
    if (a->info > chave) {
        return consultaABP2(a->esq,chave);
    }
    return consultaABP2(a->dir,chave);
}

void InsereArvore(pNodoA **a, int ch) {
    pNodoA *novo = *a;
    if (*a == NULL) {
        novo = (pNodoA*) malloc(sizeof(pNodoA));
        novo->info = ch;
        novo->esq = NULL;
        novo->dir = NULL;
    } else {
        if (ch < (*a)->info) {
            InsereArvore(&((*a)->esq),ch);
        } else {
            InsereArvore(&((*a)->dir),ch);
        }
    }
    *a = novo;
}

void ImprimirPreFixadoAEsquerda(pNodoA *a) {
    if (a == NULL) {
        return;
    }
    printf("(%d)  ", a->info);
    ImprimirPreFixadoAEsquerda(a->esq);
    ImprimirPreFixadoAEsquerda(a->dir);
}

int ContarNodos(pNodoA *a) {
    if (a == NULL) {
        return 0;
    }
    return 1 + ContarNodos(a->esq) + ContarNodos(a->dir);
}

void ImprimirPreFixadoAEsquerdaComNivel(pNodoA *a) {
    return AuxImprimirPreFixadoAEsquerdaComNivel(a, 1);
}
// função auxiliar para não precisar passar o nivel quando chamar a função
void AuxImprimirPreFixadoAEsquerdaComNivel(pNodoA *a, int nivel) {
    int i;
    if (a == NULL) {
        return;
    }
    for(i = 0; i < nivel; i++) {
        printf("=");
    }
    printf("%d\n", a->info);
    AuxImprimirPreFixadoAEsquerdaComNivel(a->esq, nivel+1);
    AuxImprimirPreFixadoAEsquerdaComNivel(a->dir, nivel+1);
}

*/
