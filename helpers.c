#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "TAD/avl.h"
#include "TAD/bst.h"

// coloca caracteres em minusculo
void wordtolowercase(char *s) {
  int i;
  for (i=strlen(s)-1; i>=0; i--) {
    s[i] = tolower(s[i]);
  }
}
// retorna o maior entre a e b
int max(int a, int b) {
  return (a > b) ? a : b;
}
// abre arquivo dado pelo nome e o modo
int loadfile(FILE **file, char *filename, char *mode) {
  if (!(*file = fopen(filename, mode))) {
    switch(mode[0]) {
      case 'r':
        printf("erro ao tentar abrir o arquivo %s \n",filename);
      break;
      case 'w':
        printf("erro ao tentar criar o arquivo %s \n",filename);
      break;
    }
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
// vai para a proxima palavra do token
int nextword(char **word, char *text) {
  char sepparator[] = {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"};
  *word = strtok(text, sepparator);
  if ((*word) != NULL) {
    wordtolowercase(*word);
    return 1;
  }
  return 0;
}
// guarda no vetor line uma linha do arquivo de entrada de tweets
int lineofwords(char line[], int size, FILE *input, int *id_number) {
  char *id;
  if (!fgets(line, size, input)) {
    return 0;
  }
  id = strtok(line, ";");
  *id_number = atoi(id);
  return 1;
}
// guarda no vetor line uma palavra do arquivo de consulta
int wordtoquery(char line[], int size, FILE *query, char **word) {
  if (!fgets(line, size, query)) {
    return 0;
  }
  if ((strlen(line) == 1 && line[0] == '\n') || !nextword(word, line)) {
    return wordtoquery(line, size, query, word);
  }
  return 1;
}

// recebe 3 arquivos, um para leitura de tweets, um para consultar palavras e outro para saída das palavras
// consultadas e em quais tweets elas foram encontradas.
// retorna uma struct com as estatisticas da indexação e consulta
STATISTICS_T indexandqueryAVL(FILE *input, FILE *query, FILE *output) {
  int id_number; // id do tweet
  char *word, line[LINE_SIZE]; // linha a serem lidas do arquivo e palavra para token
  AVL_T *tree = avl_init(); // guarda ponteiro para arvore
  WORD_T *Word; // guarda ponteiro para palavra na arvore
  MENTION_T *Mentions; // guarda ponteiro para menções da palavra na arvore
  STATISTICS_T stats = {0, 0, 0, 0, 0, 0}; // inicia estatisticas com os valores em 0
  clock_t clock_start = 0, clock_elapsed = 0; // usados para o tempo decorrido nas estatisticas

  // INDEXAÇÃO
  clock_start = clock();
  while (lineofwords(line, LINE_SIZE, input, &id_number)) {
    while (nextword(&word, NULL)) {
      avl_insert(&tree, word, &Word, &stats);
      word_add_mention(&Word, id_number);
    }
  }
  clock_elapsed = clock_diff(clock_start); // acumula tempo decorrido
  stats.elapsed_index = clock_elapsed; // grava tempo decorrido para indexação

  // CONSULTA
  clock_start = clock();
  while (wordtoquery(line, LINE_SIZE, query, &word)) {
    if ((Word = avl_search(tree, word, &stats.comparations_query))) {
      fprintf(output,"consulta: %s Palavra encontrada nos tweets", word);
      for (Mentions = mention_invert(Word->mentions); Mentions; Mentions = Mentions->next) {
        fprintf(output, " %d,", Mentions->id);
      }
    } else {
      fprintf(output, "consulta: %s Palavra não encontrada", word);
    }
    fprintf(output, "\n");
  }
  clock_elapsed = clock_diff(clock_start); // acumula tempo decorrido
  stats.height = avl_height(tree);
  stats.elapsed_query = clock_elapsed; // grava tempo decorrido para consulta

  return stats;
}

// recebe 3 arquivos, um para leitura de tweets, um para consultar palavras e outro para saída das palavras
// consultadas e em quais tweets elas foram encontradas.
// retorna uma struct com as estatisticas da indexação e consulta
STATISTICS_T indexandqueryBST(FILE *input, FILE *query, FILE *output) {
  setlocale(LC_ALL, "Portuguese");
  int id_number; // id do tweet
  char *word, line[LINE_SIZE]; // linha a serem lidas do arquivo e palavra para token
  BST_T *tree = bst_init(); // guarda ponteiro para arvore
  WORD_T *Word; // guarda ponteiro para palavra na arvore
  MENTION_T *Mentions; // guarda ponteiro para menções da palavra na arvore
  STATISTICS_T stats = {0, 0, 0, 0, 0, 0}; // inicia estatisticas com os valores em 0
  clock_t clock_start = 0, clock_elapsed = 0; // usados para o tempo decorrido nas estatisticas

  // INDEXAÇÃO
  clock_start = clock();
  while (lineofwords(line, LINE_SIZE, input, &id_number)) {
    while (nextword(&word, NULL)) {
      bst_insert(&tree, word, &Word, &stats);
      word_add_mention(&Word, id_number);
    }
  }
  clock_elapsed = clock_diff(clock_start); // acumula tempo decorrido
  stats.elapsed_index = clock_elapsed; // grava tempo decorrido para indexação

  // CONSULTA
  clock_start = clock();
  while (wordtoquery(line, LINE_SIZE, query, &word)) {
    if ((Word = bst_get(tree, word, &stats.comparations_query))) {
      fprintf(output,"consulta: %s Palavra encontrada nos tweets", word);
      for (Mentions = mention_invert(Word->mentions); Mentions; Mentions = Mentions->next) {
        fprintf(output, " %d,", Mentions->id);
      }
    } else {
      fprintf(output, "consulta: %s Palavra não encontrada", word);
    }
    fprintf(output, "\n");
  }
  clock_elapsed = clock_diff(clock_start); // acumula tempo decorrido
  stats.height = bst_height(tree);
  stats.elapsed_query = clock_elapsed; // grava tempo decorrido para consulta

  return stats;
}
// coloca em um arquivo de escrita as estatisticas geradas por funções indexandquery
void putstats(FILE *output, STATISTICS_T *stats) {
  fprintf(output, "\n********** Estatísticas da Indexação **************\n");
  fprintf(output, "nodos = %d\n", stats->nodes);
  fprintf(output, "comparações = %lu\n", stats->comparations_index);
  fprintf(output, "rotações = %d\n", stats->rotations);
  fprintf(output, "altura da árvore = %d\n", stats->height);
  fprintf(output, "tempo decorrido = %ld ms\n", stats->elapsed_index);

  fprintf(output, "\n********** Estatísticas das Consultas **************\n");
  fprintf(output, "comparações = %lu\n", stats->comparations_query);
  fprintf(output, "tempo decorrido = %ld ms\n", stats->elapsed_query);
}
// calcula a diferença entre o clock atual e um clock salvo antes
clock_t clock_diff(clock_t clock_start) {
  return ((clock() - clock_start) * 1000) / CLOCKS_PER_SEC;
}
