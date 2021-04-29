#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TAD/avl.h"
#include "TAD/word.h"
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

int roda_base(char *inputfile_name, char *searchfile_name, char *outputfile_name) {
  setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
  FILE * input;
  FILE * search;
  FILE * output;
  AVL_T *tree = avl_init();
  int ok = 0;
  char *word, line[300], *id; // linhas a serem lidas do arquivo
  char sepparator[]= {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
  int id_number;
  Word_T *palavra = word_init();
  Mention_T *mencoes;

  // test if input file exists
  if (!(input=fopen(inputfile_name,"r"))) {
    printf("error on trying to open file %s \n",inputfile_name);
    return 1;
  }
  // ..................................
  if (!(search=fopen(searchfile_name,"r"))) {
    printf("error on trying to open file %s \n",searchfile_name);
    return 1;
  }
  // test create output file
  if (!(output=fopen(outputfile_name,"w"))) {
    printf("error on trying to create file %s \n",outputfile_name);
    return 1;
  }
  Word_T *guarda;

  // each line of input file
  while (fgets(line,1000,input)) {
    id = strtok(line, ";"); // get tweet id
    id_number = atoi(id); // converts id in string to int
    //fprintf(output,"%d;%", id_number);

    word = strtok(NULL, sepparator); // get tweet first word

    // while find words on tweet...
    while (word != NULL) {
      ok = 0;
      wordtolowercase(word); // convert word to lowercase
      avl_insert(&tree, word, &ok, &guarda);
      word_add_mention(&guarda, id_number);
      //fprintf(output," %s", word); // put the word in output file
      word = strtok(NULL, sepparator); // tweet get the next word of tweet
    }
    //fprintf(output,"\n%");
  }

//
//  guarda = avl_search(tree, "ir");
//  printf("%d", guarda->mentions->id);
//      printf("|%d|", guarda->mentions->id);
  while (fgets(line,1000,search)) {
    word = strtok(line, sepparator);
    fprintf(output,"consulta: %s Palavra ", word);
    if (palavra = avl_search(tree, word)) {
      fprintf(output, "encontrada nos tweets");
      for (mencoes = palavra->mentions; mencoes != NULL; mencoes = mencoes->next) {
        fprintf(output, " %d,", mencoes->id);
      }
    } else {
      fprintf(output, "não encontrada");
    }
    fprintf(output, "\n");
  }

  // close files input and output
  fclose(input);
  fclose(output);
  return 0;
}


int main (int argc, char *argv[]) {
  setlocale(LC_ALL,"");
/*
  FILE * input;
  FILE * search;
  FILE * output;
*/
/*
  */
/*
  Word_T *palavra = word_init();
  word_set(&palavra, "palavra");
  word_add_mention(&palavra, 3);
  word_add_mention(&palavra, 4);
  word_add_mention(&palavra, 6);
  Mention_T* mentions;
  for(mentions = palavra->mentions; mentions != NULL; mentions = mentions->next) {
    printf("%d ", mentions->id);
  }
  */
/*
  int ok = 0;
  AVL_T *tree = avl_init();
  Word_T *guarda;
  Mention_T* mentions;

  avl_insert(&tree, "idiota", &ok, &guarda);
  printf("(%p)", guarda);
  word_add_mention(&guarda, 3);
  word_add_mention(&guarda, 6);
  printf(" [%s] ", (guarda));

  avl_insert(&tree, "pota", &ok, &guarda);
  printf("(%p)", guarda);
  word_add_mention(&guarda, 7);
  word_add_mention(&guarda, 9);

  printf(" [%s] ", (guarda));

  Word_T* palavra = guarda;

  for(mentions = palavra->mentions; mentions != NULL; mentions = mentions->next) {
    printf("%d ", mentions->id);
  }

//  avl_print(tree);

*/
  roda_base("base_completa.csv", "consulta_100.txt", "output.txt");

//  avl_printwithlevel(tree);

  //print(tree);
//  printf("%d", strcmp("b", "a"));
//  loadfiles(argc, argv, input, search, output);

//  closefiles(input, search, output);
  return 0;
}
