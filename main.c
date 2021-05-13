#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "helpers.h"

/*
  padrão para chamada deste programa: programa.exe <arquivo de entrada> <arquivo de consulta> <arquivo de saida> <arvore OU "cmp"> <vezes testa consulta>
  Podendo <arvore> ser: AVL ou BST/ABP
  *<vezes testa consulta> é um parametro opcional por padrão será 1.
*/
int main (int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese");

  int times = 1;
  STATISTICS_T stats_avl, stats_bst;
  FILE *input, *query, *output;

  if (argc < 5) {
    printf("Número incorreto de parâmetros.\nPara chamar o programa digite: %s <arq_entrada> <arq_consulta> <arq_saida> <arvore>\nArvores possiveis: AVL e ABP. \nOBS: também é possível passar CMP para fazer uma comparação das duas árvores.\n",argv[0]);
    return EXIT_FAILURE;
  }
  if (loadfile(&input, argv[1], "r") || loadfile(&query, argv[2], "r") || loadfile(&output, argv[3], "w")) {
    return EXIT_FAILURE;
  }

  // parametro opcional que repete o teste de consulta pelo numero dado.
  // padrão: 1.
  if (argc >= 6) {
    times = atoi(argv[5]);
  }
  // faz entrada do tipo de árvore ser não case-sensitive.
  wordtolowercase(argv[4]);


  if (strcmp(argv[4], "avl") == 0) { // caso a árvore escolhida for AVL
    stats_avl = indexandqueryAVL(input, query, output, times);
    putstats(output, &stats_avl);
    if (times > 1) {
      putstattimes(output, times);
    }
  } else if (strcmp(argv[4], "bst") == 0 || strcmp(argv[4],"abp") == 0) { // caso a árvore escolhida for ABP
    stats_bst = indexandqueryBST(input, query, output, times);
    putstats(output, &stats_bst);
    if (times > 1) {
      putstattimes(output, times);
    }
  } else if (strcmp(argv[4], "cmp") == 0) { // caso foi escolhido uma comparação
    printf("\nrodando AVL...");
    stats_avl = indexandqueryAVL(input, query, output, times); // indexa e consulta na arvore AVL retornando as estatisticas

    // volta para o inicio de cada arquivo usado
    fseek(input, 0, SEEK_SET);
    fseek(query, 0, SEEK_SET);
    fseek(output, 0, SEEK_SET);

    printf("\rrodando ABP...");
    // usa os arquivos novamente, agora para pegar as estatisticas da ABP
    stats_bst = indexandqueryBST(input, query, output, times);

    // coloca as estatisticas das duas árvores no arquivo de saída
    fprintf(output, "\n\n\t\tÁrvore AVL\n");
    putstats(output, &stats_avl);
    fprintf(output, "\n\n\t\tÁrvore ABP\n");
    putstats(output, &stats_bst);
    if (times > 1) {
      putstattimes(output, times);
    }
  } else {
    printf("Erro! árvore não encontrada.\nAs árvores disponíveis são: AVL e ABP");
  }

  fclose(input);
  fclose(query);
  fclose(output);

  return EXIT_SUCCESS;
}
