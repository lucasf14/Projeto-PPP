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

void imprime_lista(List l){
    printf("__________________\n");
    if (l==NULL){
        printf("A lista de tarefas encontra-se vazia! \n");
    }
    else{
        while(l!=NULL){
            if(strcmp(l->tarefa.pessoa.nomePessoa, "") == 0){
                printf("\nTarefa no. %d: %s\nPrioridade: %d\nData de Criação: %d/%d/%d\nDescrição da tarefa: %s\nPessoa responsável: Não tem\nPrazo: %d/%d/%d\n",
                    l->tarefa.identificador,
                    l->tarefa.novaTarefa,
                    l->tarefa.prioridade,
                    l->tarefa.data_criacao.dia,
                    l->tarefa.data_criacao.mes,
                    l->tarefa.data_criacao.ano,
                    l->tarefa.desc,
                    l->tarefa.data_prazo.dia,
                    l->tarefa.data_prazo.mes,
                    l->tarefa.data_prazo.ano);
                l=l->next;
            }
            else{
                printf("\nTarefa no. %d: %s\nPrioridade: %d\nData de Criação: %d/%d/%d\nDescrição da tarefa: %s\nPessoa responsável: %s\nPrazo: %d/%d/%d\n",
                    l->tarefa.identificador,
                    l->tarefa.novaTarefa,
                    l->tarefa.prioridade,
                    l->tarefa.data_criacao.dia,
                    l->tarefa.data_criacao.mes,
                    l->tarefa.data_criacao.ano,
                    l->tarefa.desc,
                    l->tarefa.pessoa.nomePessoa,
                    l->tarefa.data_prazo.dia,
                    l->tarefa.data_prazo.mes,
                    l->tarefa.data_prazo.ano);
                if(l->tarefa.fase==3){
                     printf("Data Conclusão: %d/%d/%d",
                        l->tarefa.data_conclusao.dia,
                        l->tarefa.data_conclusao.mes,
                        l->tarefa.data_conclusao.ano);
                }
                else if (l->tarefa.fase==2){
                    printf("Data Conclusão: A tarefa ainda não se encontra concluída.\n");

                }
            l=l->next;
            }
        printf("__________________\n");
        }
    }
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

void leTarefa(List l, TipoTarefa *tarefa){
    TipoData data;
    char flag = 'n';
    printf("\nNome da tarefa: ");
    scanf(" %[^\n]s", tarefa->novaTarefa);
    printf("Identificador: ");
    tarefa->identificador = protInteiro();
    printf("Insira data de criacao: \n");
    verificaData(&data);
    tarefa->data_criacao.ano=data.ano;
    tarefa->data_criacao.mes=data.mes;
    tarefa->data_criacao.dia=data.dia;
    printf("Prioridade (1 a 10): ");
    tarefa->prioridade = protInteiro();
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        printf("Prioridade inválida, tente novamente (1 a 10): ");
        tarefa->prioridade = protInteiro();
    }
    printf("Descrição da tarefa: ");
    scanf(" %[^\n]s", tarefa->desc);
    printf("A que fase deseja adicionar a tarefa?\n");
    printf("[1] To do.\n");
    printf("[2] Doing.\n");
    printf("[3] Done.\n");
    printf("Fase: ");
    tarefa->fase = protInteiro();
    while(tarefa->fase<1 || tarefa->fase>3){
        tarefa->fase = protInteiro();
    }
    if (tarefa->fase==1){
        printf("Deseja associar já a tarefa a uma pessoa? [s/n]: ");
        scanf(" %s", &flag);
        while(flag != 's' && flag != 'n'){
            do{
                printf("Resposta inválida, tente novamente [s/n]: ");
                fflush(stdin);
            }
            while(!scanf(" %s", &flag));
        }
        if(flag == 's'){
            printf("Pessoa a atribuir: ");
            scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
        }
    }
    else{
        printf("Pessoa a atribuir: ");
        scanf(" %[^\n]s", tarefa->pessoa.nomePessoa);
    }
    printf("Insira data de prazo: \n");
    verificaData(&data);
    compara_datas(tarefa, &data);
    tarefa->data_prazo.ano=data.ano;
    tarefa->data_prazo.mes=data.mes;
    tarefa->data_prazo.dia=data.dia;
    printf("\n");
}

void associaTarefa(List l, TipoTarefa *tarefa, char flag, int id){
    if(flag == 'n'){
        id = verificaID(l, tarefa);
    }
    while(l != NULL){
        if(id != l->tarefa.identificador){
            l=l->next;
        }
        else{
            printf("Pessoa a atribuir: ");
            scanf(" %[^\n]s", l->tarefa.pessoa.nomePessoa);
            break;
        }
    };
}

int verificaID(List l, TipoTarefa *tarefa){
    List copia = l;
    int id;
    printf("Introduza o ID da tarefa: ");
    id = protInteiro();
    while(copia != NULL){
        if(id != copia->tarefa.identificador){
            copia=copia->next;
        }
        else{
            return id;
        }
    }
    if(id != copia->tarefa.identificador){
        printf("Não encontrei nada nesta lista. Tente novamente! \n");
        verificaID(l, tarefa);
    }
    return 0;
}

void printListaTarefas(List l, int num){
    int i = 1;
    printf("____________________\n");
    while(l!=NULL){

        if(strcmp(l->tarefa.pessoa.nomePessoa, "") == 0){
            printf("\nTarefa no. %d: %s\nPrioridade: %d\nDescrição da tarefa: %s\nPessoa responsável: Não tem\nPrazo: %d/%d/%d\n",
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

    }
    printf("____________________\nTotal de tarefas: %d\n\n", num);
}

void printTarefasPessoa(List l, TipoTarefa *tarefa){ /*errada */
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

