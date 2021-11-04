#include <stdio.h>
#include <string.h>

#include "Util.h"
#include "Arvore.h"
#include "Fila.h"

#include "Sugere.h"

void imprimeSugestao(No *raiz, char *palavra){
    if(raiz){
        if(distanciaEdicao( getPalavra(raiz), palavra) < 2 )
            printf("%s ", getPalavra(raiz));
        else{
            imprimeSugestao(getEsquerda(raiz), palavra);
            imprimeSugestao(getDireita(raiz), palavra);
        }
    }
}