#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Fila.h"

typedef struct nofila{
    char *palavra;
    struct nofila *proximo;
}NoFila;

typedef struct fila{
    NoFila *inicio;
    NoFila *fim;
    int n;
}Fila;

NoFila *criaNoFila(){
    NoFila *no = malloc(sizeof(NoFila));
    no->palavra = NULL;
    no->proximo = NULL;
    return no;
}

Fila *criaFila(){
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = fila->fim = NULL;
    fila->n = 0;
    return fila;
}

void liberaNoFila(NoFila *no){
    if(no != NULL){
        liberaNoFila(no->proximo);
        free(no->palavra);
        free(no);
    }
}

void liberaFila(Fila *fila){
    NoFila *aux = fila->inicio;
    while(!filaVazia(fila)){
        dequeue(fila);
        aux = front(fila);
    }
    free(fila);
    fila = NULL;
}

int getTamanhoFila(Fila *fila){
    if(filaVazia(fila))
        return 0;
    return fila->n;
}

void enqueue(Fila *fila, char *palavra){
    NoFila *no = malloc(sizeof(NoFila));
    no->palavra = malloc(sizeof(char) * (strlen(palavra) +1) );
    strcpy(no->palavra, palavra);
    no->proximo = NULL;
    if(filaVazia(fila))
        fila->inicio = fila->fim = no;
    else{
        fila->fim->proximo = no;
    }
    fila->fim = no;
    fila->n++;
}

void dequeue(Fila *fila){
    if(!filaVazia(fila)){
        NoFila *aux = fila->inicio;
        fila->inicio = fila->inicio->proximo;
        fila->n--;
        free(aux->palavra);
        free(aux);
    }
}

NoFila *front(Fila *fila){
    if(filaVazia(fila))
        return NULL;
    return fila->inicio;
}

bool filaVazia(Fila *fila){
    if(fila->n == 0 || fila == NULL)
        return true;
    else
        return false;
}

void imprimePalavra(NoFila *no){
    printf("%s ", no->palavra);
}

char *palavraFront(Fila *fila){
    if(filaVazia(fila))
        return NULL;
    return fila->inicio->palavra;
}

bool buscaPalavraFila(Fila *fila, char *palavra){
    if(filaVazia(fila))
        return false;
    NoFila *no = front(fila);
    while(no != NULL){
        if(strcmp(no->palavra, palavra) == 0)
            return true;
        no = no->proximo;
    }
    free(no);
    return false;
}
