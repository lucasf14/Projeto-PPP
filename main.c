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

List addListaOrdenado(List l, List node, int fase){
    int num;
    TipoData data1, data2;
    List ant;
    List act;
    node->next=NULL;
    ant=l;
    act=l->next;
    if(fase == 1){
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
        if(act == NULL){
            if(node->tarefa.pessoa.nomePessoa == '\0'){
                printf("Pessoa a atribuir: ");
                node->tarefa.pessoa.nomePessoa = protString();
                verificaPessoaFicheiro(node->tarefa.pessoa.nomePessoa);
                ant->next = node;
                node->next = act;
            }
            else{
                ant->next = node;
                node->next = act;
            }
        }
        ant = l;
        act = l->next;
        num = comparaNome(act, node);
        while(num > -1 && act!= NULL){
            ant = ant->next;
            act = act->next;
            num = comparaNome(act, node);
        }
        ant->next = node;
        node->next = act;
    }
    if(fase == 3){
        if(act == NULL){
            printf("Insira a data de conclusão: \n");
            verificaData(&data2);
            ant->next = node;
            node->next = act;
            ant = l;
            act = l->next;
            act->tarefa.data_conclusao.ano=data2.ano;
            act->tarefa.data_conclusao.mes=data2.mes;
            act->tarefa.data_conclusao.dia= data2.dia;
            num = comparaMaiorData(&data1, &data2);
        }
        else{
            printf("Insira a data de conclusão: \n");
            verificaData(&data2);
            data1.ano=act->tarefa.data_conclusao.ano;
            data1.mes=act->tarefa.data_conclusao.mes;
            data1.dia=act->tarefa.data_conclusao.ano;
            act->tarefa.data_conclusao.ano=data2.ano;
            act->tarefa.data_conclusao.mes=data2.mes;
            act->tarefa.data_conclusao.dia= data2.dia;
            num = comparaMaiorData(&data1, &data2);
        }
        ant = l;
        act = l->next;
        while(num > -1 && act != NULL){
            ant = ant->next;
            act = act->next;
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
    if(strcmp(fonte ->tarefa.pessoa.nomePessoa, destino->tarefa.pessoa.nomePessoa) < 0){
        num = 0;
        return num;
    }
    else if(strcmp(fonte ->tarefa.pessoa.nomePessoa, destino->tarefa.pessoa.nomePessoa) > 0){
        num = -1;
        return num;
    }
    else{
        return 0;
    }
    return 0;
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
    while(id == 0){
        id = verificaID(l);
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

void mover_tarefas(List fonte, List destino, int fase){
    int id;
    List ant, act, aux;
    List nodenovo;
    ant=fonte;
    if (ant==NULL){
        nodenovo = (List)malloc(sizeof(No));
        id = verificaID(fonte);
        while(id == 0){
            id = verificaID(fonte);
        }

        if (ant->tarefa.identificador == id){
            nodenovo->tarefa.prioridade = ant->tarefa.prioridade;
            nodenovo->tarefa.identificador = ant->tarefa.identificador;
            nodenovo->tarefa.data_criacao.ano = ant->tarefa.data_criacao.ano;
            nodenovo->tarefa.data_criacao.mes = ant->tarefa.data_criacao.mes;
            nodenovo->tarefa.data_criacao.dia = ant->tarefa.data_criacao.dia;
            nodenovo->tarefa.pessoa.nomePessoa = ant->tarefa.pessoa.nomePessoa;
            nodenovo->tarefa.desc = ant->tarefa.desc;
            nodenovo->tarefa.data_prazo.ano = ant->tarefa.data_prazo.ano;
            nodenovo->tarefa.data_prazo.mes = ant->tarefa.data_prazo.mes;
            nodenovo->tarefa.data_prazo.dia = ant->tarefa.data_prazo.dia;
            nodenovo->tarefa.data_conclusao.ano = ant->tarefa.data_conclusao.ano;
            nodenovo->tarefa.data_conclusao.mes = ant->tarefa.data_conclusao.mes;
            nodenovo->tarefa.data_conclusao.dia = ant->tarefa.data_conclusao.dia;
            nodenovo->tarefa.fase = fase;
            nodenovo->next = NULL;
            destino = addListaOrdenado(destino, nodenovo, fase);
            free(ant);
            fonte=NULL;
        }
    }
    if (ant!=NULL){
        act = fonte->next;
        if(act == NULL){
            printf("Lista vazia!\n");
            return;
        }
        nodenovo = (List)malloc(sizeof(No));
        id = verificaID(fonte);
        while(id == 0){
            id = verificaID(fonte);
        }
        while(act != NULL){
            if (act->tarefa.identificador != id){
                ant = act;
                act = act->next;
            }
            else{
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
                nodenovo->tarefa.data_conclusao.ano = act->tarefa.data_conclusao.ano;
                nodenovo->tarefa.data_conclusao.mes = act->tarefa.data_conclusao.mes;
                nodenovo->tarefa.data_conclusao.dia = act->tarefa.data_conclusao.dia;
                nodenovo->tarefa.fase = fase;
                nodenovo->next = NULL;
                destino = addListaOrdenado(destino, nodenovo, fase);
                aux=act;
                if(act->next==NULL){
                    if (ant==fonte){
                        fonte=NULL;
                    }
                    else{
                        ant->next=NULL;
                    }
                }
                else{
                    act=act->next;
                    if (ant==fonte){
                        fonte=act;
                    }
                    else{
                        ant->next=act;
                    }
                }
                free(aux);
            }
        }
    }
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
                if(aux->tarefa.fase==2){
                    printf(" Data Conclusão: A tarefa ainda não se encontra concluída.\n");
                }
                if(aux->tarefa.fase==3){
                     printf(" Data Conclusão: %d/%d/%d\n",
                        aux->tarefa.data_conclusao.dia,
                        aux->tarefa.data_conclusao.mes,
                        aux->tarefa.data_conclusao.ano);
                }
            }
            aux=aux->next;
            printf("___________________________________________\n");
        }
    }
}

void imprime_lista_pessoa(List listaToDo, List listaDoing, List listaDone, char *nome){
    List aux;
    int fase;
    aux=listaToDo->next;
    printf("\nLista de tarefas \"To Do\":\n");
    for(fase=1; fase<4; fase++){
        if (fase==2){
            aux=listaDoing->next;
            printf("\nLista de tarefas \"Doing\":\n");
        }
        if (fase==3){
            aux=listaDone->next;
            printf("\nLista de tarefas \"Done\":\n");
        }
        while(aux!=NULL){
            if (strcmp(aux->tarefa.pessoa.nomePessoa,nome) == 0){
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
            }
        aux=aux->next;
        printf("___________________________________________\n");
        }
    }
}

void verificaPessoaFicheiro(char *nome){
    FILE *file = fopen("listapessoas.txt", "r");
    char *nomeFich;
    int ret;
    char linha[MAX];
    if(file == NULL){
        printf("Não foi possível abrir o ficheiro.\n");
        menu();
    }
    while (!feof(file)){
        fgets(linha, MAX, file);
        nomeFich = strtok(linha, "-");
        ret = strcmp(nomeFich, nome);
        if(ret == 0){
            break;
        }
    }
    if(ret != 0){
        printf("A pessoa introduzida não existe. Tente novamente: ");
        nome = protString();
        verificaPessoaFicheiro(nome);
    }
    fclose(file);
}

void leTarefa(List listaToDo,List listaDoing,List listaDone, TipoTarefa *tarefa, int max_tarefas){
    TipoData data;
    char *flag = "n";
    int auxiliar;
    printf("Identificador: ");
    tarefa->identificador = protInteiro();
    verificaIdentificador(listaToDo, tarefa);
    verificaIdentificador(listaDoing, tarefa);
    verificaIdentificador(listaDone, tarefa);
    printf("Insira data de criação: \n");
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
    tarefa->desc = protString();
    tarefa->fase = 1;
    printf("Deseja associar já a tarefa a uma pessoa? [s/n]: ");
    flag = protString();
    while(flag[0] != 's' && flag[0] != 'n'){
        printf("Resposta inválida, tente novamente [s/n]: ");
        flag = protString();
    }
    if(flag[0] == 's'){
        printf("Pessoa a atribuir: ");
        tarefa->pessoa.nomePessoa = protString();
        verificaPessoaFicheiro(tarefa->pessoa.nomePessoa);
        auxiliar=verificaMaxTarefasPessoas(listaToDo, listaDoing, listaDone, tarefa->pessoa.nomePessoa, max_tarefas);
        while(auxiliar==0){
            printf("Essa pessoa já tem um número máximo de tarefas atribuído. \n");
            printf("Pessoa a atribuir: ");
            tarefa->pessoa.nomePessoa = protString();
            verificaPessoaFicheiro(tarefa->pessoa.nomePessoa);
            auxiliar=verificaMaxTarefasPessoas(listaToDo, listaDoing, listaDone, tarefa->pessoa.nomePessoa, max_tarefas);
        }
    }
    printf("Insira data de prazo: \n");
    verificaData(&data);
    compara_datas(tarefa, &data);
    tarefa->data_prazo.ano=data.ano;
    tarefa->data_prazo.mes=data.mes;
    tarefa->data_prazo.dia=data.dia;
    printf("\n");
}

void associaTarefa(List l, List x, List y, TipoTarefa *tarefa, char *flag, int id, int max_tarefas){
    List aux = l->next;
    char *nome;
    int auxiliar;
    if(flag[0] == 'n'){
        id = verificaID(l);
    }
    while(aux != NULL){
        if(id != aux->tarefa.identificador){
            aux=aux->next;
        }
        else{
            printf("Pessoa a atribuir: ");
            nome = protString();
            verificaPessoaFicheiro(nome);
            auxiliar=verificaMaxTarefasPessoas(l, x, y, nome, max_tarefas);
            while(auxiliar==0){
                printf("Essa pessoa já tem um número máximo de tarefas atribuído. \n");
                printf("Pessoa a atribuir: ");
                nome = protString();
                verificaPessoaFicheiro(nome);
                auxiliar=verificaMaxTarefasPessoas(l, x, y, nome, max_tarefas);
        }
        aux->tarefa.pessoa.nomePessoa = nome;
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
        return id;
    }
    else{
        printf("Não encontrei nada nesta lista. Tente novamente! \n");
    }
    return 0;
}

int verificaMaxTarefasPessoas(List l, List x, List y, char *nome, int max_tarefas){
    int num=0;
    int fase;
    List aux;
    aux=l->next;
    for(fase=1; fase<4; fase++){
        if (fase==2){
            aux=x->next;
        }
        if (fase==3){
            aux=y->next;
        }
        while(aux!=NULL){
            if(aux->tarefa.pessoa.nomePessoa != NULL){
                if (strcmp(aux->tarefa.pessoa.nomePessoa, nome) == 0){
                    num+=1;
                }
            }
        aux=aux->next;
        }
    }
    if (num<max_tarefas){
        return -1;
    }
    return 0;
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




