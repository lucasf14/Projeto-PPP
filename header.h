/*

Criar estrutura Data p/ fazer os prazos, datas de criação e afins

*/

typedef struct S_Data{
    int dia, mes, ano;
}TipoData;

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
    TipoData data_criacao;
    char desc[100];
    TipoData data_prazo;
    TipoData data_conclusao;
    Pessoa pessoa;
    int fase;
    struct S_Tarefa *next;
} TipoTarefa;

typedef struct no *List; /*isto e um ponteiro para um no*/

typedef struct no{
    TipoTarefa tarefa;
    List next;
}No;

List addLista(List l, List node);
List criaLista(List l, List node);
void leTarefa(List l, TipoTarefa *tarefa);
void printListas(List l);
int protMenu();
int menu();
void listaPessoas();
void verificaData(TipoData*data);
void compara_datas(TipoTarefa*tarefa, TipoData*data);
void le_data(TipoTarefa *tarefa);
void associaTarefa(List l, TipoTarefa *tarefa, char flag, int id);
void printTarefasPessoa(List l, TipoTarefa *tarefa);
void verificaID(List l, TipoTarefa *tarefa);
void verificaListas(List listaToDo, List listaDoing, List node);
void imprime_lista(List l);
void procuraLista(List l, TipoTarefa *tarefa, int id);
