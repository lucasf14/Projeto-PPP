#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 1000


int menu(){
    int comando, max_tarefas;
    int input;
    char *nome;
    char *flag = "n";
    List listaToDo, listaDoing, listaDone, novo;
    listaToDo = criaLista();
    listaDoing = criaLista();
    listaDone = criaLista();
    setlocale(LC_ALL, "Portuguese");
    printf("Defina o número máximo de tarefas por pessoa: ");
    max_tarefas = protInteiro();
    while(1){
        printf("MENU:\n");
        printf(" [1] Criar tarefa.\n");
        printf(" [2] Ver lista de tarefas.\n");
        printf(" [3] Ver lista de pessoas.\n");
        printf(" [4] Associar tarefa a pessoa.\n");
        printf(" [5] Eliminar uma tarefa.\n");
        printf(" [6] Mover tarefas de fase.\n");
        printf(" [7] Visualizar as tarefas associadas à pessoa.\n");
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
                leTarefa(listaToDo, listaDoing, listaDone, &novo->tarefa, max_tarefas);
                listaToDo=addListaOrdenado(listaToDo, novo, 1);
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
                system("cls");
                printf("OPÇÕES:\n");
                printf(" [1] Associar ou reassociar uma pessoa a uma tarefa a \"To Do\".\n");
                printf(" [2] Ressociar uma pessoa a uma tarefa a \"Doing\".\n");
                printf("\nSelecione um opção: ");
                input = protInteiro();
                if(input == 0)
                    free(&novo->tarefa);
                while(input < 1 || input > 2){
                    printf("Comando desconhecido, tente novamente: ");
                    input = protInteiro();
                }
                if(input == 1){
                    if(listaToDo->next == NULL){
                        printf("Lista vazia!\n");
                        break;
                    }
                    associaTarefa(listaToDo, listaDoing, listaDone, &novo->tarefa, flag, novo->tarefa.identificador, max_tarefas);
                }
                else{
                    if(listaDoing->next == NULL){
                        printf("Lista vazia!\n");
                        break;
                    }
                    associaTarefa(listaDoing, listaToDo, listaDone, &novo->tarefa, flag, novo->tarefa.identificador, max_tarefas);
                }
                break;
            case 5:
                system("cls");
                printf("OPÇÕES:\n");
                printf(" [1] Eliminar tarefa de \"To Do\".\n");
                printf(" [2] Eliminar tarefa de \"Doing\".\n");
                printf(" [3] Eliminar tarefa de \"Done\".\n");
                printf("\nSelecione um opção: ");
                input = protInteiro();
                while(input < 1 || input > 3){
                    printf("Comando desconhecido, tente novamente: ");
                    input = protInteiro();
                }
                if(input == 1)
                    listaToDo = eliminaTarefa(listaToDo);
                else if(input == 2)
                    listaDoing = eliminaTarefa(listaDoing);
                else
                    listaDone = eliminaTarefa(listaDone);
                break;
            case 6:
                system("cls");
                printf("OPÇÕES:\n");
                printf(" [1] Mover de \"To Do\" para \"Doing\".\n");
                printf(" [2] Mover de \"Doing\" para \"To Do\".\n");
                printf(" [3] Mover de \"Doing\" para \"Done\".\n");
                printf(" [4] Mover de \"Done\" para \"Doing\".\n");
                printf(" [5] Mover de \"Done\" para \"Todo\".\n");
                printf("\nSelecione um opção: ");
                input = protInteiro();
                if(input == 0)
                    free(&novo->tarefa);
                while(input < 1 || input > 5){
                    printf("Comando desconhecido, tente novamente: ");
                    input = protInteiro();
                }
                if(input == 1)
                    mover_tarefas(listaToDo, listaDoing, 2);
                else if(input == 2)
                    mover_tarefas(listaDoing, listaToDo, 1);
                else if(input == 3)
                    mover_tarefas(listaDoing, listaDone, 3);
                else if(input == 4)
                    mover_tarefas(listaDone, listaDoing, 2);
                else
                    mover_tarefas(listaDone, listaToDo, 1);
                break;
            case 7:
                printf("Insira pessoa: ");
                nome=protString();
                verificaPessoaFicheiro(nome);
                imprime_lista_pessoa(listaToDo, listaDoing, listaDone, nome);
                break;
            case 9:
                 system("cls");
                 break;
            case 10:
                return 0;

        }
    }
}
