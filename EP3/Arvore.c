#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Arvore.h"

//  sudo setxkbmap -model abnt2 -layout br

typedef struct no{
    char *palavra;
    struct no *esq;
    struct no *dir;
    int altura;
}No;

No *criaNo(char *palavra){
    No *no = malloc(sizeof(No));
    // ALOCA O ESPAÇO DE MEMÓRIA NECESSÁRIO PRA PALAVRA
    char *copiaPalavra = malloc(strlen(palavra)+1);
    // CRIA UMA CÓPIA TRANSFORMANDO O FORMATO PARA *CHAR DA PALAVRA NO ESPAÇO DE MEMÓRIA
    strcpy(copiaPalavra, palavra);
    no->palavra = copiaPalavra;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 0;
    return no;
}

No *buscaNo(No *raiz, char *palavra){
    // CASO A RAIZ SEJA NULA OU ELE TENHA ENCONTRADO A PALAVRA
    if(raiz == NULL || strcmp(raiz->palavra, palavra) == 0)
        return raiz;
    if(strcmp(raiz->palavra, palavra) > 0)
        return buscaNo(raiz->esq, palavra);
    else
        return buscaNo(raiz->dir, palavra);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

char *getPalavra(No *no){
    return no->palavra;
}

No *getEsquerda(No *no){
    return no->esq;
}

No *getDireita(No *no){
    return no->dir;
}

int getAltura(No *no){
    if (no == NULL)
        return -1;
    return no->altura;
}

int getFatorBalanceamento(No *raiz){
    return (getAltura(raiz->esq) - getAltura(raiz->dir));
}

void liberaArvore(No *raiz){
    if(raiz != NULL){
        liberaArvore(raiz->esq);
        liberaArvore(raiz->dir);
        free(raiz->palavra);
        free(raiz);
    }
}

void imprimeArvore(No *raiz){
    if(raiz != NULL){
        printf("%s ",raiz->palavra);
        imprimeArvore(raiz->dir);
        imprimeArvore(raiz->esq);
    }
    printf("\n");
}

No *insereABB(No *raiz, No *no){
    if(raiz == NULL)
        return no;
    if(strcmp(raiz->palavra , no->palavra) > 0)
        raiz->esq = insereABB(raiz->esq, no);
    else
        raiz->dir = insereABB(raiz->dir, no);

    return raiz;
}

No* removeABB(No *raiz, char *chave){
    if(raiz == NULL)
        return NULL;
    if(strcmp(raiz->palavra , chave) > 0){
        raiz->esq = removeABB(raiz->esq, chave);
    }
    else if(strcmp(raiz->palavra , chave) < 0){
        raiz->dir = removeABB(raiz->dir, chave);
    }
    // ACHOU O NÓ A SER REMOVIDO
    else{
        // SE É FOLHA
        if(raiz->dir == NULL && raiz->esq == NULL)
            free(raiz);
        // SE NÃO

        // SE TEM UM UNICO FILHO A ESQUERDA
        else if(raiz->dir == NULL){
            No *aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }
        // SE TEM UM UNICO FILHO A DIREITA
        else if(raiz->esq == NULL){
            No *aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }
        // TEM DOIS FILHOS
        else{
            No *aux = raiz->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            raiz->palavra = aux->palavra;
            aux->palavra = chave;
            raiz->esq = removeABB(raiz->esq, chave);
        }
    }
    // ATUALIZA A ALTURA DA ARVORE
    raiz->altura = max( getAltura(raiz->esq), getAltura(raiz->dir) ) + 1;

    return raiz;
}

No *rotacaoEsquerda(No *raiz){
    No *aux = raiz->dir;

    raiz->dir = aux->esq;
    aux->esq = raiz;

    raiz->altura = max(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;
    aux->altura = max(getAltura(aux->esq), getAltura(aux->dir)) + 1;

    return aux;
}

No *rotacaoDireita(No *raiz){
    No *aux = raiz->esq;

    raiz->esq = aux->dir;
    aux->dir = raiz;

    raiz->altura = max(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;
    aux->altura = max(getAltura(aux->esq), getAltura(aux->dir)) + 1;

    return aux;
}

No *insereAVL(No *raiz, No *novo){
    if (raiz == NULL) return novo;
    if(strcmp(raiz->palavra , novo->palavra) > 0)
        raiz->esq = insereAVL(raiz->esq, novo);
    else
        raiz->dir = insereAVL(raiz->dir, novo);

    raiz->altura = max(getAltura(raiz->esq), getAltura(raiz->dir)) + 1;

    int FB = getFatorBalanceamento(raiz);

    // Rotação RR
    if (FB > 1 && getFatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
    // Rotação LL
    if (FB < -1 && getFatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
    // Rotação LR
    if (FB > 1 && getFatorBalanceamento(raiz->esq) < 0){
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    // Rotação RL
    if (FB < -1 && getFatorBalanceamento(raiz->dir) > 0){
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}

No *removeAVL(No *raiz, char *chave){
    if(raiz == NULL)
        return NULL;
    
    if(strcmp(raiz->palavra , chave) > 0){
        raiz->esq = removeABB(raiz->esq, chave);
    }
    else if(strcmp(raiz->palavra , chave) < 0){
        raiz->dir = removeABB(raiz->dir, chave);
    }
    else{
        // SE É FOLHA
        if(raiz->dir == NULL && raiz->esq == NULL)
            free(raiz);
        // SE NÃO

        // SE TEM UM UNICO FILHO A ESQUERDA
        else if(raiz->dir == NULL){
            No *aux = raiz;
            raiz = raiz->esq;
            free(aux);
        }
        // SE TEM UM UNICO FILHO A DIREITA
        else if(raiz->esq == NULL){
            No *aux = raiz;
            raiz = raiz->dir;
            free(aux);
        }
        // TEM DOIS FILHOS
        else{
            No *aux = raiz->esq;
            while(aux->dir != NULL){
                aux = aux->dir;
            }
            raiz->palavra = aux->palavra;
            aux->palavra = chave;
            raiz->esq = removeABB(raiz->esq, chave);
        }
    }
    // ATUALIZA A ALTURA DA ARVORE
    raiz->altura = max( getAltura(raiz->esq), getAltura(raiz->dir) ) + 1;


    int FB = getFatorBalanceamento(raiz);

    //Rotação RR
    if (FB > 1 && getFatorBalanceamento(raiz->esq) >= 0) 
        return rotacaoDireita(raiz);
    //Rotação LL
    if (FB < -1 && getFatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
    //Rotação LR
    if (FB > 1 && getFatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    //Rotação RL
    if (FB < -1 && getFatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }
    return raiz;
}