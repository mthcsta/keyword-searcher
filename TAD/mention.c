#include <stdlib.h>
#include "mention.h"

MENTION_T* mention_init() {
  return NULL;
}

// insere nova menção no inicio da lista de menções
void mention_insert(MENTION_T **mention_list, int current_id) {
    MENTION_T *new_mention;
    new_mention = (MENTION_T*) malloc(sizeof(MENTION_T));
    new_mention->id = current_id;
    new_mention->next = *mention_list;
    *mention_list = new_mention;
}

// retorna a lista de menções passadas em forma inversa
MENTION_T* mention_invert(MENTION_T *mention_list) {
  MENTION_T *new_list = NULL, *pt_list;
  for (pt_list = mention_list; pt_list; pt_list = pt_list->next) {
    mention_insert(&new_list, pt_list->id);
  }
  return new_list;
}
