#include <stdio.h>
#include <stdlib.h>
#include "header.h"


void verificaData(TipoTarefa *tarefa){
    int num_dias;
    printf("Insira o prazo: \n");
    printf("Ano:");
    while (!scanf(" %d", &tarefa->data_prazo.ano)){
        printf("Ano inválido, tente novamente: ");
        fflush(stdin);
    }

    printf("\n Escolha o mês: \n 1->janeiro \t 2->fevereiro \t 3->marco \n 4->abril \t 5->maio \t 6->junho \n 7->julho \t 8->agosto \t 9->setembro \n 10->outubro \t 11->novembro \t 12->dezembro \n");
    printf("Mês:");
    scanf(" %d", &tarefa->data_prazo.mes);


    while(tarefa->data_prazo.mes>12 || tarefa->data_prazo.mes<1){
        do{
            printf("Mês inválido, tente novamente: ");
            fflush(stdin);
        }
        while (!scanf(" %d", &tarefa->data_prazo.mes));
    }

    switch(tarefa->data_prazo.mes){
            case 1:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 2:
                if (tarefa->data_prazo.ano%4==0 && (tarefa->data_prazo.ano%400==0 || tarefa->data_prazo.ano%100!=0)){
                    num_dias=29;
                }
                else{
                    num_dias=28;
                }
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>num_dias || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês têm no máximo %d dias. Tente novamente: ", num_dias);
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 3:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 4:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>30 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 30 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 5:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 6:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>30 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 30 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 7:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 8:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 9:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>30 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 30 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 10:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 11:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>30 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 30 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;

            case 12:
                printf("Dia:");
                scanf(" %d", &tarefa->data_prazo.dia);
                while(tarefa->data_prazo.dia>31 || tarefa->data_prazo.dia<1){
                    do{
                        printf("O mês tem no máximo 31 dias. Tente Novamente: ");
                        fflush(stdin);
                    }
                    while (!scanf(" %d", &tarefa->data_prazo.dia));
                }
                break;
    }
}
