#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "mention.h"

WORD_T* word_init() {
  return NULL;
}
MENTION_T* word_mentions(WORD_T *Word) {
  return Word->mentions;
}
const char* word_content(WORD_T *Word) {
  return Word->content;
}
void word_insert(WORD_T **Word, char word[]) {
  WORD_T *new_word;

  new_word = (WORD_T*) malloc(sizeof(WORD_T));
  new_word->mentions = mention_init();
  strcpy(new_word->content, word);
  *Word = new_word;
}
void word_add_mention(WORD_T **Word, int id) {
  if ((*Word)->mentions == NULL || mention_id((*Word)->mentions) != id) {
    mention_insert(&(*Word)->mentions, id);
  }
}
