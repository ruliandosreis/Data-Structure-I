#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"

Lista *criaLista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

Lista *juntaLista(Lista *l1, Lista *l2) {
    Lista *resultado = criaLista();
    /*
     * Sua tarefa é, entre outras, implementar o código dessa função que junta duas listas ordenadas de forma que
     * a lista resultante ('resultado') esteja ordenada.
     * Os elementos de l1 e l2, se existirem, sempre estarão ordenados (do menor para o maior de acordo com a id do nó).
     *
     * Lembre-se que você não pode fazer alocação dinâmica/estática de novos nós (usando malloc), mas você pode
     * criar novos ponteiros para os nós das listas. Além disso, com exceção da função criaLista, a função
     * juntaLista não pode utilizar/chamar outras funções do TAD Lista, ou seja, todo o código de manipulação dos
     * elementos da lista devem ser feitos dentro da função juntaLista.
     *
     * A função deve ter complexidade O(n)
     *
     * Exemplos de entrada:
     * l1 = 1->2->5->10
     * l2 = 3->7->8->11
     * Resultado esperado:
     * resultado = 1->2->3->5->7->8->10->11
    */
    int aux1, aux2;

    // VERIFICAÇÃO DE LISTA VAZIA //
    if(l1->inicio == NULL && l2->inicio == NULL){
        return resultado;
    }
    if(l1->inicio == NULL){
        resultado->inicio = l2->inicio;
        resultado->fim = l2->inicio;
        l2->inicio = l2->inicio->proximo;
        while(l2->inicio != NULL){
            resultado->fim->proximo = l2->inicio;
            resultado->fim = resultado->fim->proximo;
            l2->inicio = l2->inicio->proximo;
        }
        return resultado;
    }else if(l2->inicio == NULL){
        resultado->inicio = l1->inicio;
        resultado->fim = l1->inicio;
        l1->inicio = l1->inicio->proximo;
        while(l1->inicio != NULL){
            resultado->fim->proximo = l1->inicio;
            resultado->fim = resultado->fim->proximo;
            l1->inicio = l1->inicio->proximo;
        }
        return resultado;
    }

    aux1 = l1->inicio->id;
    aux2 = l2->inicio->id;

    // COMPARAÇÃO INICIAL //

    if(aux1 < aux2){
        resultado->inicio = l1->inicio;
        resultado->fim = l1->inicio;

        l1->inicio = l1->inicio->proximo;

    }else{
        resultado->inicio = l2->inicio;
        resultado->fim = l2->inicio;

        l2->inicio = l2->inicio->proximo;
    }

    // LAÇO DE REPETIÇÃO //

    while(l1->inicio != NULL  &&  l2->inicio !=NULL){
        aux1 = l1->inicio->id;
        aux2 = l2->inicio->id;
        if (aux1 < aux2){
            resultado->fim->proximo = l1->inicio;
            resultado->fim = resultado->fim->proximo;
            l1->inicio = l1->inicio->proximo;
        }else{
            resultado->fim->proximo = l2->inicio;
            resultado->fim = resultado->fim->proximo;
            l2->inicio = l2->inicio->proximo;
        }
    }

    if(l1->inicio == NULL){
        while(l2->inicio != NULL){
            resultado->fim->proximo = l2->inicio;
            resultado->fim = resultado->fim->proximo;
            l2->inicio = l2->inicio->proximo;
        }
    }else{
        while(l1->inicio != NULL){
            resultado->fim->proximo = l1->inicio;
            resultado->fim = resultado->fim->proximo;
            l1->inicio = l1->inicio->proximo;
        }
    }
    return resultado;
}
