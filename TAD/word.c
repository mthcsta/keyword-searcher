#include<stdio.h>
#include<stdlib.h>
#include "word.h"

Word_T* word_init() {
  Word_T *word;
  word = (Word_T*) malloc(sizeof(Word_T));
  return word;
}
void word_set(Word_T **Word, char word[]) {
  strcpy((*Word)->content, word);
  (*Word)->mentions = NULL;
}

void mention_insert(Mention_T **mentionList, int currentId) {
    Mention_T *new_mention;

    new_mention = (Mention_T*) malloc(sizeof(Mention_T));

    new_mention->id = currentId;
    new_mention->next = *mentionList;
    *mentionList = new_mention;
}
Mention_T* mention_invert(Mention_T *mentionList) {
  Mention_T *new_list = NULL, *ptList;
  for (ptList = mentionList; ptList; ptList = ptList->next) {
    mention_insert(&new_list, ptList->id);
  }
  return new_list;
}
void word_add_mention(Word_T **word, int id) {
  Word_T *wordinha = *word;
  if (wordinha->mentions == NULL || wordinha->mentions->id != id) {
    mention_insert(&(wordinha->mentions), id);
  }
}

// mention_insert(word->mentions, current_id)
