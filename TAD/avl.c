#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

AVL_T* Init() {
    return NULL;
}
AVL_T* rotateleft(AVL_T *p) {
  AVL_T *z;

  z = p->right;
  p->right = z->left;
  z->left = p;
  p->BF = 0;
  p = z;
  return p;
}

AVL_T* doublerotateleft(AVL_T *p) {
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

AVL_T* rotateright(AVL_T *p) {
  AVL_T *u;

  u = p->left;
  p->left = u->right;
  u->right = p;
  p->BF = 0;
  p = u;
  return p;
}

AVL_T* doublerotateright(AVL_T* p) {
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

int insert(AVL_T **tree, char x[], int *ok) {
  /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
  x, a chave a ser inserida e h a altura da árvore */
  AVL_T *treeAux = *tree;
  if (!treeAux) {
    treeAux = (AVL_T*) malloc(sizeof(AVL_T));
    strcpy(treeAux->data, x);
    treeAux->left = NULL;
    treeAux->right = NULL;
    treeAux->BF = 0;
    *ok = 1;
  } else if (strcmp(x, treeAux->data) == -1) {
    insert(&(treeAux->left), x, ok);
    if (*ok) {
      switch (treeAux->BF) {
        case -1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = 1; break;
        case 1: treeAux = Caso1(treeAux, ok); break;
      }
    }
  } else {
    insert(&(treeAux->right), x, ok);
    if (*ok) {
      switch (treeAux->BF) {
        case 1: treeAux->BF = 0; *ok = 0; break;
        case 0: treeAux->BF = -1; break;
        case -1: treeAux = Caso2(treeAux, ok); break;
      }
    }
  }
  *tree = treeAux;
  return 0;
}

AVL_T* Caso1(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->left;
  a = (z->BF == 1) ? rotateright(a) : doublerotateright(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

AVL_T* Caso2(AVL_T *a , int *ok) {
  AVL_T *z;
  z = a->right;
  a = (z->BF == -1) ? rotateleft(a) : doublerotateleft(a);
  a->BF = 0;
  *ok = 0;
  return a;
}

void print(AVL_T *tree) {
  if (!tree) {
    return;
  }
  printf("%s\n", tree->data);
  print(tree->left);
  print(tree->right);
  return;
}
void printwithlevelTR(AVL_T *tree, int level) {
  int i;
  if (!tree) {
    return;
  }
  for(i = level; i > 0; i--) {
    printf("=");
  }
  printf("%s\n", tree->data);
  printwithlevelTR(tree->left, level+1);
  printwithlevelTR(tree->right, level+1);
}
void printwithlevel(AVL_T *tree) {
  printwithlevelTR(tree, 1);
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
