#ifndef _MENTION_H_
#define _MENTION_H_
#include <stdio.h>

typedef struct MENTION {
  int id;
  struct MENTION *next;
} MENTION_T;

MENTION_T* mention_init();
void mention_insert(MENTION_T **mention_list, int current_id);
MENTION_T* mention_invert(MENTION_T *mention_list);

#endif // _MENTION_H_
