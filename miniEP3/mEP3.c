/*
  Rulian Dos Reis
  Estrutura de Dados I   2021/1
  24/06/2021
  mEP2.c
*/

/*  IMPORTAÇÃO DE BIBLIOTECAS */
#include <stdio.h>
#include <stdlib.h>

/* realiza uma busca binaria */
int buscaBinaria(int *p, int tamanho, int valor){
  int inicio = 0;
  int fim = tamanho-1;
  int meio;
  while(inicio <= fim){
    meio = (inicio + fim)/2;

    if(p[meio] == valor){
      return meio;
    }
    else{
      if(valor > p[meio]){
        inicio = meio + 1;
      }
      else{
        fim = meio -1;
      }
    }
  }
  return -1;
}

int main(){
  /* n = numero de casas existentes */
  /* k = valor procurado */
  int n, k;
  /* requisicao da entrada n */
  scanf("%d", &n);

  /* alocacao dinamica do ponteiro que contem os valores inseridos */
  int *p = malloc(n * sizeof(int));
  
  /* definicao dos valores aos elementos do ponteiro*/
  for(int i=0; i<n; i++){
    scanf("%d", &p[i]);
  }

  /* requisicao da entrada k */
  scanf("%d", &k);

  /* inicio do processamento */
  int recebeBusca;
  
  int achou = 0;

  for(int i=0;i<n;i++){
    int aux2 = (k - p[i]);
    recebeBusca = buscaBinaria(p,n,aux2);
    if(recebeBusca != -1){
      printf("SIM\n");
      printf("%d %d",i+1,recebeBusca+1);
      printf("\n");
      achou = 1;
      break;
    }
  }
  if(achou != 1){
    printf("NAO");
    printf("\n");
  }

  free(p);
  return 0;
}