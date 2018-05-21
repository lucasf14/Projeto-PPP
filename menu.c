#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 100


int menu(){
    int totalTarefas = 0;
    int comando;
    char flag = 'n';
    List listaTarefas, novo, listaToDo, listaDoing, listaDone;
    listaTarefas = NULL; /* se não for necessária no fim, apagar */
    listaToDo = NULL;
    listaDoing = NULL;
    listaDone = NULL;
    setlocale(LC_ALL, "Portuguese");
    while(1){
        printf("MENU:\n");
        printf(" [1] Criar tarefa.\n");
        printf(" [2] Ver lista de tarefas.\n");
        printf(" [3] Ver lista de pessoas.\n");
        printf(" [4] Associar tarefa a pessoa.\n");
        printf(" [5] Ver tarefas de uma pessoa.\n");
        printf(" [6] Ver tarefas em To Do e em Doing.\n");
        printf(" [0] Sair do programa.\n");
        printf("\nIntroduza o comando: ");
        comando = protMenu();
        while(comando < 1 || comando > 10){
            printf("Comando desconhecido, tente novamente: ");
            comando = protMenu();
        }
        switch(comando){
            default:
                printf("Comando desconhecido, tente novamente: ");
                comando = protMenu();
                break;
            case 1:
                if(totalTarefas < MaxTarefas){
                    novo=(List)malloc(sizeof(No));
                    leTarefa(listaTarefas, &novo->tarefa);
                    if (novo->tarefa.fase==1){
                        if (listaToDo==NULL){
                            listaToDo=criaLista(listaToDo, novo);
                        }
                        else{
                            listaToDo=addLista(listaToDo, novo);
                        }
                    }
                    else if (novo->tarefa.fase==2){
                        if (listaDoing==NULL){
                            listaDoing=criaLista(listaDoing, novo);
                        }
                        else{
                            listaDoing=addLista(listaDoing, novo);
                        }
                    }
                    else{
                        if (listaDone==NULL){
                            listaDone=criaLista(listaDone, novo);
                        }
                        else{
                            listaDone=addLista(listaDone, novo);
                        }
                    }
                    totalTarefas += 1;
                    break;
                }
                else{
                    printf("Lista cheia!\n\n");
                    break;
                }
            case 2:
                printf("Lista de tarefas \"To Do\":\n");
                imprime_lista(listaToDo);
                printf("Lista de tarefas \"Doing\":\n");
                imprime_lista(listaDoing);
                /* alterar a função p imprimir os dados da Done */
                break;
            case 3:
                listaPessoas();
                break;
            case 4:
                associaTarefa(listaToDo, &novo->tarefa, flag, novo->tarefa.identificador); /* Fazer para todas as listas */
                break;
            case 5:
                printTarefasPessoa(listaTarefas, &novo->tarefa); /*esta está incorreta */
                break;
            case 6:
                break;
            case 10:
                return 0;
        }
    }
}
