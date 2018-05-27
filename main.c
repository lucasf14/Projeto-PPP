#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 1000


List criaLista(){
    List l = (List)malloc(sizeof(struct no));
    l->next= NULL;
    return l;
}

List addListaFinal(List l, List node){
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

List addListaOrdenado(List l, List node, int fase){
    int num;
    TipoData data1, data2;
    List ant;
    List act;
    node->next=NULL;
    ant=l;
    act=l->next;
    if(fase == 1){
        num = comparaMaiorPrioridade(l, node);
        if(num == -1){
            node->next = l;
            return node;
        }
        ant = l;
        act = l->next;
        num = comparaMaiorPrioridade(act, node);
        while(num > -1 && act != NULL){
            ant = ant->next;
            act = act->next;
            num = comparaMaiorPrioridade(act, node);
        }
        ant->next = node;
        node->next = act;
    }
    if(fase == 2){
        if(act->tarefa.pessoa.nomePessoa == '\0'){
            act->tarefa.pessoa.nomePessoa = protString();
        }
        num = comparaNome(act, node);
        if(num == -1){
            node->next = l;
            return node;
        }
        ant = l;
        act = l->next;
        num = comparaNome(act, node);
        while(num > -1 && act != NULL){
            ant = ant->next;
            act = act->next;
            num = comparaNome(act, node);
        }
        ant->next = node;
        node->next = act;
    }
    if(fase == 3){
        data1.ano=act->tarefa.data_conclusao.ano;
        data1.mes=act->tarefa.data_conclusao.mes;
        data1.dia=act->tarefa.data_conclusao.dia;
        data2.ano=node->tarefa.data_conclusao.ano;
        data2.mes=node->tarefa.data_conclusao.mes;
        data2.dia=node->tarefa.data_conclusao.dia;
        num = comparaMaiorData(&data1, &data2);
        if(num == -1){
            node->next = l;
            return node;
        }
        ant = ant->next;
        act = act->next;
        data1.ano=act->tarefa.data_conclusao.ano;
        data1.mes=act->tarefa.data_conclusao.mes;
        data1.dia=act->tarefa.data_conclusao.dia;
        data2.ano=node->tarefa.data_conclusao.ano;
        data2.mes=node->tarefa.data_conclusao.mes;
        data2.dia=node->tarefa.data_conclusao.dia;
        num = comparaMaiorData(&data1, &data2);
        while(num > -1 && act != NULL){
            ant = ant->next;
            act = act->next;
            data1.ano=act->tarefa.data_conclusao.ano;
            data1.mes=act->tarefa.data_conclusao.mes;
            data1.dia=act->tarefa.data_conclusao.dia;
            data2.ano=node->tarefa.data_conclusao.ano;
            data2.mes=node->tarefa.data_conclusao.mes;
            data2.dia=node->tarefa.data_conclusao.dia;
            num = comparaMaiorData(&data1, &data2);
        }
        ant->next = node;
        node->next = act;
    }
    return l;
}

int comparaNome(List fonte, List destino){
    int num;
    if(fonte == NULL){
        return -1;
    }
    if(strcmp(fonte ->tarefa.pessoa.nomePessoa, destino->tarefa.pessoa.nomePessoa) > 0){
        num = 0;
        return num;
    }
    else if(strcmp(fonte ->tarefa.pessoa.nomePessoa, destino->tarefa.pessoa.nomePessoa) < 0){
        num = -1;
        return num;
    }
    else{
        return 0;
    }
}

int comparaMaiorPrioridade(List fonte, List destino){
    int num;
    TipoData data1, data2;
    if(fonte == NULL){
        return -1;
    }
    data1.ano=fonte->tarefa.data_criacao.ano;
    data1.mes=fonte->tarefa.data_criacao.mes;
    data1.dia=fonte->tarefa.data_criacao.dia;
    data2.ano=destino->tarefa.data_criacao.ano;
    data2.mes=destino->tarefa.data_criacao.mes;
    data2.dia=destino->tarefa.data_criacao.dia;
    if(fonte ->tarefa.prioridade > destino->tarefa.prioridade){
        num = 0;
        return num;
    }
    else if(fonte ->tarefa.prioridade < destino->tarefa.prioridade){
        num = -1;
        return num;
    }
    else{
        num = comparaMaiorData(&data1, &data2);
        return num;
    }
}


int comparaMaiorData(TipoData *data1, TipoData *data2){
    if (data1->ano < data2->ano){
       return 0;
    }
    else if (data1->ano > data2->ano){
       return -1;
    }
    else{
        if (data1->mes < data2->mes){
            return 0;
        }
        else if (data1->mes > data2->mes){
            return -1;
        }
        else{
            if (data1->dia < data2->dia){
                return 0;
            }
            else if(data1->dia > data2->dia){
                return -1;
            }
            else{
                return 0;
            }
        }
    }
}

void verificaIdentificador(List l, TipoTarefa *tarefa){
    List aux = l->next;
    while(aux != NULL){
        if(aux->tarefa.identificador != tarefa->identificador){
            aux=aux->next;
        }
        else{
            printf("O identificador inserido já se encontra utilizado. Tente novamente: ");
            tarefa->identificador = protInteiro();
            if(tarefa->identificador == 0){
                free(tarefa);
                return;
            }
            verificaIdentificador(aux, tarefa);
        }
    }
}

List eliminaTarefa(List l){
    int id;
    List act, ant;
    act = l->next;
    ant = l;
    if(act == NULL){
        printf("Lista vazia!\n");
        return l;
    }
    id = verificaID(l);
    if(id == 0){
        return l;
    }
    while(act != NULL && act->tarefa.identificador != id){
        ant = act;
        act = act->next;
    }
    if(act != NULL){
        if(ant != NULL){
            ant->next=act->next;
        }
        else{
            l=act->next;
        }
        free(act);
    }
    return l;
}

List mover_tarefas(List fonte, List destino, int fase){
    int id;
    List ant, act;
    List nodenovo;
    if(fonte->next == NULL){
        printf("Lista vazia!\n");
        return fonte;
    }
    nodenovo = (List)malloc(sizeof(No));
    ant=fonte;
    act = fonte->next;
    id = verificaID(fonte);
    while(act != NULL && act->tarefa.identificador != id){
        ant = act;
        act = act->next;
    }
    nodenovo->tarefa.prioridade = act->tarefa.prioridade;
    nodenovo->tarefa.identificador = act->tarefa.identificador;
    nodenovo->tarefa.data_criacao.ano = act->tarefa.data_criacao.ano;
    nodenovo->tarefa.data_criacao.mes = act->tarefa.data_criacao.mes;
    nodenovo->tarefa.data_criacao.dia = act->tarefa.data_criacao.dia;
    nodenovo->tarefa.pessoa.nomePessoa = act->tarefa.pessoa.nomePessoa;
    nodenovo->tarefa.desc = act->tarefa.desc;
    nodenovo->tarefa.data_prazo.ano = act->tarefa.data_prazo.ano;
    nodenovo->tarefa.data_prazo.mes = act->tarefa.data_prazo.mes;
    nodenovo->tarefa.data_prazo.dia = act->tarefa.data_prazo.dia;
    nodenovo->next = NULL;
    destino = addListaOrdenado(destino, nodenovo, fase);
    ant->next = act->next;
    free(act);
    return destino;
}


void imprime_lista(List l){
    List aux = l->next;
    printf("___________________________________________\n");
    if (aux==NULL){
        printf("Esta lista encontra-se vazia! \n");
        printf("___________________________________________\n");
    }
    else{
        while(aux!=NULL){
            if(aux->tarefa.pessoa.nomePessoa == '\0'){
                printf("\nTarefa no. %d.\n Prioridade: %d\n Data de Criação: %d/%d/%d\n Descrição da tarefa: %s\n Pessoa responsável: Não tem\n Prazo: %d/%d/%d\n",
                    aux->tarefa.identificador,
                    aux->tarefa.prioridade,
                    aux->tarefa.data_criacao.dia,
                    aux->tarefa.data_criacao.mes,
                    aux->tarefa.data_criacao.ano,
                    aux->tarefa.desc,
                    aux->tarefa.data_prazo.dia,
                    aux->tarefa.data_prazo.mes,
                    aux->tarefa.data_prazo.ano);
                aux=aux->next;
            }
            else{
                printf("\nTarefa no. %d.\n Prioridade: %d\n Data de Criação: %d/%d/%d\n Descrição da tarefa: %s\n Pessoa responsável: %s\n Prazo: %d/%d/%d\n",
                    aux->tarefa.identificador,
                    aux->tarefa.prioridade,
                    aux->tarefa.data_criacao.dia,
                    aux->tarefa.data_criacao.mes,
                    aux->tarefa.data_criacao.ano,
                    aux->tarefa.desc,
                    aux->tarefa.pessoa.nomePessoa,
                    aux->tarefa.data_prazo.dia,
                    aux->tarefa.data_prazo.mes,
                    aux->tarefa.data_prazo.ano);
                if(aux->tarefa.fase==3){
                     printf(" Data Conclusão: %d/%d/%d\n",
                        aux->tarefa.data_conclusao.dia,
                        aux->tarefa.data_conclusao.mes,
                        aux->tarefa.data_conclusao.ano);
                }
                else if (aux->tarefa.fase==2){
                    printf(" Data Conclusão: A tarefa ainda não se encontra concluída.\n");

                }
            aux=aux->next;
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

void leTarefa(List listaToDo,List listaDoing,List listaDone, TipoTarefa *tarefa){
    TipoData data;
    char *flag = "n";
    printf("Identificador: ");
    tarefa->identificador = protInteiro();
    verificaIdentificador(listaToDo, tarefa);
    verificaIdentificador(listaDoing, tarefa);
    verificaIdentificador(listaDone, tarefa);
    if(tarefa->identificador == 0){
        free(tarefa);
        return;
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
        return;
    }
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        printf("Prioridade inválida, tente novamente (1 a 10): ");
        tarefa->prioridade = protInteiro();
        if(tarefa->prioridade == 0){
            free(tarefa);
            return;
        }
    }
    printf("Descrição da tarefa: ");
    tarefa->desc = protString();
    if(strcmp(tarefa->desc, "quit") == 0){
        free(tarefa);
        return;
    }
    tarefa->fase = 1;
    printf("Deseja associar já a tarefa a uma pessoa? [s/n]: ");
    flag = protString();
    if(strcmp(flag, "quit") == 0){
        free(tarefa);
        return;
    }
    while(flag[0] != 's' && flag[0] != 'n'){
        printf("Resposta inválida, tente novamente [s/n]: ");
        flag = protString();
        if(strcmp(flag, "quit") == 0){
            free(tarefa);
            return;
        }
    }
    if(flag[0] == 's'){
        printf("Pessoa a atribuir: ");
        tarefa->pessoa.nomePessoa = protString();
        if(strcmp(tarefa->pessoa.nomePessoa, "quit") == 0){
            free(tarefa);
            return;
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
        id = verificaID(l);
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

int verificaID(List l){
    int id;
    List aux = l->next;
    printf("Introduza o ID da tarefa: ");
    id = protInteiro();
    while(aux->next != NULL && id != aux->tarefa.identificador){
        aux=aux->next;
    }
    if(id == aux->tarefa.identificador){
        printf("wtf happening here\n");
        return id;
    }
    else{
        printf("Não encontrei nada nesta lista. Tente novamente! \n");
        verificaID(l);
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




