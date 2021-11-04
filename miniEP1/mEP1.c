/*
  Rulian Dos Reis
  Estrutura de Dados I   2021/1
  24/06/2021
*/

/*  IMPORTAÇÃO DE BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>

int main(){
  
  long int N, a, b, j;
  int M, operacao;
  long int x;

  scanf("%ld %d", &N, &M);

  long int *vetor = calloc(N, sizeof(long int));

  for(int cont = 0; cont < M; cont++){  /* loop para percorrer a quantidade M de operações */
    scanf("%d", &operacao);
    switch( operacao ){
      case 1:
        scanf("%ld %ld %ld", &a , &b , &x);
        for (int i = (a-1); i < b; i++)
          *(vetor + i) += x;
      break;

      case 2:
        scanf("%ld %ld %ld", &a , &b , &x);
        for (int i = (a-1); i < b; i++)
          *(vetor + i) -= x;
      break;

      case 3:
        scanf("%ld", &j);
        printf("%ld", *(vetor + (j-1)));
        printf("\n");
      break;
    }
  }
  free(vetor);
  return 0;
}