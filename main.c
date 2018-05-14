#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxTarefas 10

/*

Criar estrutura Data p/ fazer os prazos, datas de criação e afins

*/

typedef struct S_Prazo{
    int diap, mesp, anop;
} Prazo;

typedef struct S_DataConclusao{
    int diac, mesc, anoc;
} DataConclusao;

typedef struct S_Pessoa{
    char nomePessoa[100];
    char mail[100];
    int identificador;
    struct S_Pessoa *next;
} Pessoa;

typedef struct S_Tarefa{
    char novaTarefa[100];
    int prioridade;
    int identificador;
    char desc[100];
    Prazo prazo;
    DataConclusao conclusao;
    Pessoa pessoa;
    struct S_Tarefa *next;
} TipoTarefa;



typedef struct no *List; /*isto e um ponteiro para um no*/

typedef struct no{
    TipoTarefa tarefa;
    List next;
}No;

List addTarefa_inicio(List l, List node){
    node->next=l;
    l=node;
    return l;
}

List addTarefa_fim(List l, List node){
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
    scanf(" %d", &tarefa->identificador);

    while (!scanf(" %d", &tarefa->prioridade ))
        fflush(stdin);
    printf("Prioridade (1 a 10): ");
    scanf(" %d", &tarefa->prioridade);
    while(tarefa->prioridade <= 0 || tarefa->prioridade > 10){
        while (!scanf(" %d", &tarefa->prioridade ))
            printf("Prioridade invalida, tente novamente (1 a 10): ");
            fflush(stdin);
    }
    printf("Descricao da tarefa: ");
    scanf(" %[^\n]s", tarefa->desc);
    printf("Prazo: ");
    scanf("%d/%d/%d", &tarefa->conclusao.diac, &tarefa->conclusao.mesc, &tarefa->conclusao.anoc);
    printf("Pessoa a atribuir: ");
    scanf(" %[^\n]s", tarefa->pessoa.nomePessoa); /* verificar se está no ficheiro */

    /*while (!scanf("%d/%d/%d", &tarefa->conclusao.diac, &tarefa->conclusao.mesc, &tarefa->conclusao.anoc)){
        printf("Prazo invalido, tente novamente (dd/mm/aaaa): ");
        fflush(stdin);
    }

    CHECK NOUTRA ALTURA

    */

    printf("\n");
}

void printListaTarefas(List l, int num){
    int i = 1;
    printf("____________________\n", num);
    while(l!=NULL){
        printf("\nTarefa no. %d: %s\nPrioridade: %d\nDescricao da tarefa: %s\nPrazo: %d/%d/%d", i,
               l->tarefa.novaTarefa,
               l->tarefa.prioridade,
               l->tarefa.desc,
               l->tarefa.conclusao.diac,
               l->tarefa.conclusao.mesc,
               l->tarefa.conclusao.anoc);
        l=l->next;
        i+= 1;
    }
    printf("____________________\nTotal de tarefas: %d\n\n", num);
}

int main(){
    int totalTarefas = 0;
    int comando;
    List listaTarefas, novo;
    listaTarefas = NULL;
    while(1){
        printf("MENU:\n[1] Definir tarefas.\n[2] Ver lista de tarefas.\n...\n[10] Sair do programa.\n\nIntroduza o comando: ");
        scanf("%d", &comando);
        switch(comando){
            default:
                printf("Comando desconhecido, tente novamente!\n");
                break;
            case 1:
                if(totalTarefas < MaxTarefas){
                    if(totalTarefas == 0){
                        novo=(List)malloc(sizeof(No));
                        leTarefa(&novo->tarefa);
                        listaTarefas=addTarefa_inicio(listaTarefas, novo);
                        totalTarefas += 1;
                        break;
                    }
                    else{
                        novo=(List)malloc(sizeof(No));
                        leTarefa(&novo->tarefa);
                        listaTarefas=addTarefa_fim(listaTarefas, novo);
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
            case 10:
                return 0;
        }
    }
}
