#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "helpers.h"

/*
  padr�o para chamada deste programa: programa.exe <arquivo de entrada> <arquivo de consulta> <arquivo de saida> <arvore OU "cmp">
  Podendo <arvore> ser: AVL ou BST/ABP
*/
int main (int argc, char *argv[]) {
  setlocale(LC_ALL, "Portuguese");

  STATISTICS_T stats_avl, stats_bst;
  FILE *input, *query, *output;

  if (argc < 5) {
    printf("N�mero incorreto de par�metros.\nPara chamar o programa digite: %s <arq_entrada> <arq_consulta> <arq_saida> <arvore>\nArvores possiveis: AVL e ABP. \nOBS: tamb�m � poss�vel passar CMP para fazer uma compara��o das duas �rvores.\n",argv[0]);
    return EXIT_FAILURE;
  }
  if (loadfile(&input, argv[1], "r") || loadfile(&query, argv[2], "r") || loadfile(&output, argv[3], "w")) {
    return EXIT_FAILURE;
  }

  // faz entrada do tipo de �rvore ser n�o case-sensitive.
  wordtolowercase(argv[4]);


  if (strcmp(argv[4], "avl") == 0) { // caso a �rvore escolhida for AVL
    stats_avl = indexandqueryAVL(input, query, output);
    putstats(output, &stats_avl);
  } else if (strcmp(argv[4], "bst") == 0 || strcmp(argv[4],"abp") == 0) { // caso a �rvore escolhida for ABP
    stats_bst = indexandqueryBST(input, query, output);
    putstats(output, &stats_bst);
  } else if (strcmp(argv[4], "cmp") == 0) { // caso foi escolhido uma compara��o
    printf("\nrodando AVL...");
    stats_avl = indexandqueryAVL(input, query, output); // indexa e consulta na arvore AVL retornando as estatisticas

    // volta para o inicio de cada arquivo usado
    fseek(input, 0, SEEK_SET);
    fseek(query, 0, SEEK_SET);
    fseek(output, 0, SEEK_SET);

    printf("\rrodando ABP...");
    // usa os arquivos novamente, agora para pegar as estatisticas da ABP
    stats_bst = indexandqueryBST(input, query, output);

    // coloca as estatisticas das duas �rvores no arquivo de sa�da
    fprintf(output, "\n\n\t\t�rvore AVL\n");
    putstats(output, &stats_avl);
    fprintf(output, "\n\n\t\t�rvore ABP\n");
    putstats(output, &stats_bst);
  } else {
    printf("Erro! �rvore n�o encontrada.\nAs �rvores dispon�veis s�o: AVL e ABP");
  }

  fclose(input);
  fclose(query);
  fclose(output);

  return EXIT_SUCCESS;
}
