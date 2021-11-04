#ifndef EP3_ARVORE_H
#define EP3_ARVORE_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct no No;

No *criaNo(char *);

No *buscaNo(No *, char *);

int max(int , int );

char *getPalavra(No *);

No *getEsquerda(No *);

No *getDireita(No *);

int getAltura(No *);

void liberaArvore(No *);

void imprimeArvore(No *);

No *insereABB(No *, No *);

No *removeABB(No *, char *);

int getFatorBalanceamento(No *);

No *rotacaoEsquerda(No *);

No *rotacaoDireita(No *);

No *insereAVL(No *, No *);

No *removeAVL(No *, char *);

bool estaNaArvore(No *, char *);

#endif