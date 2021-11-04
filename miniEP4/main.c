#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"

int listaVazia(Lista *l){
    return (l->inicio == NULL);
}
void insereLista(Lista *l, int valor) {
    No *no = malloc(sizeof(No));
    no->id = valor;
    no->proximo = NULL;
    if(listaVazia(l)) {
        no->proximo = l->inicio;
        l->inicio = l->fim = no;
    }
    else {
        No *atual = l->inicio;
        No *anterior = NULL;
        while (atual && atual->id < no->id){
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == l->inicio) {
            no->proximo = l->inicio;
            l->inicio = no;
        }
        else if (atual == NULL) {
            anterior->proximo = no;
            l->fim = no;
        }
        else {
            anterior->proximo = no;
            no->proximo = atual;
        }
    }
}
void imprimeLista(Lista *l) {
      No *atual = l->inicio;
      while (atual != l->fim) {
          printf("%d->", atual->id);
          atual = atual->proximo;
      }
      if(atual){
        printf("%d",atual->id);
      }
      //printf("NULL");
}
void liberaLista(Lista* l) {
        No* atual = l->inicio;
        if(listaVazia(l)){
            return;
        }
        while (atual != NULL) {
            No* t = atual->proximo;
            free(atual);
            atual = t;
        }
        free(l);
        l = NULL;
}
int main(){
  Lista *l1 = criaLista();
  insereLista(l1,151);
  insereLista(l1,277);
  insereLista(l1,630);
  insereLista(l1,639);
  Lista *l2 = criaLista();
  insereLista(l2,53);
  printf("--------------------- Lista 1 -----------------------\n");
  imprimeLista(l1);
  printf("\n-----------------------------------------------------\n");
  printf("--------------------- Lista 2 -----------------------\n");
  imprimeLista(l2);
  printf("\n");
  printf("-----------------------------------------------------\n");
  printf("\n");
  Lista *LJ = juntaLista(l1,l2);
  printf("--------------------- Lista Juntada -----------------\n");
  imprimeLista(LJ);
    printf("\n");
  printf("-----------------------------------------------------\n");
  free(l1);
  free(l2);
  liberaLista(LJ);


}
