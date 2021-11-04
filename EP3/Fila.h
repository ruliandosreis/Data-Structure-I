#ifndef EP3_FILA_H
#define EP3_FILA_H

#include <stdio.h>
#include <string.h>

typedef struct nofila NoFila;

typedef struct fila Fila;

NoFila *criaNoFila();

Fila *criaFila();

void liberaNoFila(NoFila *);

void liberaFila(Fila *);

int getTamanhoFila(Fila *);

void enqueue(Fila *, char *);

void dequeue(Fila *);

NoFila *front(Fila *);

bool filaVazia(Fila *);

void imprimePalavra(NoFila *);

char *palavraFront(Fila *);

bool buscaPalavraFila(Fila *, char *);

#endif