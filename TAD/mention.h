#ifndef _MENTION_H_
#define _MENTION_H_
#include <stdio.h>

typedef struct MENTION {
  int id;
  struct MENTION *next;
} MENTION_T;

MENTION_T* mention_init();
// acessando os membros da estrutura
MENTION_T* mention_next(MENTION_T *Mention);
int mention_id(MENTION_T *Mention);
// adiciona uma nova men??o ao inicio de uma lista de men??es
void mention_insert(MENTION_T **mention_list, int current_id);
// inverte uma lista de men??es
MENTION_T* mention_invert(MENTION_T *mention_list);

#endif // _MENTION_H_
