#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Avalia.h"
#include "Categorias.h"
#include "Pilha.h"
#include "Util.h"

/**
 * @brief Faz a avaliação da expressão em notação pós-fixa e retorna o resultado da expressão.
 * A sua função deve examinar cada objeto da fila 'posFixa' e:
 * - Se o objeto for um operando (FLOAT ou INT), empilhar o objeto;
 * - Se o objeto contém um operador, então:
 *   - Desempilhar um ou dois números da pilha, dependendo do tipo do operador;
 *   - Calcular o valor da operação correspondente; e
 *   - Empilhar o valor calculado.
 * Ao final (quando a fila estiver vazia), retorne o objeto (ou uma cópia) do topo da pilha.
 *
 * @param posFixa Fila com os objeto em notação pos-fixa
 * @return Objeto*
 */
Objeto *avalia(Fila *posFixa) {
    Objeto *examina = criaObjeto();
    Pilha *pilha = criaPilha();

    examina = front(posFixa);

    while(front(posFixa)){
        if(examina->categoria == FLOAT || examina->categoria == INT){
            empilha(pilha,examina);
        }
        else{
            if(examina->categoria == OPER_MENOS_UNARIO){
                Objeto *pegaProx = copiaObjeto(topoPilha(pilha));
                desempilha(pilha);
                if(pegaProx->categoria == FLOAT){
                    pegaProx->valor.vFloat = (-1)*pegaProx->valor.vFloat;
                    pegaProx->categoria = FLOAT;
                }
                else{
                    pegaProx->valor.vInt = (-1)*pegaProx->valor.vInt;
                    pegaProx->categoria = INT;
                }
                empilha(pilha,pegaProx);
                free(pegaProx);
            }
            else{
                Objeto *pegaPrimeiro = copiaObjeto(topoPilha(pilha));
                desempilha(pilha);

                Objeto *pegaSegundo = copiaObjeto(topoPilha(pilha));
                desempilha(pilha);

                Objeto *saida = criaObjeto();
                if(examina->categoria == OPER_ADICAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = pegaPrimeiro->valor.vFloat + pegaSegundo->valor.vInt;
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = pegaPrimeiro->valor.vFloat + pegaSegundo->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = pegaPrimeiro->valor.vInt + pegaSegundo->valor.vInt;
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = pegaPrimeiro->valor.vInt + pegaSegundo->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                else if(examina->categoria == OPER_SUBTRACAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = pegaSegundo->valor.vInt - pegaPrimeiro->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = pegaSegundo->valor.vFloat - pegaPrimeiro->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = pegaSegundo->valor.vInt - pegaPrimeiro->valor.vInt;
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = pegaSegundo->valor.vFloat - pegaPrimeiro->valor.vInt;
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                else if(examina->categoria == OPER_MULTIPLICACAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = pegaPrimeiro->valor.vFloat * pegaSegundo->valor.vInt;
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = pegaPrimeiro->valor.vFloat * pegaSegundo->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = pegaPrimeiro->valor.vInt * pegaSegundo->valor.vInt;
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = pegaPrimeiro->valor.vInt * pegaSegundo->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                else if(examina->categoria == OPER_DIVISAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = pegaSegundo->valor.vInt / pegaPrimeiro->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = pegaSegundo->valor.vFloat / pegaPrimeiro->valor.vFloat;
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = pegaSegundo->valor.vInt / pegaPrimeiro->valor.vInt;
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = pegaSegundo->valor.vFloat / pegaPrimeiro->valor.vInt;
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                else if(examina->categoria == OPER_RESTO_DIVISAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = fmod(pegaSegundo->valor.vInt, pegaPrimeiro->valor.vFloat);
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = fmod(pegaSegundo->valor.vFloat, pegaPrimeiro->valor.vFloat);
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = fmod(pegaSegundo->valor.vInt, pegaPrimeiro->valor.vInt);
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = fmod(pegaSegundo->valor.vFloat, pegaPrimeiro->valor.vInt);
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                else if(examina->categoria == OPER_EXPONENCIACAO){
                    if(pegaPrimeiro->categoria == FLOAT){
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vFloat = pow(pegaSegundo->valor.vFloat, pegaPrimeiro->valor.vInt);
                            saida->categoria = FLOAT;
                        }
                        else{
                            saida->valor.vFloat = pow(pegaSegundo->valor.vFloat, pegaPrimeiro->valor.vFloat);
                            saida->categoria = FLOAT;
                        }
                    }
                    else{
                        if(pegaSegundo->categoria == INT){
                            saida->valor.vInt = pow(pegaSegundo->valor.vInt, pegaPrimeiro->valor.vInt);
                            saida->categoria = INT;
                        }
                        else{
                            saida->valor.vFloat = pow(pegaSegundo->valor.vInt, pegaPrimeiro->valor.vFloat);
                            saida->categoria = FLOAT;
                        }
                    }
                    empilha(pilha,saida);
                }
                liberaObjeto(saida);
                free(pegaPrimeiro);
                free(pegaSegundo);
            }
        }
        dequeue(posFixa);
        examina=front(posFixa);
    }
    examina = copiaObjeto(topoPilha(pilha));
    liberaPilha(pilha);
    return examina;
}
