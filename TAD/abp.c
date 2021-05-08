#include<string.h>
#include "word.h"
#include "../helpers.h"
#include "bst.h"

BST_T* bst_init() {
  return NULL;
}
BST_T** bst_search(BST_T **tree, char word[], long unsigned int *stats_comparations2) {
  int cmp;
  while (*tree) {
    (*stats_comparations2)++;
    cmp = strcmp(word, (*tree)->data->content);
    if (cmp == 0) {
      return tree;
    }
    if (cmp == -1) {
      tree = &(*tree)->left;
    } else {
      tree = &(*tree)->right;
    }
  }
  return tree;
}

WORD_T* bst_get(BST_T *tree, char word[], long unsigned int *stats_comparations2) {
  if ((tree = *(bst_search(&tree, word, stats_comparations2))) != NULL ) {
    return tree->data;
  }
  return NULL;
}
BST_T* bst_newnode(char *word, BST_T *left, BST_T *right) {
  BST_T* new_node = (BST_T*) malloc(sizeof(BST_T));
  new_node->data = word_init();
  word_insert(&(new_node->data), word);
  new_node->left = left;
  new_node->right = right;
  return new_node;
}
void bst_insert(BST_T **tree, char *word, WORD_T **Word, int *stats_nodes, long unsigned int *stats_comparations) {
  if(*(tree = (bst_search(tree, word, stats_comparations))) == NULL) {
    (*stats_nodes)++;
    *tree = bst_newnode(word, NULL, NULL);
  }
  *Word = (*tree)->data;
  return;
}

int bst_query(FILE *input, FILE *search, FILE *output) {
  BST_T *tree = bst_init();
  int stats_nodes = 0;
  char *word, line[300], *id; // linhas a serem lidas do arquivo
  char sepparator[]= {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
  int id_number;
  MENTION_T *Mentions;
  WORD_T *Word;
  unsigned long int stats_comparations = 0, stats_comparations2 = 0;

  // each line of input file
  while (fgets(line,1000,input)) {
    id = strtok(line, ";"); // get tweet id
    id_number = atoi(id); // converts id in string to int

    word = strtok(NULL, sepparator); // get tweet first word

    // while find words on tweet...
    while (word != NULL) {
      wordtolowercase(word); // convert word to lowercase
      bst_insert(&tree, word, &Word, &stats_nodes, &stats_comparations);
      word_add_mention(&Word, id_number);
      word = strtok(NULL, sepparator); // tweet get the next word of tweet
    }
    //printf("\r%d",id_number);
  }
  //bst_print(tree);
  while (fgets(line,1000,search)) {
    word = strtok(line, sepparator);
    fprintf(output,"consulta: %s Palavra ", word);
    //printf("%s ", word);
    if ((Word = bst_get(tree, word, &stats_comparations2))) {
      fprintf(output, "encontrada nos tweets");
      for (Mentions = mention_invert(Word->mentions); Mentions; Mentions = Mentions->next) {
        fprintf(output, " %d,", Mentions->id);
      }
    } else {
      fprintf(output, "n�o encontrada");
    }
    fprintf(output, "\n");
  }

  fprintf(output, "\n********** Estatísticas da Indexação **************\n");
  fprintf(output, "nodos = %d\ncomparações = %lu\naltura da árvore = %d\n", stats_nodes, stats_comparations, bst_height(tree));
  fprintf(output, "\n********** Estatísticas das Consultas **************\n");
  fprintf(output, "comparações = %lu", stats_comparations2);

  return EXIT_SUCCESS;
}
void bst_print(BST_T *tree) {
  MENTION_T *mentions = NULL;
  if (!tree) return;
  printf("%s, ", tree->data->content);
  for (mentions = tree->data->mentions; mentions; mentions = mentions->next) {
    printf(" %d ", mentions->id);
  }
  printf("\n");
  bst_print(tree->left);
  bst_print(tree->right);
}
int bst_height(BST_T *tree) {
  if (!tree) {
    return -1;
  }
  return 1 + max(bst_height(tree->left), bst_height(tree->right));
}
