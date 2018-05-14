#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10



/*

Criar estrutura Data p/ fazer os prazos, datas de criação e afins

*/

List addTarefa_inicio(List l, List node){
    node->next=l;
    l=node;
    return l;
}

List addTarefa_fim(List l, List node){
    List act;
    act=(List)malloc(sizeof(No));
    node->next=NULL;
    act=l;
    if(act==NULL){
        act=node;
    }
    while(act->next!=NULL){
        act=act->next;
    }
    act->next=node;
    return l;
}

void leTarefa(TipoTarefa *tarefa){
    printf("\nNome da tarefa: ");
    scanf(" %[^\n]s", tarefa->novaTarefa);
    printf("Identificador: ");
    scanf(" %d", &tarefa->identificador);
    while (!scanf(" %d", &tarefa->identificador))
        fflush(stdin);
    printf("Prioridade (1 a 10): ");
    scanf(" %d", &tarefa->prioridade);
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        while (!scanf(" %d", &tarefa->prioridade ))
            printf("Prioridade inválida, tente novamente (1 a 10): ");
            fflush(stdin);
    }
    printf("Descrição da tarefa: ");
    scanf(" %[^\n]s", tarefa->desc);
    printf("Pessoa a atribuir: ");
    scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
    printf("Prazo: ");
    scanf("%d/%d/%d", &tarefa->conclusao.diac, &tarefa->conclusao.mesc, &tarefa->conclusao.anoc);
 /* verificar se está no ficheiro */

    /*while (!scanf("%d/%d/%d", &tarefa->conclusao.diac, &tarefa->conclusao.mesc, &tarefa->conclusao.anoc)){
        printf("Prazo invalido, tente novamente (dd/mm/aaaa): ");
        fflush(stdin);
    }

    CHECK NOUTRA ALTURA

    */

    printf("\n");
}

void printListaTarefas(List l, int num){
    int i = 1;
    printf("____________________\n", num);
    while(l!=NULL){
        printf("\nTarefa no. %d: %s\nPrioridade: %d\nDescrição da tarefa: %s\nPessoa responsável: %s\nPrazo: %d/%d/%d\n",
               l->tarefa.identificador,
               l->tarefa.novaTarefa,
               l->tarefa.prioridade,
               l->tarefa.desc,
               l->tarefa.pessoa.nomePessoa,
               l->tarefa.conclusao.diac,
               l->tarefa.conclusao.mesc,
               l->tarefa.conclusao.anoc);
        l=l->next;
        i+= 1;
    }
    printf("____________________\nTotal de tarefas: %d\n\n", num);
}

int main(){

    int totalTarefas = 0;
    int comando;
    List listaTarefas, novo;
    listaTarefas = NULL;
    setlocale(LC_ALL, "Portuguese");
    while(1){
        printf("MENU:\n[1] Definir tarefas.\n[2] Ver lista de tarefas.\n...\n[10] Sair do programa.\n\nIntroduza o comando: ");
        scanf("%d", &comando);
        switch(comando){
            default:
                printf("Comando desconhecido, tente novamente!\n");
                break;
            case 1:
                if(totalTarefas < MaxTarefas){
                    if(totalTarefas == 0){
                        novo=(List)malloc(sizeof(No));
                        leTarefa(&novo->tarefa);
                        listaTarefas=addTarefa_inicio(listaTarefas, novo);
                        totalTarefas += 1;
                        break;
                    }
                    else{
                        novo=(List)malloc(sizeof(No));
                        leTarefa(&novo->tarefa);
                        listaTarefas=addTarefa_fim(listaTarefas, novo);
                        totalTarefas += 1;
                        break;
                    }
                }
                else{
                    printf("Lista cheia!\n\n");
                    break;
                }
            case 2:
                printListaTarefas(listaTarefas, totalTarefas);
                break;
            case 10:
                return 0;
        }
    }
}
