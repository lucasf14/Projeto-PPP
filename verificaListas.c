#include <stdio.h>
#include <stdlib.h>
#include "header.h"

void verificaListas(List listaToDo, List listaDoing, List node){
    if (node->tarefa.fase==1){
        if (listaToDo==NULL){
            listaToDo=criaLista(listaToDo, node);
        }
        else{
            listaToDo=addLista(listaToDo, node);
        }
    }
    else{
        if (listaDoing==NULL){
            listaDoing=criaLista(listaDoing, node);
        }
        else{
            listaDoing=addLista(listaDoing, node);
        }
    }
}

