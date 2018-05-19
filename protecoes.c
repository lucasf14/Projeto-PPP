#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include "header.h"
#define MaxTarefas 10
#define MAX 100

int protMenu() {
    char str[MAX];
    while (scanf(" %[^\n]", str) ) {
        int i = 0;
        int len = strlen(str);
        while (i < len) {
            if (str[i] < '0' || str[i] > '9' || i > 0) {
                printf("Comando desconhecido, tente novamente: ");
                protMenu();
            }
            i++;
        }
    break;
    }
    return atoi(str);
}

char *protString(){
    char *string = (char *) malloc(MAX * sizeof(char));
    while (scanf(" %[^\n]", string) ) {
        int i = 0;
        int len = strlen(string);
        while (i < len) {
            if ((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32) {
                printf("Nao pode introduzir números ou símbolos.\n");
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
