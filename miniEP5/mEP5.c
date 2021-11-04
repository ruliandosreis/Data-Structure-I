#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util.h"
#include "Objetos.h"
#include "Lista.h"
#include "mEP5.h"

/**
 * @brief Verifica se a lista com a expressão matemática (que pode contér números e simbolos)
 * é uma expressão válida. Além disso, ela também deve verificar se os operados são válidos,
 * ou seja, se são '+' ou '-' (únicos que serão considerados válidos nesse miniEP).
 * Uma expressão deve ser considerada inválida se:
 * - Houver a leitura de dois objetos seguidos do mesmo tipo (por exemplo, dois objetos do tipo STR
 *   ou dois objetos numéricos);
 * - Terminar com um operador;
 * - Se o operador não for soma (+) ou subtração (-).
 *
 * @param expressao: lista encadeada com os itens (números e possíveis operadores)
 * @return true ou false
 */

bool expressaoValida(Lista *expressao) {
    Objeto *aux = getPrimeiro(expressao);
    int tamanho = tamanhoLista(expressao);
    /*
      * VERIFICA SE, CASO A LISTA TENHA APENAS UM ELEMENTO, O MESMO NÃO É UM OPERADOR
    */
    if(tamanho == 1){
        if(aux->tipo != INT && aux->tipo != FLOAT)
            return false;
    }
    /*
      * PERCORRE ATÉ O PENÚLTIMO ELEMENTO DA LISTA VERIFICANDO SE OS TIPOS DOS OBJETOS
      * EM SEQUENCIA SÃO OS MESMOS E CONFERE SE OS OPERADORES SÃO APENAS "+" OU "-"
    */
    for(int i=0; i < tamanho-1; i++){
        if(aux->tipo == aux->proximo->tipo)
            return false;
        else if(aux->tipo == STR){
            if(strcmp(aux->item.vString, "+") != 0 && strcmp(aux->item.vString,"-") != 0)
                return false;
        }
        aux = aux->proximo;
    }
    /*
      * VERIFICA O ÚLTIMO ELEMENTO DA LISTA E CONFERE SE O MESMO NÃO É UM OPERADOR
    */
    if(aux->tipo == STR)
        return false;
    return true;
}

/**
 * @brief Calcula o valor da expressão presente em 'expressão'. Supõem-se que a
 * expressão é válida.
 *
 * Exemplos:
 * - 10 = -10
 * 10 = 10
 * 10 + -15 = -5 (o '-15' significa o número inteiro -15 e não o operador '-' seguido do número 15)
 * - 10 + 15 = 5
 * -10 - -15 = 5
 * - -10 - -15 = 25
 * + 10 + -15 = -5
 * 3.5 + 10 = 13.5 (note que se um valor for real, o resultado final deve ser real)
 *
 * @param expressao: lista encadeada com os itens (números e possíveis operadores)
 * @return Objeto*
 */
Objeto *avaliaExpressao(Lista *expressao) {
    Objeto *resultado = criaObjeto();
    Objeto *aux = getPrimeiro(expressao);
    int tamanho = tamanhoLista(expressao);

    if(tamanho == 1){
        // SE O UNICO ELEMENTO FOR INTEIRO
        if(aux->tipo == INT){
            resultado->item.vInt = aux->item.vInt;
            resultado->tipo = INT;
        }
        // SE O UNICO ELEMENTO FOR FLOAT
        else{
            resultado->item.vFloat = aux->item.vFloat;
            resultado->tipo = FLOAT;
        }
    }
    else if(tamanho == 2){
        // SE O TAMANHO FOR 2 SIGNIFICA QUE O PRIMEIRO *DEVE* SER UM STR, CASO CONTRARIO, APENAS TERÃO CASOS INVÁLIDOS
        // SE FOR POSITIVO
        if(strcmp(aux->item.vString, "+") == 0){
            // SE O SEGUNDO FOR UM INTEIRO
            if(aux->proximo->tipo == INT){
                resultado->item.vInt = aux->proximo->item.vInt;
                resultado->tipo = INT;
            }
            // SE O SEGUNDO FOR UM FLOAT
            else{
                resultado->item.vFloat = aux->proximo->item.vFloat;
                resultado->tipo = FLOAT;
            }
        }
        else{
            // SE O SEGUNDO FOR UM INTEIRO
            if(aux->proximo->tipo == INT){
                resultado->item.vInt = (-1) * aux->proximo->item.vInt;
                resultado->tipo = INT;
            }
            // SE O SEGUNDO FOR UM FLOAT
            else{
                resultado->item.vFloat = (-1) * aux->proximo->item.vFloat;
                resultado->tipo = FLOAT;
            }
        }
    }
    else{
        /*
        * ANÁLISE PARA UMA LISTA COM 3 OU MAIS OBJETOS
        */
        while(aux->proximo != NULL){
            /*
            * SE O PRIMEIRO OBJETO FOR UM INTEIRO
            */
            if(aux->tipo == INT){
                resultado->item.vInt = aux->item.vInt;
                /*
                * ANALISE DE SINAIS DO SEGUNDO OBJETO
                */
                // SE FOR POSITIVO
                if(strcmp(aux->proximo->item.vString, "+") == 0){
                    // SE O TERCEIRO ELEMENTO FOR UM INTEIRO
                    if(aux->proximo->proximo->tipo == INT){
                        resultado->item.vInt = resultado->item.vInt + aux->proximo->proximo->item.vInt;
                        resultado->tipo = INT;
                        aux->proximo->proximo->item.vInt = resultado->item.vInt;
                    }
                    // SE O TERCEIRO ELEMENTO FOR UM FLOAT
                    else{
                        resultado->item.vFloat = resultado->item.vInt + aux->proximo->proximo->item.vFloat;
                        resultado->tipo = FLOAT;
                        aux->proximo->proximo->item.vFloat = resultado->item.vFloat;
                    }
                }
                // SE FOR NEGATIVO
                else{
                    // SE O TERCEIRO ELEMENTO FOR UM INTEIRO
                    if(aux->proximo->proximo->tipo == INT){
                        resultado->item.vInt = resultado->item.vInt - aux->proximo->proximo->item.vInt;
                        resultado->tipo = INT;
                        aux->proximo->proximo->item.vInt = resultado->item.vInt;
                    }
                    // SE O TERCEIRO ELEMENTO FOR UM FLOAT
                    else{
                        resultado->item.vFloat = resultado->item.vInt -aux->proximo->proximo->item.vFloat;
                        resultado->tipo = FLOAT;
                        aux->proximo->proximo->item.vFloat = resultado->item.vFloat;
                    }
                }
                aux = aux->proximo->proximo;
                if(resultado->tipo == INT){
                    aux->tipo = INT;
                }
                else{
                    aux->tipo = FLOAT;
                }
            }
            /*
            * SE O PRIMEIRO OBJETO FOR UM FLOAT
            */
            else if(aux->tipo == FLOAT){
                resultado->tipo = FLOAT;
                resultado->item.vFloat = aux->item.vFloat;
                /*
                * ANALISE DE SINAIS DO SEGUNDO OBJETO
                */
                // SE FOR POSITIVO
                if(strcmp(aux->proximo->item.vString, "+") == 0){
                    // SE O TERCEIRO ELEMENTO FOR UM INTEIRO
                    if(aux->proximo->proximo->tipo == INT){
                        resultado->item.vFloat = resultado->item.vFloat + aux->proximo->proximo->item.vInt;
                        resultado->tipo = FLOAT;
                    }
                    // SE O TERCEIRO ELEMENTO FOR UM FLOAT
                    else{
                        resultado->item.vFloat = resultado->item.vFloat + aux->proximo->proximo->item.vFloat;
                        resultado->tipo = FLOAT;
                    }
                }
                // SE FOR NEGATIVO
                else{
                    // SE O TERCEIRO ELEMENTO FOR UM INTEIRO
                    if(aux->proximo->proximo->tipo == INT){
                        resultado->item.vFloat = resultado->item.vFloat - aux->proximo->proximo->item.vInt;
                        resultado->tipo = FLOAT;
                    }
                    // SE O TERCEIRO ELEMENTO FOR UM FLOAT
                    else{
                        resultado->item.vFloat = resultado->item.vFloat - aux->proximo->proximo->item.vFloat;
                        resultado->tipo = FLOAT;
                    }
                }
                // TERCEIRO OBJETO RECEBE O RESULTADO
                aux->proximo->proximo->item.vFloat = resultado->item.vFloat;
                aux = aux->proximo->proximo;
                aux->tipo = FLOAT;
            }
            /*
            * SE O PRIMEIRO OBJETO FOR UM STR
            */
            else{
                // SE FOR POSITIVO
                if(strcmp(aux->item.vString, "+") == 0){
                    // SE O SEGUNDO OBJETO FOR UM INT
                    if(aux->proximo->tipo == INT){
                        resultado->tipo = INT;
                        resultado->item.vInt = aux->proximo->item.vInt;
                        aux->proximo->item.vInt = resultado->item.vInt;
                    }
                    // SE O SEGUNDO OBJETO FOR UM FLOAT
                    else{
                        resultado->tipo = FLOAT;
                        resultado->item.vFloat = aux->proximo->item.vFloat;
                        aux->proximo->item.vFloat = resultado->item.vFloat;
                    }
                }
                // SE FOR NEGATIVO
                else{
                    // SE O SEGUNDO OBJETO FOR UM INT
                    if(aux->proximo->tipo == INT){
                        resultado->tipo = INT;
                        resultado->item.vInt = (-1) * aux->proximo->item.vInt;
                        aux->proximo->item.vInt = resultado->item.vInt;
                    }
                    // SE O SEGUNDO OBJETO FOR UM FLOAT
                    else{
                        resultado->tipo = FLOAT;
                        resultado->item.vFloat = (-1) * aux->proximo->item.vFloat;
                        aux->proximo->item.vFloat = resultado->item.vFloat;
                    }
                }
                aux = aux->proximo;
                if(resultado->tipo == INT){
                    aux->tipo = INT;
                }
                else{
                    aux->tipo = FLOAT;
                }
            }
        }
    }
    return resultado;
}