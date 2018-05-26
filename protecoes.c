#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MAX 1000

int protMenu() {
    char *string = (char *) malloc(MAX * sizeof(char));
    while (scanf(" %[^\n]", string) ) {
        int i = 0;
        int len = strlen(string);
        while (i < len) {
            if (string[i] < '0' || string[i] > '9') {
                printf("Comando inválido, tente novamente: ");
                free(string);
                return protMenu();
            }
            i++;
        }
    break;
    }
    return atoi(string);
}

int protInteiro() {
    char *inteiro = (char *) malloc(MAX * sizeof(char));
    while (scanf(" %[^\n]", inteiro) ) {
        int i = 0;
        int len = strlen(inteiro);
        if(strcmp(inteiro, "quit") == 0){
            return 0;
        }
        while (i < len) {
            if (inteiro[i] < '0' || inteiro[i] > '9') {
                printf("Não pode introduzir letras ou símbolos.\n");
                printf("Tente novamente: ");
                free(inteiro);
                return protInteiro();
            }
            else if(inteiro[0] == '0'){
                printf("Não pode introduzir números começados por 0.\n");
                printf("Tente novamente: ");
                free(inteiro);
                return protInteiro();
            }
            i++;
        }
        break;
    }
    return atoi(inteiro);
}

char *protString(){
    char *string = (char *) malloc(MAX * sizeof(char));
    while (scanf(" %[^\n]", string) ) {
        int i = 0;
        int len = strlen(string);
        if(strcmp(string, "quit") == 0){
            return string;
        }
        while (i < len) {
            if ((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32) {
                printf("Não pode introduzir números ou símbolos.\n");
                printf("Tente novamente: ");
                free(string);
                return protString();
            }
            i++;
        }
        break;
    }
    return string;
}


