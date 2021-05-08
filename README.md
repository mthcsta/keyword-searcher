# Keyword Searcher
Este projeto foi feito com objetivo de fazer uma comparação entre árvores binárias de busca balanceada. As árvores escolhidas para o projeto foram BST (*Binary Search Tree*, em português, ABP ou *Árvore Binária de Pesquisa*)  e AVL (*Adelson Velsky e Landis*).

## Executar programa
clique no arquivo `executa-programa.bat` para uma forma mais fácil de testar o programa.

## Forma de comparação
A comparação é dividida duas etapas:

### Indexação
Nesta etapa o programa faz a leitura de um arquivo **CSV** (padrão separando os dados por ponto e vírgula), captura uma linha do arquivo e faz a inserção das palavras ainda não indexadas na árvore. 

### Consulta
Nesta etapa o programa faz a leitura de um arquivo de texto contendo uma palavra por linha, captura a palavra e verifica se ela foi indexada na árvore criada anteriormente.

### Saída
Parte desta etapa é feita durante a etapa de consulta. Tem dois casos diferentes para cada palavra consultada:
##### Caso a palavra for encontrada
é informado no arquivo de saída os tweets em que a palavra foi mencionada.
##### Caso a palavra não for encontrada
é informado no arquivo de saída que a palavra não foi encontrada.
Por fim, é dado estatísticas da árvore como quantidade de nodos criados, comparações feitas durante indexação e consulta, e as rotações feitas. 

## Estruturas
Para a implementação do projeto foram precisas 5 estruturas
**WORD**: contém uma string com a palavra e um ponteiro para a estrutura MENTION, uma LSE(Lista Simplesmente Encadeada) com as menções a palavra.
**MENTION**: contem um INT que guarda um id de tweet e um ponteiro para outro MENTION
**AVL**: árvore AVL com a parte do dado sendo do tipo WORD
**BST**: árvore BST(ou ABP) com a parte do dado sendo do tipo WORD
**STATISTICS**: contem as estatísticas usadas para a comparação

## Implementação
Todo o projeto tem variaveis e funções definidos em inglês para manter um padrão para o código todo. Para este projeto foi utilizada as árvores AVL e BST dadas em aula com modificações, tendo sido modificado cada nome de função para o inglês. A árvore AVL foi modificada para ter como entrada **WORD** e **STATISTICS** e retorno **WORD** em algumas funções, também foi necessário adicionar uma condição em caso a palavra já existir na árvore. A árvore BST teve as mesmas modificações que a AVL, com o diferencial de que também foi modificada a parte de busca/inserção, sendo feita uma função para ambas que percorre a árvore até encontrar ou um fim ou uma palavra. 

## Resultados
Abaixo 3 tabelas com os resultados tirados das estatísticas geradas.

| indexação | **AVL** (100) | **BST** (100) | **AVL** (10k) | **BST** (10k) | **AVL** (900k) | **BST** (900k) |  
|----|-----|----|----|----|----|----|
| nodos | 704 | 704 | 15542 | 15542 | 174346 | 174346 |
| comparações | 11196 | 11478 | 1391862 | 1398596 | 131249844 | 124073420 |
| rotações | 500 | 0  | 11105 | 0 | 123929 | 0 | 
| altura da árvore | 11 | 22 | 17 | 34 | 21 | 45 |
| tempo decorrido | 1 ms | 0 ms | 52 ms | 38 ms | 4.661 ms | 3.629 ms |

| 10 consultas | **AVL** (100) | **BST** (100) | **AVL** (10k) | **BST** (10k) | **AVL** (900k) | **BST** (900k) |  
|----|-----|----|----|----|----|----|
| comparações | 82 | 98 | 87 | 97 | 91 | 97 |
| tempo decorrido | 0 ms | 0 ms | 1 ms | 1 ms | 120 ms | 106 ms |

| 1000 consultas | **AVL** (100) | **BST** (100) | **AVL** (10k) | **BST** (10k) | **AVL** (900k) | **BST** (900k) |  
|----|-----|----|----|----|----|----|
| comparações | 9745 | 11486 | 13242 | 16915 | 14705 | 16915 |
| tempo decorrido | 3 ms | 0 ms | 3 ms | 5 ms | 261 ms | 254 ms |

## Referências
* AVL e ABP(BST) tiradas dos slides passados em aula
