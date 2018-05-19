#include <stdio.h>
#include <stdlib.h>
#include "header.h"


void verificaData(TipoData*data){
    int num_dias;
    printf("Ano:");
    while (!scanf(" %d", &data->ano)){
        printf("Ano inválido, tente novamente: ");
        fflush(stdin);
    }
    printf("\n Escolha o mês: \n 1->janeiro \t 2->fevereiro \t 3->marco \n 4->abril \t 5->maio \t 6->junho \n 7->julho \t 8->agosto \t 9->setembro \n 10->outubro \t 11->novembro \t 12->dezembro \n");
    printf("Mês:");
    scanf(" %d", &data->mes);
    while(data->mes>12 || data->mes<1){
        do{
            printf("Mês inválido, tente novamente: ");
            fflush(stdin);
        }
        while (!scanf(" %d", &data->mes));
    }
    if(data->mes==1 || data->mes==3 || data->mes==5 || data->mes==7 || data->mes==8 || data->mes==10 || data->mes==12){
            printf("Dia:");
            scanf(" %d", &data->dia);
            while(data->dia>31 || data->dia<1){
                do{
                    printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                    fflush(stdin);
                   }
                while (!scanf(" %d", &data->dia));
            }
    }
    if (data->mes==2){
            if (data->ano%4==0 && (data->ano%400==0 || data->ano%100!=0)){
                num_dias=29;
            }
            else{
                num_dias=28;
            }
            printf("Dia:");
            scanf(" %d", &data->dia);
            while(data->dia>num_dias || data->dia<1){
                do{
                    printf("O mês têm no máximo %d dias. Tente novamente: ", num_dias);
                    fflush(stdin);
                }
                while (!scanf(" %d", &data->dia));
            }
    }
    if(data->mes==4 || data->mes==6 || data->mes==9 || data->mes==11){
            printf("Dia:");
            scanf(" %d", &data->dia);
            while(data->dia>31 || data->dia<1){
                do{
                    printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                    fflush(stdin);
                }
                while (!scanf(" %d", &data->dia));
            }
    }
}

void compara_datas(TipoTarefa*tarefa, TipoData*data){
    int aux=0;
    while (aux==0){
        if(tarefa->data_criacao.ano<data->ano){
            aux=1;
        }
        else if (tarefa->data_criacao.ano==data->ano){
            if (tarefa->data_criacao.mes<data->mes){
                aux=1;
            }
            else if(tarefa->data_criacao.mes==data->mes){
                if (tarefa->data_criacao.dia<data->dia){
                    aux=1;
                }
            }
        }
        if (aux==0){
            printf("A data de prazo nao pode ser inferior à data de criacao.\n");
            printf("Data de Criacao:%d/%d/%d \nInsira nova data de prazo: \n", tarefa->data_criacao.dia, tarefa->data_criacao.mes, tarefa->data_criacao.ano);
            verificaData(data);
        }
    }
}


