#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 1000


List criaLista(List l, List node){
    node->next=l;
    l=node;
    return l;
}

List addLista(List l, List node){
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


void verificaPessoaFicheiro(TipoTarefa *tarefa){
    FILE *file = fopen("listapessoas.txt", "r");
    char *nome;
    int ret;
    char linha[MAX];
    if(file == NULL){
        printf("Não foi possível abrir o ficheiro.\n");
        menu();
    }
    while (!feof(file)){
        fgets(linha, MAX, file);
        nome = strtok(linha, "-");
        ret = strcmp(nome, tarefa->pessoa.nomePessoa);
        if(ret == 0){
            break;
        }
    }
    if(ret != 0){
        printf("A pessoa introduzida não existe. Tente novamente: ");
        scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
        verificaPessoaFicheiro(tarefa);
    }
    fclose(file);
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
    printf("\n");
}

void associaTarefa(List l, TipoTarefa *tarefa){
    verificaID(l, tarefa);
    printf("Pessoa a atribuir: ");
    scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
    verificaPessoaFicheiro(tarefa);
    verificaData(tarefa);
}

void verificaID(List l, TipoTarefa *tarefa){
    int id;
    printf("Introduza o ID da tarefa: ");
    scanf(" %d", &id);
    while(l->next !=NULL){
        printf("ID1 = %d\nID2 = %d\n\n", id, l->tarefa.identificador);
        if(id != l->tarefa.identificador){
            l=l->next;
        }
        else{
            break;
        }
    }
    if(id != l->tarefa.identificador){
        printf("Não encontrei nada nesta lista. Tente novamente! \n");
        verificaID(l, tarefa);
    }
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
               l->tarefa.data_prazo.dia,
               l->tarefa.data_prazo.mes,
               l->tarefa.data_prazo.ano);
        l=l->next;
        i+= 1;
    }
    printf("____________________\nTotal de tarefas: %d\n\n", num);
}

void printTarefasPessoa(List l, TipoTarefa *tarefa){
    int i = 0, ret;
    printf("Introduza o nome da pessoa a verificar: ");
    scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
    verificaPessoaFicheiro(tarefa);
    printf("Pessoa responsável: %s", tarefa->pessoa.nomePessoa);
    printf("\n____________________\n");
    while(l!=NULL){
        ret = strcmp(l->tarefa.pessoa.nomePessoa, tarefa->pessoa.nomePessoa);
        printf("\n\tPESSOA1: %s\n\n\tPESSOA2: %s", l->tarefa.pessoa.nomePessoa, tarefa->pessoa.nomePessoa);
        if(ret == 0){
            printf("\nTarefa no. %d: %s\nPrioridade: %d\nDescrição da tarefa: %s\nPrazo: %d/%d/%d\n",
                   l->tarefa.identificador,
                   l->tarefa.novaTarefa,
                   l->tarefa.prioridade,
                   l->tarefa.desc,
                   l->tarefa.data_prazo.dia,
                   l->tarefa.data_prazo.mes,
                   l->tarefa.data_prazo.ano);
            l=l->next;
            i+= 1;
        }
        else{
            l=l->next;
        }
    }
    printf("____________________\nTotal de tarefas: %d\n\n", i);
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
