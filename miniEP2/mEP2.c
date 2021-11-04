/*
  Rulian Dos Reis
  Estrutura de Dados I   2021/1
  24/06/2021
  mEP2.c
*/

/*  IMPORTAÇÃO DE BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>

int main(){
  int ordemMatrizes;
  scanf("%d",&ordemMatrizes);

  /* aloca dinamicamente o vetor p */
  int *p = malloc(ordemMatrizes * sizeof(int));

  /* recebe o vetor p equivalente à matriz de permutação */
  for(int i=0; i < ordemMatrizes; i++){
    scanf("%d", &p[i]);
  }

  /* aloca a matriz B dinamicamente */
  int **B = malloc(ordemMatrizes * sizeof(int*));
  for(int j=0; j<ordemMatrizes; j++)
      B[j] = malloc (ordemMatrizes * sizeof(int));

  for(int i=0; i<ordemMatrizes; i++)
    for(int j=0; j<ordemMatrizes; j++){
      scanf("%d", &B[i][j]);
    }

  /* imprime a matriz resultante*/
  for(int i=1; i<=ordemMatrizes; i++){
    int cont;
    for(cont=0; p[cont]!=i; cont++);
    for(int j=0; j<ordemMatrizes; j++)
      printf("%d ", B[cont][j]);
    printf("\n");
  }

  /* libera a memória alocada para as matrizes */
  for (int i=0; i<ordemMatrizes; i++ )
    free(B[i]);
  free(B);
  free(p);
  return 0;
}
