#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 100

int protMenu() {
    char str[MAX];
    while (scanf(" %[^\n]", str) ) {
        int i = 0;
        int len = strlen(str);
        while (i < len) {
            if (str[i] < '0' || str[i] > '9' || i > 0) {
                printf("Comando desconhecido, tente novamente: ");
                protMenu();
            }
            i++;
        }
    break;
    }
    return atoi(str);
}


int menu(){
    int totalTarefas = 0;
    int comando;
    char flag = 'n';
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
        printf(" [0] Sair do programa.\n");
        printf("\nIntroduza o comando: ");
        comando = protMenu();
        switch(comando){
            default:
                printf("Comando inválido, tente novamente: ");
                break;
            case 1:
                if(totalTarefas < MaxTarefas){
                    if(totalTarefas == 0){
                        novo=(List)malloc(sizeof(No));
                        leTarefa(listaTarefas, &novo->tarefa);
                        listaTarefas=criaLista(listaTarefas, novo);
                        /*verificaListas(listaToDo, listaDoing, listaDone, novo);*/
                        totalTarefas += 1;
                        break;
                    }
                    else{
                        novo=(List)malloc(sizeof(No));
                        leTarefa(listaTarefas, &novo->tarefa);
                        listaTarefas=addLista(listaTarefas, novo);
                        /*verificaListas(listaToDo, listaDoing, listaDone, novo);*/
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
            case 3:
                listaPessoas();
                break;
            case 4:
                associaTarefa(listaTarefas, &novo->tarefa, flag);
                break;
            case 5:
                printTarefasPessoa(listaTarefas, &novo->tarefa);
                break;
            case 0:
                return 0;
        }
    }
}
