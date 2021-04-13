#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TAD/avl.h"

int loadfiles(int argc, char *argv[], FILE *input, FILE *search, FILE *output) {
  if (argc!=4) {
    printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: %s <arq_entrada> <arq_consulta> <arq_saida>\n",argv[0]);
    return 1;
  }
  // test if input file exists
  if (!(input=fopen(argv[1],"r"))) {
    printf("error on trying to open file %s \n",argv[1]);
    return 2;
  }
  // test if search file exists
  if (!(search=fopen(argv[2],"r"))) {
    printf("error on trying to open file %s \n",argv[2]);
    return 3;
  }
  // test create output file
  if (!(output=fopen(argv[3],"w"))) {
    printf("error on trying to create file %s \n",argv[3]);
    return 4;
  }

  return 0;
}
void closefiles(FILE *input, FILE *search, FILE *output) {
  fclose(input);
  fclose(search);
  fclose(output);
}

int main (int argc, char *argv[]) {
  setlocale(LC_ALL,"");
/*
  FILE * input;
  FILE * search;
  FILE * output;
*/

  int ok = 0;
  AVL_T *tree = Init();
  insert(&tree, "pedro", &ok);
  insert(&tree, "paulo", &ok);
  insert(&tree, "paula", &ok);
  insert(&tree, "pauli", &ok);
  insert(&tree, "aranha", &ok);

  printwithlevel(tree);

  //print(tree);
//  printf("%d", strcmp("b", "a"));
//  loadfiles(argc, argv, input, search, output);

//  closefiles(input, search, output);
  return 0;
}
