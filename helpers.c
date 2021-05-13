#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "TAD/avl.h"
#include "TAD/bst.h"
#include "TAD/word.h"
#include "TAD/mention.h"

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
  char sepparator[] = {" 0123456789,.&*%\?!;/-+'@\"$#=~><()][}{:\n\t_^`|\\"};
  *word = strtok(text, sepparator); // aponta para a proxima palavra do token
  if ((*word) != NULL) { // caso a palavra n�o seja NULL, ent�o poe em minusculo.
    wordtolowercase(*word);
    return 1;
  }
  return 0;
}
// guarda no vetor line uma linha do arquivo de entrada de tweets
int lineofwords(char line[], int size, FILE *input, int *id_number) {
  char *id;
  if (!fgets(line, size, input)) { // se fgets falhar ent�o termina a fun��o informando que deve terminar o la�o.
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

// coloca palavra consultada em OUTPUT junto dos ids onde a palavra foi mencionada
void wordtooutput(FILE *output, WORD_T **Word, char *word) {
  MENTION_T *Mentions;
  if (!(*Word)) { // caso o ponteiro seja nulo, ent�o n�o foi encontrada a palavra.
    fprintf(output, "consulta: %s Palavra n�o encontrada", word);
    return;
  }
  fprintf(output,"consulta: %s Palavra encontrada nos tweets", word);
  for (Mentions = mention_invert(word_mentions(*Word)); Mentions; Mentions = mention_next(Mentions)) {
    fprintf(output, " %d,", mention_id(Mentions));
  }
  return;
}

// recebe 3 arquivos, um para leitura de tweets, um para consultar palavras e outro para sa�da das palavras
// recebe por fim uma variavel times que diz quantas vezes o programa repetir� o arquivo de consulta
// consultadas e em quais tweets elas foram encontradas.
// retorna uma struct com as estatisticas da indexa��o e consulta
STATISTICS_T indexandqueryAVL(FILE *input, FILE *query, FILE *output, int times) {
  int id_number, times_dec; // id do tweet e vezes que consultar�
  char *word, line[LINE_SIZE]; // linha a serem lidas do arquivo e palavra para token
  AVL_T *tree = avl_init(); // guarda ponteiro para arvore
  WORD_T *Word; // guarda ponteiro para palavra na arvore
  STATISTICS_T stats = {0, 0, 0, 0, 0, 0}; // inicia estatisticas com os valores em 0
  clock_t clock_start = 0; // usados para o tempo decorrido nas estatisticas

  // INDEXA��O
  clock_start = clock();
  while (lineofwords(line, LINE_SIZE, input, &id_number)) {
    while (nextword(&word, NULL)) {
      avl_insert(&tree, word, &Word, &stats);
      word_add_mention(&Word, id_number);
    }
  }
  stats.elapsed_index = clock_diff(clock_start); // grava tempo decorrido para indexa��o
  stats.height = avl_height(tree);

  // repete o arquivo CONSULTA x vezes, onde x � a variavel times
  times_dec = times;
  clock_start = clock();
  do {
    fseek(query, 0, SEEK_SET);
    while (wordtoquery(line, LINE_SIZE, query, &word)) {
      Word = avl_search(tree, word, &stats.comparations_query);
    }
    times_dec--;
  } while (times_dec > 0);
  // guarda valores referentes ao clock
  stats.elapsed_query = clock_diff(clock_start);
  stats.elapsed_query_average = stats.elapsed_query / times; // grava tempo decorrido para consulta

  // repete CONSULTA porem agora inserindo no arquivo de sa�da.
  fseek(query, 0, SEEK_SET); // coloca ponteiro para o arquivo no come�o
  stats.comparations_query = 0;
  while (wordtoquery(line, LINE_SIZE, query, &word)) {
    Word = avl_search(tree, word, &stats.comparations_query);
    wordtooutput(output, &Word, word);
    fprintf(output, "\n");
  }
  return stats;
}

// recebe 3 arquivos, um para leitura de tweets, um para consultar palavras e outro para sa�da das palavras
// recebe por fim uma variavel times que diz quantas vezes o programa repetir� o arquivo de consulta
// consultadas e em quais tweets elas foram encontradas.
// retorna uma struct com as estatisticas da indexa��o e consulta
STATISTICS_T indexandqueryBST(FILE *input, FILE *query, FILE *output, int times) {
  setlocale(LC_ALL, "Portuguese");
  int id_number, times_dec; // id do tweet
  char *word, line[LINE_SIZE]; // linha a serem lidas do arquivo e palavra para token
  BST_T *tree = bst_init(); // guarda ponteiro para arvore
  WORD_T *Word; // guarda ponteiro para palavra na arvore
  STATISTICS_T stats = {0, 0, 0, 0, 0, 0}; // inicia estatisticas com os valores em 0
  clock_t clock_start = 0; // usados para o tempo decorrido nas estatisticas

  // INDEXA��O
  clock_start = clock();
  while (lineofwords(line, LINE_SIZE, input, &id_number)) {
    while (nextword(&word, NULL)) {
      bst_insert(&tree, word, &Word, &stats);
      word_add_mention(&Word, id_number);
    }
  }
  stats.elapsed_index = clock_diff(clock_start); // grava tempo decorrido para indexa��o
  stats.height = bst_height(tree);

  // repete o arquivo CONSULTA x vezes, onde x � a variavel times
  times_dec = times;
  clock_start = clock();
  do {
    fseek(query, 0, SEEK_SET);
    while (wordtoquery(line, LINE_SIZE, query, &word)) {
      Word = bst_get(tree, word, &stats.comparations_query);
    }
    times_dec--;
  } while(times_dec > 0);
  // guarda valores referentes ao clock
  stats.elapsed_query = clock_diff(clock_start);
  stats.elapsed_query_average = stats.elapsed_query / times; // grava tempo decorrido para consulta

  // repete CONSULTA porem agora inserindo no arquivo de sa�da.
  fseek(query, 0, SEEK_SET);
  stats.comparations_query = 0; // zera compara��es...
  while (wordtoquery(line, LINE_SIZE, query, &word)) {
    Word = bst_get(tree, word, &stats.comparations_query);
    wordtooutput(output, &Word, word);
    fprintf(output, "\n");
  }

  return stats;
}
// coloca em um arquivo de escrita as estatisticas geradas por fun��es indexandquery
void putstats(FILE *output, STATISTICS_T *stats) {
  fprintf(output, "\n********** Estat�sticas da Indexa��o **********\n");
  fprintf(output, "nodos = %d\n", stats->nodes);
  fprintf(output, "compara��es = %lu\n", stats->comparations_index);
  fprintf(output, "rota��es = %d\n", stats->rotations);
  fprintf(output, "altura da �rvore = %d\n", stats->height);
  fprintf(output, "tempo decorrido = %.3f s\n", stats->elapsed_index);

  fprintf(output, "\n********** Estat�sticas das Consultas **********\n");
  fprintf(output, "compara��es = %lu\n", stats->comparations_query);
  fprintf(output, "tempo decorrido = %.3f s\n", stats->elapsed_query);
  if (stats->elapsed_query != stats->elapsed_query_average) {
    fprintf(output, "tempo decorrido (m�dia) = %.3f s\n", stats->elapsed_query_average);
  }
}
void putstattimes(FILE *output, int times) {
  fprintf(output, "\n*A m�dia para o tempo decorrido foi tirada de uma repeti��o de %dx o arquivo de consulta.", times);
}

// calcula a diferen�a entre o clock atual e um clock salvo antes
double clock_diff(clock_t clock_start) {
  return (double)(clock() - clock_start) / MILLISEC;
}

