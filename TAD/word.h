#ifndef _WORD_H_
#define _WORD_H_
#include "mention.h"
#define MAX_SIZE 100

typedef struct WORD {
  char content[MAX_SIZE];
  MENTION_T *mentions;
} WORD_T;

WORD_T* word_init();
void word_insert(WORD_T **Word, char word[]);
void word_add_mention(WORD_T **word, int id);

#endif
