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



List addListaFinal(List l, List node);
List criaLista();
List addListaOrdenado(List l, List node, int fase);

int comparaMaiorPrioridade(List fonte, List destino);
int comparaMaiorData(TipoData *data1, TipoData *data2);
void procura_lista(List l, int identificador, List prev, List cur);
int comparaNome(List fonte, List destino);
void leTarefa(List listaToDo,List listaDoing,List listaDone, TipoTarefa *tarefa);
void printListas(List l);
int protMenu();
char *protString();
int protInteiro();
int menu();
void listaPessoas();
void verificaData(TipoData*data, TipoTarefa *tarefa);
void verificaIdentificador(List l, TipoTarefa *tarefa);
void verificaPessoaFicheiro(TipoTarefa *tarefa);
void compara_datas(TipoTarefa*tarefa, TipoData*data);
void le_data(TipoTarefa *tarefa);
void associaTarefa(List l, TipoTarefa *tarefa, char *flag, int id);
int verificaID(List l);
void imprime_lista(List l);

List mover_tarefas(List fonte, List destino, int fase);
List eliminaTarefa(List l);
