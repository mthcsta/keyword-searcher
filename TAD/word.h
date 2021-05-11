#ifndef _WORD_H_
#define _WORD_H_
#include "mention.h"
#define MAX_SIZE 100

typedef struct WORD {
  char content[MAX_SIZE];
  MENTION_T *mentions;
} WORD_T;

WORD_T* word_init();
// acessando os membros da estrutura
MENTION_T* word_mentions(WORD_T *Word);
const char* word_content(WORD_T *Word);
// instancia uma WORD para palavra passada
void word_insert(WORD_T **Word, char word[]);
// adiciona uma menção a uma Word
void word_add_mention(WORD_T **Word, int id);

#endif
