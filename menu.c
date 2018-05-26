#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 1000


int menu(){
    int totalTarefas = 0;
    int comando;
    int input;
    char *flag = "n";
    List listaTarefas, novo, listaToDo, listaDoing, listaDone;
    listaTarefas = NULL;
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
        printf(" [6] Mover tarefas de fase.\n");
        printf(" [9] Limpar o ecrã.\n");
        printf(" [10] Sair do programa.\n");
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
                novo=(List)malloc(sizeof(No));
                leTarefa(listaToDo, &novo->tarefa);
                if (novo->tarefa.fase==1){
                    if(listaToDo==NULL){
                        listaToDo=criaLista(listaToDo, novo);
                    }
                    else{
                        listaToDo=addListaOrdenado(listaToDo, novo);
                    }
                }
                totalTarefas += 1;
                break;
            case 2:
                printf("\nLista de tarefas \"To Do\":\n");
                imprime_lista(listaToDo);
                printf("\nLista de tarefas \"Doing\":\n");
                imprime_lista(listaDoing);
                printf("\nLista de tarefas \"Done\":\n");
                imprime_lista(listaDone);
                break;
            case 3:
                listaPessoas();
                break;
            case 4:
                associaTarefa(listaToDo, &novo->tarefa, flag, novo->tarefa.identificador); /* Fazer para todas as listas */
                break;
            case 5:
                printTarefasPessoa(listaTarefas, &novo->tarefa);                                    /*esta está incorreta */
                break;
            case 6:
                system("cls");
                printf("OPÇÕES:\n");
                printf(" [1] Mover de \"To Do\" para \"Doing\".\n");
                printf(" [2] Mover de \"Doing\" para \"To Do\".\n");
                printf(" [3] Mover de \"Doing\" para \"Done\".\n");
                printf(" [4] Mover de \"Done\" para \"Doing\".\n");
                printf("\nSelecione um opção: ");
                input = protInteiro();
                if(input == 0){
                    free(&novo->tarefa);
                }
                while(input < 1 || input > 4){
                    printf("Comando desconhecido, tente novamente: ");
                    input = protInteiro();
                    if(input == 0){
                        free(&novo->tarefa);
                    }
                    if(input == 1)
                        mover_tarefas(listaToDo, listaDoing);
                    else if(input == 2)
                        mover_tarefas(listaDoing, listaToDo);
                    else if(input == 3)
                        mover_tarefas(listaDoing, listaDone);
                    else
                        mover_tarefas(listaDone, listaDoing);
                }

                break;
            case 7:
                eliminaTarefa(listaToDo);
                break;
            case 9:
                 system("cls");
                 break;
            case 10:
                return 0;

        }
    }
}
