typedef struct vertice{
    int ligacao;
    char aresta;
    struct Vertice *proximo;
}Vertice;

typedef struct automato{
    int ligacoes;
    int narestas;
    char *alfabeto;
    int inicio;
    int *fim;
    struct Vertice **lista;
}Automato;

Automato *quintupla(int ligacoes, int narestas, char *alfabeto, int inicial, int *final);
void criarAresta(Automato *aut, int inicio, int fim, char ponte);
Vertice *criaVertice(int vertice, char ponte);
void qtdAresta(Automato *aut);
void addEstados(Automato *aut);
void  mostraAutomato(Automato *aut);
void sentenca(Automato *aut, char sentenca[]);
