#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void wordtolowercase(char *s) {
  int i;
  for (i=strlen(s); i>=0; i--) {
    s[i]=tolower(s[i]);
  }
}

int tokenizer(char *inputfile_name, char *outputfile_name) {
  setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados
  FILE * input;
  FILE * output;

  char *word, line[300], *id; // linhas a serem lidas do arquivo
  char sepparator[]= {" 0123456789,.&*%\?!;/-'@\"$#=~><()][}{:\n\t_"}; //caracteres separadores para as palavras
  int id_number;

  // test if input file exists
  if (!(input=fopen(inputfile_name,"r"))) {
    printf("error on trying to open file %s \n",inputfile_name);
    return 1;
  }
  // test create output file
  if (!(output=fopen(outputfile_name,"w"))) {
    printf("error on trying to create file %s \n",outputfile_name);
    return 1;
  }

  // each line of input file
  while (fgets(line,1000,input)) {
    id = strtok(line, ";"); // get tweet id
    id_number = atoi(id); // converts id in string to int
    fprintf(output,"%d;%", id_number);

    word = strtok(NULL, sepparator); // get tweet first word

    // while find words on tweet...
    while (word != NULL) {
      wordtolowercase(word); // convert word to lowercase
      fprintf(output," %s", word); // put the word in output file
      word = strtok(NULL, sepparator); // tweet get the next word of tweet
    }
    fprintf(output,"\n%");
  }
  // close files input and output
  fclose(input);
  fclose(output);
  return 0;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

int loadfiles(int argc, char *argv[], FILE **input, FILE **search, FILE **output) {
  if (argc!=4) {
    printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: %s <arq_entrada> <arq_consulta> <arq_saida>\n",argv[0]);
    return 4;
  }
  // test if input file exists
  if (!(*input=fopen(argv[1],"r"))) {
    printf("error on trying to open file %s \n",argv[1]);
    return 3;
  }
  // test if search file exists
  if (!(*search=fopen(argv[2],"r"))) {
    printf("error on trying to open file %s \n",argv[2]);
    return 2;
  }
  // test create output file
  if (!(*output=fopen(argv[3],"w"))) {
    printf("error on trying to create file %s \n",argv[3]);
    return 1;
  }

  return 0;
}
