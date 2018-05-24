typedef struct S_Data{
    int dia, mes, ano;
}TipoData;

typedef struct S_Pessoa{
    char *nomePessoa;
    char *mail;
    int identificador;
    struct S_Pessoa *next;
} Pessoa;

typedef struct S_Tarefa{
    int prioridade;
    int identificador;
    TipoData data_criacao;
    char *desc;
    TipoData data_prazo;
    TipoData data_conclusao;
    Pessoa pessoa;
    int fase;
    struct S_Tarefa *next;
} TipoTarefa;

typedef struct no* List; /*isto e um ponteiro para um no*/

typedef struct no{
    TipoTarefa tarefa;
    List next;
}No;



List addLista(List l, List node);
List criaLista(List l, List node);
List addListaOrdenado(List l, List node);
int comparaMaiorPrioridade(List fonte, List destino);
int comparaMaiorData(List data1, List data2);
void procura_lista(List l, int identificador, List ant, List seg, List atual);
void mover_tarefas(List listaToDo, List listaDoing, List listaDone, TipoTarefa*tarefa);
void leTarefa(List l, TipoTarefa *tarefa);
void printListas(List l);
int protMenu();
char *protString();
int protInteiro();
int menu();
void listaPessoas();
void verificaData(TipoData*data);
void verificaPessoaFicheiro(TipoTarefa *tarefa);
void compara_datas(TipoTarefa*tarefa, TipoData*data);
void le_data(TipoTarefa *tarefa);
void associaTarefa(List l, TipoTarefa *tarefa, char *flag, int id);
void printTarefasPessoa(List l, TipoTarefa *tarefa);
int verificaID(List l, TipoTarefa *tarefa);
void imprime_lista(List l);
