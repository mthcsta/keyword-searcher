#define TypeData char
#define MAXWORDSIZE 100
typedef struct AVL {
  char data[MAXWORDSIZE];
  int BF;
  struct AVL *left;
  struct AVL *right;
} AVL_T;


AVL_T* Init();
AVL_T* rotateleft(AVL_T *p);
AVL_T* doublerotateleft(AVL_T *p);
AVL_T* rotateright(AVL_T *p);
AVL_T* doublerotateright(AVL_T* p);
int insert(AVL_T **tree, char x[], int *ok);
AVL_T* Caso1(AVL_T *a , int *ok);
AVL_T* Caso2(AVL_T *a , int *ok);
void print(AVL_T *tree);

void printwithlevelTR(AVL_T *tree, int level);
void printwithlevel(AVL_T *tree);
