#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 1000


List criaListaTarefas(List l, List node){
    node->next=l;
    l=node;
    return l;
}

List addTarefa(List l, List node){
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
    while(!scanf(" %d", &tarefa->identificador )){
            printf("Identificador inválido, tente novamente: ");
            fflush(stdin);
    }
    printf("Prioridade (1 a 10): ");
    scanf(" %d", &tarefa->prioridade);
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        do{
            printf("Prioridade inválida, tente novamente (1 a 10): ");
            fflush(stdin);
        }
        while (!scanf(" %d", &tarefa->prioridade));
    }
    printf("Descrição da tarefa: ");
    scanf(" %[^\n]s", tarefa->desc);
    printf("Pessoa a atribuir: ");
    scanf(" %[^\n]s", tarefa->pessoa.nomePessoa); /*Verificar se esta pessoa está no ficheiro */
    printf("Prazo: ");
    while (!scanf("%d/%d/%d", &tarefa->data_conclusao.dia, &tarefa->data_conclusao.mes, &tarefa->data_conclusao.ano)){
        printf("Prazo inválido, tente novamente (dd/mm/aaaa): ");
        fflush(stdin);
    }
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
               l->tarefa.data_conclusao.dia,
               l->tarefa.data_conclusao.mes,
               l->tarefa.data_conclusao.ano);
        l=l->next;
        i+= 1;
    }
    printf("____________________\nTotal de tarefas: %d\n\n", num);
}

void listaPessoas(){
    FILE *file = fopen("listapessoas.txt", "r");
    char *nome;
    char *email;
    char *id;
    char linha[MAX];
    if(file == NULL){
        printf("Não foi possível abrir o ficheiro.\n");
        menu();
    }
    printf("___________________________________________\n");
    while(!feof(file)){
        fgets(linha, MAX, file);
        nome = strtok(linha, "-");
        email = strtok(NULL, "-");
        id = strtok(NULL, "-");
        printf("NOME: %s\nE-MAIL: %s\nID: %s\n", nome, email, id);
    }
    printf("___________________________________________");
    fclose(file);
    printf("\n");
}

int main(){
    menu();
    return 0;
}
