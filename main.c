#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "TAD/avl.h"
#include "TAD/word.h"
#include "helpers.h"

int main (int argc, char *argv[]) {
  setlocale(LC_ALL,"");
  FILE *input, *search, *output;

  //char *argx[] = {"nadinha", "test/base_100.txt", "test/consulta_100.txt", "output.txt"};
  //argc = 4;
  if (loadfiles(argc, argv, &input, &search, &output) == 0) {
    avl_query(input, search, output);
    fclose(input);
    fclose(search);
    fclose(output);
  }

  return 0;
}
