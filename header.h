

/*

Criar estrutura Data p/ fazer os prazos, datas de cria��o e afins

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

List addTarefa(List l, List node);
List criaListaTarefas(List l, List node);
void leTarefa(TipoTarefa *tarefa);
void printListaTarefas(List l, int num);
int protMenu();
int menu();
void listaPessoas();
