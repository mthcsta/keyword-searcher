#ifndef WORDT
#define WORDT 1
#define MAX_SIZE 100
typedef struct Mention {
  int id;
  struct Mention *next;
} Mention_T;

typedef struct Word {
  char content[MAX_SIZE];
  Mention_T *mentions;
} Word_T;

Word_T* word_init();
void mention_insert(Mention_T **mentionList, int currentId);


void word_add_mention(Word_T** word, int id);
#endif
