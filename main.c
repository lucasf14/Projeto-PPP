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
    List cur;
    cur=(List)malloc(sizeof(No));
    node->next=NULL;
    cur=l;
    if(cur==NULL){
        cur=node;
    }
    while(cur->next!=NULL){
        cur=cur->next;
    }
    cur->next=node;
    return l;
}

List addListaOrdenado(List l, List node){
    int num;
    List cur;
    List seg;
    node->next=NULL;
    cur=NULL;
    seg = l;
    num = comparaMaiorPrioridade(l, node);
    if(num == -1){
        node->next = l;
        return node;
    }
    cur = l;
    seg = l->next;
    num = comparaMaiorPrioridade(seg, node);
    while(num > -1 && seg != NULL){
        cur = cur->next;
        seg = seg->next;
        num = comparaMaiorPrioridade(seg, node);
    }
    cur->next = node;
    node->next = seg;
    return l;
}

int comparaMaiorPrioridade(List fonte, List destino){
    int num;
    if(fonte == NULL){
        return -1;
    }
    if(fonte ->tarefa.prioridade > destino->tarefa.prioridade){
        num = 0;
        return num;
    }
    else if(fonte ->tarefa.prioridade < destino->tarefa.prioridade){
        num = -1;
        return num;
    }
    else{
        num = comparaMaiorData(fonte, destino);
        return num;
    }
}

int comparaMaiorData(List data1, List data2){
    if (data1->tarefa.data_criacao.ano < data2->tarefa.data_criacao.ano){
       return 0;
    }
    else if (data1->tarefa.data_criacao.ano > data2->tarefa.data_criacao.ano){
       return -1;
    }
    else{
        if (data1->tarefa.data_criacao.mes < data2->tarefa.data_criacao.mes){
            return 0;
        }
        else if (data1->tarefa.data_criacao.mes > data2->tarefa.data_criacao.mes){
            return -1;
        }
        else{
            if (data1->tarefa.data_criacao.dia < data2->tarefa.data_criacao.dia){
                return 0;
            }
            else if(data1->tarefa.data_criacao.dia > data2->tarefa.data_criacao.dia){
                return -1;
            }
            else{
                return 0;
            }
        }
    }
}

void verificaIdentificador(List l, TipoTarefa *tarefa){
    while(l != NULL){
        if(l->tarefa.identificador != tarefa->identificador){
            l=l->next;
        }
        else{
            printf("O identificador inserido já se encontra utilizado. Tente novamente: ");
            tarefa->identificador = protInteiro();
            if(tarefa->identificador == 0){
                free(tarefa);
                menu();
            }
            verificaIdentificador(l, tarefa);
        }
    }
}


List eliminaTarefa(List l){
    int id;
    List cur, prev;
    cur = l;
    prev = NULL;
    if(cur == NULL){
        printf("Lista vazia!\n");
        return;
    }
    printf("Introduza o ID da tarefa a eliminar: ");
    id = protInteiro();
    if(id == 0){
        return;
    }
    while(cur != NULL){
        if(cur->tarefa.identificador != id){
            prev = cur;
            cur = cur->next;
        }
        else{
            if(cur == l){
                free(cur);
                l = NULL;
                return l;
            }
            else{
                prev->next = cur->next;
                free(cur);
            }
        }
    }
    if (cur->tarefa.identificador != id){
        printf("Tarefa não encontrada! Tente novamente: ");
        eliminaTarefa(l);
    }
    return l;
}


void mover_tarefas(List fonte, List destino){
    int id;
    List prev1, cur1;
    List prev2, cur2;
    prev1=NULL;
    cur1 = fonte;
    prev2=NULL;
    cur2 = destino;
    printf("Introduza o ID da tarefa a mover: ");
    id = protInteiro();
    procura_lista(fonte, id, prev1, cur1);
    /*
    identificador=verificaID(listaToDo, tarefa);
    procura_lista(listaToDo, identificador, ant, seg, atual);
    printf("Pessoa a atribuir: ");
    listaToDo->tarefa.pessoa.nomePessoa = protString();
    verificaPessoaFicheiro(tarefa);
    */
}

void procura_lista(List l, int identificador, List prev, List cur){
    prev=NULL;
    cur = l;
    while(cur != NULL && cur->tarefa.identificador != identificador){
        prev = cur;
        cur = cur->next;
    }
    printf("CENAS = %d", cur->tarefa.identificador);
    if(cur != NULL && cur->tarefa.identificador != identificador){
        cur = NULL;
        printf("Tarefa não existente! CRL que faço agora?");
        return;
    }
}


void imprime_lista(List l){
    printf("___________________________________________\n");
    if (l==NULL){
        printf("Esta lista encontra-se vazia! \n");
        printf("___________________________________________\n");
    }
    else{
        while(l!=NULL){
            if(l->tarefa.pessoa.nomePessoa == '\0'){
                printf("\nTarefa no. %d.\n Prioridade: %d\n Data de Criação: %d/%d/%d\n Descrição da tarefa: %s\n Pessoa responsável: Não tem\n Prazo: %d/%d/%d\n",
                    l->tarefa.identificador,
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
                printf("\nTarefa no. %d.\n Prioridade: %d\n Data de Criação: %d/%d/%d\n Descrição da tarefa: %s\n Pessoa responsável: %s\n Prazo: %d/%d/%d\n",
                    l->tarefa.identificador,
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
                     printf(" Data Conclusão: %d/%d/%d\n",
                        l->tarefa.data_conclusao.dia,
                        l->tarefa.data_conclusao.mes,
                        l->tarefa.data_conclusao.ano);
                }
                else if (l->tarefa.fase==2){
                    printf(" Data Conclusão: A tarefa ainda não se encontra concluída.\n");

                }
            l=l->next;
            }
    printf("___________________________________________\n");
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
        tarefa->pessoa.nomePessoa = protString();
        verificaPessoaFicheiro(tarefa);
    }
    fclose(file);
}

void leTarefa(List l, TipoTarefa *tarefa){
    TipoData data;
    char *flag = "n";
    printf("Identificador: ");
    tarefa->identificador = protInteiro();
    verificaIdentificador(l, tarefa);
    if(tarefa->identificador == 0){
        free(tarefa);
        menu();
    }
    printf("Insira data de criação: \n");
    verificaData(&data, tarefa);
    tarefa->data_criacao.ano=data.ano;
    tarefa->data_criacao.mes=data.mes;
    tarefa->data_criacao.dia=data.dia;
    printf("Prioridade (1 a 10): ");
    tarefa->prioridade = protInteiro();
    if(tarefa->prioridade == 0){
        free(tarefa);
        menu();
    }
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        printf("Prioridade inválida, tente novamente (1 a 10): ");
        tarefa->prioridade = protInteiro();
        if(tarefa->prioridade == 0){
            free(tarefa);
            menu();
        }
    }
    printf("Descrição da tarefa: ");
    tarefa->desc = protString();
    if(strcmp(tarefa->desc, "quit") == 0){
        free(tarefa);
        menu();
    }
    tarefa->fase = 1;
    printf("Deseja associar já a tarefa a uma pessoa? [s/n]: ");
    flag = protString();
    if(strcmp(flag, "quit") == 0){
        free(tarefa);
        menu();
    }
    while(flag[0] != 's' && flag[0] != 'n'){
        printf("Resposta inválida, tente novamente [s/n]: ");
        flag = protString();
        if(strcmp(flag, "quit") == 0){
            free(tarefa);
            menu();
        }
    }
    if(flag[0] == 's'){
        printf("Pessoa a atribuir: ");
        tarefa->pessoa.nomePessoa = protString();
        if(strcmp(tarefa->pessoa.nomePessoa, "quit") == 0){
            free(tarefa);
            menu();
        }
        verificaPessoaFicheiro(tarefa);
    }
    printf("Insira data de prazo: \n");
    verificaData(&data, tarefa);
    compara_datas(tarefa, &data);
    tarefa->data_prazo.ano=data.ano;
    tarefa->data_prazo.mes=data.mes;
    tarefa->data_prazo.dia=data.dia;
    printf("\n");
}

void associaTarefa(List l, TipoTarefa *tarefa, char *flag, int id){
    if(flag[0] == 'n'){
        id = verificaID(l, tarefa);
    }
    while(l != NULL){
        if(id != l->tarefa.identificador){
            l=l->next;
        }
        else{
            printf("Pessoa a atribuir: ");
            l->tarefa.pessoa.nomePessoa = protString();
            verificaPessoaFicheiro(tarefa);
            break;
        }
    }
}

int verificaID(List l, TipoTarefa *tarefa){
    int id;
    printf("Introduza o ID da tarefa: ");
    id = protInteiro();
    while(l != NULL){
        if(id != l->tarefa.identificador){
            l=l->next;
        }
        else{
            return id;
        }
    }
    if(id != l->tarefa.identificador){
        printf("Não encontrei nada nesta lista. Tente novamente! \n");
        verificaID(l, tarefa);
    }
    return 0;
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
            printf("\nTarefa no. %d.\nPrioridade: %d\nDescrição da tarefa: %s\nPrazo: %d/%d/%d\n",
                   l->tarefa.identificador,
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




